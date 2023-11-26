#include "Ejercicio02.h"

vector<string>* Ejercicio02::findRepeatedDnaSequences(Node<char>* head)
{
    std::unordered_map<string, int> map;

    vector<string>* result = new vector<string>();

    string current = "";

    Node<char>* p = head;

    while (p != nullptr) {

        current += p->value;

        if (current.size() == 10) {

            map[current]++;

            current.erase(0, 1);
        }

        p = p->next;
    }

    for (auto& pair : map) {

        if (pair.second > 1) {

            result->push_back(pair.first);
        }
    }

    return result;
}