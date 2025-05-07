#pragma once
#include "GameParser.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class JsonGameParser :
    public IGameParser
{
public:
	SpriteConfig _ParseSection_SPRITE(const json& rawSprite);
	AnimationConfig _ParseSection_ANIMATION(const json& rawAnimation);
	void _ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath) override;
	GameObjectConfig _ParseSection_OBJECT(const json& rawObject);
	FilePlaySceneConfig _ParsePlaySceneFile(const string& filename) override;

	SettingConfig    _ParseSection_SETTING(const json& settings);
	SceneConfig      _ParseSection_SCENE(const json& scene);
	TextureConfig    _ParseSection_TEXTURE(const json& texture);
    FileGameConfig _ParseGameConfigFile(const string& filename) override;
};

