#include <stdexcept>         
#include <cstdlib>           
#include <string>           
#include <fstream>
#include <sstream>

#include "TxtGameParser.h"
#include "GameParserFactory.h"
#include "debug.h"
#include "stringUtil.h"      
#include "AssetIDs.h"
#include "Platform.h"
#include "Portal.h"

#pragma region PLAY_SCENE
SpriteConfig TxtGameParser::_ParseSection_SPRITE(const string& line)
{
    SpriteConfig sprite{};
    vector<string> tokens = split(line);
    if (tokens.size() < 6)
    {
        DebugOut(L"[ERROR] Failed to parse line: %s\n Invalid format.", ToWSTR(line).c_str());
        return sprite;
    }

    sprite.spriteID = atoi(tokens[0].c_str());
    sprite.left = atoi(tokens[1].c_str());
    sprite.top = atoi(tokens[2].c_str());
    sprite.right = atoi(tokens[3].c_str());
    sprite.bottom = atoi(tokens[4].c_str());
    sprite.textureID = atoi(tokens[5].c_str());
    return sprite;
}
AnimationConfig TxtGameParser::_ParseSection_ANIMATION(const string& line)
{
    AnimationConfig ani;
    vector<string> tokens = split(line);
    if (tokens.size() < 3)
    {
        DebugOut(L"[ERROR] Failed to parse line: %s\n Invalid format.", ToWSTR(line).c_str());
        return ani;
    }

    ani.animationID = atoi(tokens[0].c_str());
    for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
    {
        AnimationFrameConfig frame;
        frame.spriteID = atoi(tokens[i].c_str());
        frame.frameTime = atoi(tokens[i + 1].c_str());
        ani.animationFrames.push_back(frame);
    }

    return ani;
}
void TxtGameParser::_ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath)
{
    vector<string> tokens = split(assetPath);
    if (tokens.size() < 1) return;

    string filename = tokens[0];
    ifstream f(filename);
    if (!f.is_open())
    {
        DebugOut(L"[ERROR] Failed to open file: %s\n", filename);
        return;
    }

    string line;
    string section;

    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;

        if (line[0] == '[')
        {
            section = line;
            continue;
        }

        try {
            if (section == "[SPRITES]")
            {
                config.sprites.push_back(_ParseSection_SPRITE(line));
            }
            else if (section == "[ANIMATIONS]")
            {
                config.animations.push_back(_ParseSection_ANIMATION(line));
            }
        }
        catch (const exception& e)
        {
            DebugOut(L"[ERROR] Failed to parse line: %s. Exception: %s\n", ToWSTR(line).c_str(), ToWSTR(e.what()).c_str());
        }
    }
}
GameObjectConfig TxtGameParser::_ParseSection_OBJECT(const string& line)
{
    GameObjectConfig gObjectConfig{};
    vector<string> tokens = split(line);
    if (tokens.size() < 2)
    {
        DebugOut(L"[ERROR] Failed to parse line: %s\n Invalid format.", ToWSTR(line).c_str());
        return gObjectConfig;
    }

    gObjectConfig.typeID = atoi(tokens[0].c_str());
    gObjectConfig.x = (float)atof(tokens[1].c_str());
    gObjectConfig.y = (float)atof(tokens[2].c_str());

    switch (gObjectConfig.typeID)
    {
    case OBJECT_TYPE_PLATFORM: 
    {
        gObjectConfig.additionalFieldInfo = CPlatform::GetAdditionalFieldInfo(tokens);
        break;
    }
    case OBJECT_TYPE_PORTAL:
    {
        gObjectConfig.additionalFieldInfo = CPortal::GetAdditionalFieldInfo(tokens);
        break;
    }
    default: break;
    }
    return gObjectConfig;
}
FilePlaySceneConfig TxtGameParser::_ParsePlaySceneFile(const string& filename)
{
    FilePlaySceneConfig config{};
    ifstream f(filename);
    if (!f.is_open())
    {
        DebugOut(L"[ERROR] Failed to open file: %s\n", filename);
        return config;
    }

    string line;
    string section;

    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;

        if (line[0] == '[')
        {
            section = line;
            continue;
        }

        try {
            if (section == "[ASSETS]")
            {
                auto parser = GameParserFactory::Create(line);
                parser->_ParseSection_ASSET(config, line);
            }
            else if (section == "[OBJECTS]")
            {
                config.gameObjects.push_back(_ParseSection_OBJECT(line));
            }
        }
        catch (const exception& e)
        {
            DebugOut(L"[ERROR] Failed to parse line: %s. Exception: %s\n", ToWSTR(line).c_str(), ToWSTR(e.what()).c_str());
        }
    }

    return config;
}
#pragma endregion

