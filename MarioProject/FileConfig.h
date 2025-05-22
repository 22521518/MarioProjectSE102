#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#pragma region PLAY_SCENE
struct GameObjectConfig
{
    int typeID = 0;          
    float x = 0.0f;          
    float y = 0.0f;          
    unordered_map<string, float> additionalFieldInfo;
};

struct SpriteConfig
{
    int spriteID = 0;        
    int textureID = 0;       
    int left = 0;            
    int top = 0;             
    int right = 0;           
    int bottom = 0;          
};

struct AnimationFrameConfig
{
    int spriteID = 0;        
    int frameTime = 0;       
};

struct AnimationConfig
{
    int animationID = 0;     
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
    int start = 0;          
    int width = 0;          
    int height = 0;         
};

struct SceneConfig
{
    int sceneID = 0;        
    string scenePath = "";  

    // Default constructor
    SceneConfig() = default;

    // Constructor with parameters
    SceneConfig(int id, const std::string& path) : sceneID(id), scenePath(path) {}
};

struct TextureConfig
{
    int textureID = 0;      
    string texturePath = "";

    // Default constructor
    TextureConfig() = default;

    // Constructor with parameters
    TextureConfig(int id, const std::string& path) : textureID(id), texturePath(path) {}
};

struct FileGameConfig
{
    SettingConfig setting;
    vector<SceneConfig> scenes;
    vector<TextureConfig> textures;

    // Default constructor
    FileGameConfig() = default;

    // Constructor with parameters
    FileGameConfig(const SettingConfig& settings, const vector<SceneConfig>& sc, const vector<TextureConfig>& tex)
        : setting(settings), scenes(sc), textures(tex) {
    }
};
#pragma endregion
