#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "../PAT_Parcial03/Ejercicio03.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;
using ::std::unordered_map;

namespace HojaDeTrabajo03Tests {

	const char FUNC_TYPE = 'F';
	const char VOID_TYPE = 'V';

	struct Operation {
		string funcName;
		string key;
		string value;
		int timestamp;
		string expected;
		char type;
	};

	string set(TimeMap* timeMap, Operation* op) {
		timeMap->set(op->key, op->value, op->timestamp);
		return "";
	}

	string get(TimeMap* timeMap, Operation* op) {
		return timeMap->get(op->key, op->timestamp);
	}

	static const unordered_map<string, string(*)(TimeMap*, Operation*)> timeMapOps = {
		{ "set", set },
		{ "get", get }
	};

	class E03Tests : public TestWithParam < vector<Operation*>> {
	protected:
		TimeMap* timeMap;
		vector<Operation*> operations;

		void SetUp() override {
			timeMap = new TimeMap();
			operations = GetParam();
		}

		void TearDown() override {
			delete timeMap;
			timeMap = nullptr;
		}
	public:
		static vector<vector<Operation*>> ReadParams() {
			vector<vector<Operation*>> params;

			std::ifstream paramsFile("e03.csv");
			string line1, line2;
			vector<Operation*>* ops = new vector<Operation*>();
			while (std::getline(paramsFile, line1)) {
				if (line1.length() == 0) {
					params.push_back(*ops);
					ops = new vector<Operation*>();
					continue;
				}

				vector<string> tokens;
				tokens.reserve(4);

				std::stringstream commaStream(line1);

				while (std::getline(commaStream, line2, ',')) {
					tokens.push_back(line2);
				}

				string funcName = tokens[0];
				string key = tokens[1];
				string valueOrTimestamp = tokens[2];
				string timestampOrExpected = tokens[3];

				Operation* op = new Operation{ funcName, key };

				if (funcName == "set") {
					op->value = valueOrTimestamp;
					op->timestamp = std::stoi(timestampOrExpected);
					op->expected = "";
					op->type = VOID_TYPE;
				}
				else {
					op->value = "";
					op->timestamp = std::stoi(valueOrTimestamp);
					op->expected = (timestampOrExpected == "-" ? "" : timestampOrExpected);
					op->type = FUNC_TYPE;
				}

				ops->push_back(op);
			}

			if (!ops->empty())
				params.push_back(*ops);

			return params;
		}
	};

	TEST_P(E03Tests, E03TimeMap) {
		int i = 0;

		for (auto op : operations) {
			GTEST_COUT << " - Instruccion [" << i << "]: " 
				<< op->funcName << "(" 
				<< op->key << ","
				<< (op->type == VOID_TYPE ? op->value + "," : std::to_string(op->timestamp) + "") 
				<< (op->type == VOID_TYPE ? std::to_string(op->timestamp) : "")
				<< ")" << std::endl;

			string actualResult = "";

			ASSERT_DURATION_LE(100,
				actualResult = timeMapOps.at(op->funcName)(timeMap, op););

			if (op->type == FUNC_TYPE) {
				ASSERT_EQ(actualResult, op->expected) << "Error al llamar la instruccion [" << i << "] -> " 
					<< op->funcName << "().\nSe esperaba [" << op->expected << "], pero se encontro [" << actualResult << "]";
			}

			++i;
		}
	}

	INSTANTIATE_TEST_CASE_P(E03TimeMap, E03Tests, ValuesIn(E03Tests::ReadParams()));
}