#include "Ejercicio01.h"
#include <vector>
#include <algorithm>

Node<int>* Ejercicio01::mergeLists(Node<Node<int>*>* lists)
{

    auto compare = [](Node<int>* a, Node<int>* b) {
        return a->value > b->value;
        };


    std::vector<Node<int>*> nodes;

    while (lists != nullptr)
    {
        Node<int>* currentList = lists->value;

        while (currentList != nullptr)
        {
            nodes.push_back(currentList);
            currentList = currentList->next;
        }

        lists = lists->next;
    }


    std::sort(nodes.begin(), nodes.end(), compare);

    Node<int>* result = nullptr;
    Node<int>* tail = nullptr;
    for (Node<int>* node : nodes)
    {
        if (result == nullptr)
        {
            result = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    if (tail != nullptr)
    {
        tail->next = nullptr;
    }

    return result;
}