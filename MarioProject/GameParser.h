// IGameParser.h
#pragma once
#include <string>
#include "FileConfig.h"  // struct SettingConfig, SceneConfig, TextureConfig, FileGameConfig

using namespace std;

class IGameParser {
public:
    virtual ~IGameParser() {}
    virtual void _ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath) = 0;
    virtual FileGameConfig _ParseGameConfigFile(const string& filename) = 0;
    virtual FilePlaySceneConfig _ParsePlaySceneFile(const string& filename) = 0;
};