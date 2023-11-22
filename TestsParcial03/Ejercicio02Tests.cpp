#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_Parcial03/Ejercicio02.h"
#include "../PAT_Parcial03/Node.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace HojaDeTrabajo03Tests {

	class E02Tests : public TestWithParam < tuple<string, vector<string>>> {
	protected:
		Ejercicio02* e02;
		string param;
		vector<string> expectedResult;

		void SetUp() override {
			e02 = new Ejercicio02();
			std::tie(param, expectedResult) = GetParam();
		}

		void TearDown() override {
			delete e02;
			e02 = nullptr;
		}
	public:
		static vector<tuple<string, vector<string>>> ReadParams() {
			vector<tuple<string, vector<string>>> params;

			std::ifstream paramsFile("e02.csv");
			string line1, line2;
			while (std::getline(paramsFile, line1) && std::getline(paramsFile, line2)) {
				std::stringstream commaStream(line2);

				vector<string> r;
				string commaLine;
				while (std::getline(commaStream, commaLine, ',')) {
					r.push_back(commaLine);
				}
				
				params.push_back({ line1, r });
			}

			return params;
		}
	};

	Node<char>* buildList(const string& str) {
		Node<char>* head = nullptr;
		Node<char>** it = &head;

		for (const auto& i : str) {
			*it = new Node<char>{ i };
			it = &((*it)->next);
		}

		return head;
	}

	TEST_P(E02Tests, E02DNA) {
		
		Node<char>* head = buildList(param);

		vector<string>* actualResult;

		ASSERT_DURATION_LE(100,
			actualResult = e02->findRepeatedDnaSequences(head););

		int i = 0;
		int expectedSize = expectedResult.size();
		int actualSize = actualResult->size();

		EXPECT_EQ(expectedSize, actualSize) << "La cantidad de resultados no es la esperada.";

		std::sort(expectedResult.begin(), expectedResult.end());
		std::sort(actualResult->begin(), actualResult->end());

		for (int i = 0; i < expectedSize && i < actualSize; i++) {
			ASSERT_EQ(expectedResult[i], (*actualResult)[i]) << "Error en la posicion [" << i << "] del resultado"
				<< ". Se esperaba [" << expectedResult[i] << "], pero se encontro [" << (*actualResult)[i];
		}
	}

	INSTANTIATE_TEST_CASE_P(E02DNA, E02Tests, ValuesIn(E02Tests::ReadParams()));
}