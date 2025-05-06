#include "TxtGameParser.h"
#include "debug.h"
#include "stringUtil.h"      
#include <stdexcept>         
#include <cstdlib>           

#pragma region GAME_STATE
SettingConfig TxtGameParser::_ParseSection_SETTING(const std::string& line)
{
    DebugOut(L"[INFO] Start loading game setting : %s\n", ToWSTR(line).c_str());
    auto tokens = split(line, "\t");

    if (tokens.size() < 2) {
        throw std::runtime_error("TxtGameParser::_ParseSection_SETTING: line format invalid");
    }

    SettingConfig setting{};
    if (tokens[0] == "start") {
        setting.start = std::atoi(tokens[1].c_str());
    }
    else if (tokens[0] == "width") {
        setting.width = std::atoi(tokens[1].c_str());
    }
    else if (tokens[0] == "height") {
        setting.height = std::atoi(tokens[1].c_str());
    }
    else {
        DebugOut(L"[ERROR] Unknown command: %s\n", ToWSTR(tokens[0]).c_str());
    }

    return setting;
}

SceneConfig TxtGameParser::_ParseSection_SCENE(const std::string& line)
{
    DebugOut(L"[INFO] Start loading game scene : %s\n", ToWSTR(line).c_str());
    auto tokens = split(line, "\t");

    if (tokens.size() < 2) {
        throw std::runtime_error("TxtGameParser::_ParseSection_SCENE: line format invalid");
    }

    SceneConfig scene{};
    scene.sceneID = std::atoi(tokens[0].c_str());
    scene.scenePath = tokens[1];

    DebugOut(L"[INFO] Done loading scene %d, %s\n",
        scene.sceneID, ToWSTR(scene.scenePath).c_str());

    return scene;
}

TextureConfig TxtGameParser::_ParseSection_TEXTURE(const std::string& line)
{
    DebugOut(L"[INFO] Start loading game texture : %s\n", ToWSTR(line).c_str());
    auto tokens = split(line);  // split by whitespace

    if (tokens.size() < 2) {
        throw std::runtime_error("TxtGameParser::_ParseSection_TEXTURE: line format invalid");
    }

    TextureConfig texture{};
    texture.textureID = std::atoi(tokens[0].c_str());
    texture.texturePath = tokens[1];

    DebugOut(L"[INFO] Done loading texture %d, %s\n",
        texture.textureID, ToWSTR(texture.texturePath).c_str());

    return texture;
}
FileGameConfig TxtGameParser::Parse(const std::string& filename)
{
    FileGameConfig config;
    std::ifstream f(filename);
    std::string line;
    std::string section;

    while (std::getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;

        if (line[0] == '[') {
            section = line;
            continue;
        }

        try {
            if (section == "[SETTINGS]") {
                SettingConfig setting = _ParseSection_SETTING(line);
                if (line.find("start") == 0) config.setting.start = setting.start;
                else if (line.find("width") == 0) config.setting.width = setting.width;
                else if (line.find("height") == 0) config.setting.height = setting.height;
            }
            else if (section == "[SCENES]") {
                SceneConfig scene = _ParseSection_SCENE(line);
                config.scenes.push_back(scene);
            }
            else if (section == "[TEXTURES]") {
                TextureConfig texture = _ParseSection_TEXTURE(line);
                config.textures.push_back(texture);
            }
        }
        catch (const std::exception& e) {
            DebugOut(L"[ERROR] Failed to parse line: %s\n", ToWSTR(line).c_str());
        }
    }

    return config;
}
#pragma endregion
