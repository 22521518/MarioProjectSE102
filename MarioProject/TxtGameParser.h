#pragma once
#include "GameParser.h"
#include <fstream>
#include <sstream>

#define MAX_LINE 1024

class TxtGameParser : public IGameParser {
private:
public:
	// Game state
	SettingConfig    _ParseSection_SETTING(const std::string& line);
	SceneConfig      _ParseSection_SCENE(const std::string& line);
	TextureConfig    _ParseSection_TEXTURE(const std::string& line);
	FileGameConfig Parse(const std::string& filename) override;
};