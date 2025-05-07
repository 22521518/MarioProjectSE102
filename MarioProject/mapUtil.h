#pragma once
#include <unordered_map>
#include <string>

using namespace std;

template<typename T>
T getOrDefault(const unordered_map<string, T>& map, const string& key, T defaultValue)
{
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return defaultValue;
}

float getOrDefault(const unordered_map<string, float>& map, const string& key, float defaultValue);