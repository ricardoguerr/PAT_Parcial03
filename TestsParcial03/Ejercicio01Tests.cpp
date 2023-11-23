#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_Parcial03/Ejercicio01.h"
#include "../PAT_Parcial03/Node.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace Parcial03Tests {

	bool compareAscending(const int& a, const int& b) {
		return a > b;
	}

	class E01Tests : public TestWithParam < tuple<vector<vector<int>>, vector<int>> > {
	protected:
		Ejercicio01* e01;
		vector<vector<int>> param;
		vector<int> expectedHead;

		void SetUp() override {
			e01 = new Ejercicio01();
			std::tie(param, expectedHead) = GetParam();
		}

		void TearDown() override{
			delete e01;
			e01 = nullptr;
		}

		static vector<int> computeExpectedResult(vector<vector<int>>& lists) {
			if (lists.empty())
				return vector<int>();

			int count = lists.size();
			
			vector<vector<int>> result(lists.begin(), lists.end()); 

			while (count > 1) {
				for (int i = 0; i < count / 2; ++i) {
					vector<int> r;
					r.reserve(result[i].size() + result[count - i - 1].size());

					std::merge(result[i].begin(), result[i].end(),
						result[count - i - 1].begin(), result[count - i - 1].end(),
						std::back_inserter(r), 
						compareAscending);

					result[i] = r;
				}

				count = (count + 1) / 2;
			}

			return result[0];
		}
	
		static void readFromFile(string filepath, vector<tuple<vector<vector<int>>, vector<int>>>& params) {
			std::ifstream paramsFile(filepath);
			string line;
			while (std::getline(paramsFile, line)) {
				std::stringstream pipeStream(line);

				vector<vector<int>> lists;
				string pipeLine;
				while (std::getline(pipeStream, pipeLine, '|')) {
					std::stringstream commaStream(pipeLine);
					
					vector<int> nums;
					string commaLine;
					while (std::getline(commaStream, commaLine, ',')) {
						nums.push_back(std::stoi(commaLine));
					}

					lists.push_back(nums);
				}

				vector<int> expectedResult = computeExpectedResult(lists);

				params.push_back({ lists, expectedResult });
			}
		}

	public:
		static vector<tuple<vector<vector<int>>, vector<int>>> ReadParams() {
			vector<tuple<vector<vector<int>>, vector<int>>> params;

			readFromFile("e01a.csv", params);

			return params;
		}
	};

	Node<int>* buildList(const vector<int>& list) {
		Node<int>* head = nullptr;
		Node<int>** it = &head;

		for (const auto& i : list) {
			*it = new Node<int>{ i };
			it = &((*it)->next);
		}

		return head;
	}

	Node<Node<int>*>* buildListOfLists(vector<vector<int>>& list) {
		Node<Node<int>*>* head = nullptr;
		Node<Node<int>*>** it = &head;

		Node<int>* aux;

		for (const auto& l : list) {
			Node<int>* aux = buildList(l);
			*it = new Node<Node<int>*>{ aux };
			it = &((*it)->next);
		}

		return head;
	}

	TEST_P(E01Tests, E01Merge) {
		auto lists = buildListOfLists(param);

		Node<int>* head = nullptr;
		
		ASSERT_DURATION_LE(100,
			head = e01->mergeLists(lists););

		int i = 0;
		int size = expectedHead.size();
		while (head && i < size) {
			ASSERT_EQ(expectedHead[i], head->value) << "Error en la posicion [" << i << "] de la lista"
				<< ". Se esperaba [" << expectedHead[i] << "], pero se encontro [" << head->value;

			++i;
			head = head->next;
		}

		ASSERT_TRUE(head == nullptr && i == size) << "La cantidad de nodos no es la esperada.";
	}

	INSTANTIATE_TEST_CASE_P(E01Merge, E01Tests, ValuesIn(E01Tests::ReadParams()));
}