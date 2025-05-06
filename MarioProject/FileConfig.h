#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct SettingConfig
{
    int start;
    int width;
    int height;
};

struct SceneConfig
{
    int sceneID;
    string scenePath;
};

struct TextureConfig
{
    int textureID;
    string texturePath;
};

struct FileGameConfig
{
    SettingConfig setting;
    vector<SceneConfig> scenes;
    vector<TextureConfig> textures;
};