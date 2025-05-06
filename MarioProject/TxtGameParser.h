#pragma once
#include "GameParser.h"

#define MAX_LINE 1024

using namespace std;

class TxtGameParser : public IGameParser {
private:
public:
	// Play Scene
	SpriteConfig _ParseSection_SPRITE(const string& line);
	AnimationConfig _ParseSection_ANIMATION(const string& line);
	void _ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath);
	GameObjectConfig _ParseSection_OBJECT(const string& line);
	FilePlaySceneConfig _ParsePlaySceneFile(const string& filename) override;


	// Game state
	SettingConfig    _ParseSection_SETTING(const string& line);
	SceneConfig      _ParseSection_SCENE(const string& line);
	TextureConfig    _ParseSection_TEXTURE(const string& line);
	FileGameConfig _ParseGameConfigFile(const string& filename) override;
};