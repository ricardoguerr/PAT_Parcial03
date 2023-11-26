
#include "Ejercicio03.h"
#include <unordered_map>
#include <map>

TimeMap::TimeMap() {
}

void TimeMap::set(string key, string value, int timestamp) {
    structure[key].push_back({ value, timestamp });
}

string TimeMap::get(string key, int timestamp) {
    if (structure.find(key) == structure.end()) {
        return "";
    }
    return search(structure[key], timestamp);
}

string TimeMap::search(vector<pair<string, int>>& temp, const int& timestamp) {
    int low = 0;
    int high = temp.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (temp[mid].second > timestamp) {
            high = mid - 1;
        }
        else if (temp[mid].second < timestamp) {
            low = mid + 1;
        }
        else {
            return temp[mid].first;
        }
    }

    return high >= 0 ? temp[high].first : "";
}