#pragma region GAME_STATE
SettingConfig TxtGameParser::_ParseSection_SETTING(const string& line)
{
    DebugOut(L"[INFO] Start loading game setting : %s\n", ToWSTR(line).c_str());
    vector<string> tokens = split(line, "\t");

    if (tokens.size() < 2)
    {
        throw runtime_error("TxtGameParser::_ParseSection_SETTING: line format invalid");
    }

    SettingConfig setting{};
    if (tokens[0] == "start")
    {
        setting.start = atoi(tokens[1].c_str());
    }
    else if (tokens[0] == "width")
    {
        setting.width = atoi(tokens[1].c_str());
    }
    else if (tokens[0] == "height")
    {
        setting.height = atoi(tokens[1].c_str());
    }
    else {
        DebugOut(L"[ERROR] Unknown command: %s\n", ToWSTR(tokens[0]).c_str());
    }

    return setting;
}

SceneConfig TxtGameParser::_ParseSection_SCENE(const string& line)
{
    DebugOut(L"[INFO] Start loading game scene : %s\n", ToWSTR(line).c_str());
    vector<string> tokens = split(line, "\t");

    if (tokens.size() < 2)
    {
        throw runtime_error("TxtGameParser::_ParseSection_SCENE: line format invalid");
    }

    SceneConfig scene{};
    scene.sceneID = atoi(tokens[0].c_str());
    scene.scenePath = tokens[1];

    DebugOut(L"[INFO] Done loading scene %d, %s\n",
        scene.sceneID, ToWSTR(scene.scenePath).c_str());

    return scene;
}

TextureConfig TxtGameParser::_ParseSection_TEXTURE(const string& line)
{
    DebugOut(L"[INFO] Start loading game texture : %s\n", ToWSTR(line).c_str());
    vector<string> tokens = split(line);  // split by whitespace

    if (tokens.size() < 2)
    {
        throw runtime_error("TxtGameParser::_ParseSection_TEXTURE: line format invalid");
    }

    TextureConfig texture{};
    texture.textureID = atoi(tokens[0].c_str());
    texture.texturePath = tokens[1];

    DebugOut(L"[INFO] Done loading texture %d, %s\n",
        texture.textureID, ToWSTR(texture.texturePath));

    return texture;
}

FileGameConfig TxtGameParser::_ParseGameConfigFile(const string& filename)
{
    FileGameConfig config;
    ifstream f(filename);
    string line;
    string section;

    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;

        if (line[0] == '[')
        {
            section = line;
            continue;
        }

        try {
            if (section == "[SETTINGS]")
            {
                SettingConfig setting = _ParseSection_SETTING(line);
                if (line.find("start") == 0) config.setting.start = setting.start;
                else if (line.find("width") == 0) config.setting.width = setting.width;
                else if (line.find("height") == 0) config.setting.height = setting.height;
            }
            else if (section == "[SCENES]")
            {
                SceneConfig scene = _ParseSection_SCENE(line);
                config.scenes.push_back(scene);
            }
            else if (section == "[TEXTURES]")
            {
                TextureConfig texture = _ParseSection_TEXTURE(line);
                config.textures.push_back(texture);
            }
        }
        catch (const exception& e)
        {
            DebugOut(L"[ERROR] Failed to parse line: %s. Exception: %s\n", ToWSTR(line).c_str(), ToWSTR(e.what()).c_str());
        }
    }

    return config;
}
#pragma endregion
