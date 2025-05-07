#include "mapUtil.h"

float getOrDefault(const unordered_map<string, float>& map, const string& key, float defaultValue)
{
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return defaultValue;
}