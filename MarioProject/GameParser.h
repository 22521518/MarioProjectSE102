// IGameParser.h
#pragma once
#include <string>
#include "FileConfig.h"  // struct SettingConfig, SceneConfig, TextureConfig, FileGameConfig

class IGameParser {
public:
    virtual ~IGameParser() {}
    virtual FileGameConfig _ParseGameConfigFile(const std::string& filename) = 0;
    virtual FilePlaySceneConfig _ParsePlaySceneFile(const string& filename) = 0;
};