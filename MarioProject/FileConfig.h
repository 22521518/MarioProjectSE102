#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#pragma region PLAY_SCENE
struct GameObjectConfig
{
    int typeID;
    float x;
    float y;
    unordered_map<string, float> additionalFieldInfo;
};

struct SpriteConfig 
{
    int spriteID;
    int textureID;
    int left;
    int top;
    int right;
    int bottom;
};

struct AnimationFrameConfig
{
    int spriteID;
    int frameTime;
};

struct AnimationConfig
{
    int animationID;
    vector<AnimationFrameConfig> animationFrames;
};

struct FilePlaySceneConfig
{
    vector<GameObjectConfig> gameObjects;
    vector<AnimationConfig> animations;
    vector<SpriteConfig> sprites;
};
#pragma endregion

#pragma region GAME_STATE
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
#pragma endregion