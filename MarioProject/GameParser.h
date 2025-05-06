// IGameParser.h
#pragma once
#include <string>
#include "FileConfig.h"  // struct SettingConfig, SceneConfig, TextureConfig, FileGameConfig

class IGameParser {
public:
    virtual ~IGameParser() {}
    virtual FileGameConfig Parse(const std::string& filename) = 0;
};