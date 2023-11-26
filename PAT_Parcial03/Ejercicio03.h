#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;
using std::pair;

class TimeMap {
private:
    unordered_map<string, vector<pair<string, int>>> structure;

    string search(vector<pair<string, int>>& temp, const int& timestamp);

public:
    TimeMap();

    void set(string key, string value, int timestamp);

    string get(string key, int timestamp);
};