#include "JsonGameParser.h"
#include "GameParserFactory.h"
#include "AssetIDs.h"
#include "Platform.h"
#include "Portal.h"

#pragma region PLAY_SCENE
SpriteConfig JsonGameParser::_ParseSection_SPRITE(const json& rawSprite)
{
	SpriteConfig sprite{};
	try {
		if (!rawSprite.contains("sprite_id") || !rawSprite.contains("texture_id")
			|| !rawSprite.contains("left") || !rawSprite.contains("top") ||
			!rawSprite.contains("right") || !rawSprite.contains("bottom"))
		{
			throw std::runtime_error("Missing required sprite fields.");
		}

		sprite.spriteID = rawSprite["sprite_id"].get<int>();
		sprite.left = rawSprite["left"].get<int>();
		sprite.top = rawSprite["top"].get<int>();
		sprite.right = rawSprite["right"].get<int>();
		sprite.bottom = rawSprite["bottom"].get<int>();
		sprite.textureID = rawSprite["texture_id"].get<int>();
	}
	catch (const std::exception& e)
	{
		DebugOut(L"[ERROR] Exception while parsing sprite: %S\n", e.what());
		throw;  // Rethrow for caller to handle
	}
	return sprite;
}

AnimationConfig JsonGameParser::_ParseSection_ANIMATION(const json& rawAnimation)
{
	AnimationConfig animation{};
	try {
		if (!rawAnimation.contains("animation_id") || !rawAnimation.contains("animation_frames")) {
			throw std::runtime_error("Missing required animation fields.");
		}

		animation.animationID = rawAnimation["animation_id"].get<int>();
		for (auto& ani : rawAnimation["animation_frames"])
		{
			if (!ani.contains("sprite_id") || !ani.contains("frame_time")) {
				throw std::runtime_error("Animation frame missing sprite_id or frame_time.");
			}

			AnimationFrameConfig frame{};
			frame.spriteID = ani["sprite_id"].get<int>();
			frame.frameTime = ani["frame_time"].get<int>();
			animation.animationFrames.push_back(frame);
		}
	}
	catch (const std::exception& e) {
		DebugOut(L"[ERROR] Exception while parsing animation: %S\n", e.what());
		throw;
	}
	return animation;
}

void JsonGameParser::_ParseSection_ASSET(FilePlaySceneConfig& config, const string& assetPath)
{
	try {
		ifstream f(assetPath);
		if (!f.is_open()) {
			throw std::runtime_error("Failed to open asset file: " + assetPath);
		}

		json objectData = json::parse(f);

		if (objectData.contains("sprites") && objectData["sprites"].is_array())
		{
			for (auto& s : objectData["sprites"])
			{
				try {
					config.sprites.push_back(_ParseSection_SPRITE(s));
				} catch (const std::exception& e) {
					DebugOut(L"[ERROR] Skipping sprite: %S\n", e.what());
				}
			}
		}

		if (objectData.contains("animations") && objectData["animations"].is_array())
		{
			for (auto& a : objectData["animations"])
			{
				try {
					config.animations.push_back(_ParseSection_ANIMATION(a));
				} catch (const std::exception& e) {
					DebugOut(L"[ERROR] Skipping animation: %S\n", e.what());
				}
			}
		}
	}
	catch (const std::exception& e) {
		DebugOut(L"[ERROR] Exception in _ParseSection_ASSET: %S\n", e.what());
		throw;
	}
}

GameObjectConfig JsonGameParser::_ParseSection_OBJECT(const json& rawObject)
{
	GameObjectConfig gameObject{};
	try
	{
		if (!rawObject.contains("type") || !rawObject.contains("x") || !rawObject.contains("y")) {
			throw std::runtime_error("GameObject missing required fields: type, x, or y.");
		}

		string type = rawObject["type"];
		gameObject.typeID = stoi(type);
		gameObject.x = rawObject["x"].get<float>();
		gameObject.y = rawObject["y"].get<float>();

		if (rawObject.contains("properties") && rawObject["properties"].is_array()) {
			for (const auto& prop : rawObject["properties"]) {
				if (prop.contains("name") && prop.contains("value")) {
					try 
					{
						string name = prop["name"];
						float value = prop["value"].get<float>();
						//float value = stof(valueStr);
						gameObject.additionalFieldInfo[name] = value;
						//DebugOut(L"    [PROP] %S = %.2f\n", name.c_str(), value);
					}
					catch (const std::exception& e) 
					{
						throw std::runtime_error("Invalid float property value: " + prop["value"]);
					}
				}
				else {
					DebugOut(L"[WARNING] Property missing name or value\n");
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		DebugOut(L"[ERROR] Exception while parsing GameObject: %S\n", e.what());
		throw; // Rethrow to upper layer
	}
	return gameObject;
}


FilePlaySceneConfig JsonGameParser::_ParsePlaySceneFile(const string& filename)
{
	FilePlaySceneConfig config{};

	try {
		ifstream f(filename);
		if (!f.is_open()) {
			throw std::runtime_error("Failed to open scene file: " + filename);
		}
		json objectData = json::parse(f);

		if (objectData.contains("assets") && objectData["assets"].is_array())
		{
			for (const string& assetPath : objectData["assets"])
			{
				try {
					auto parser = GameParserFactory::Create(assetPath);
					parser->_ParseSection_ASSET(config, assetPath);
				}
				catch (const std::exception& e) {
					DebugOut(L"[ERROR] Failed to load asset: %S\n", e.what());
				}
			}
		}

		if (objectData.contains("objects") && objectData["objects"].is_array())
		{
			for (auto& gameObject : objectData["objects"])
			{
				try {
					config.gameObjects.push_back(_ParseSection_OBJECT(gameObject));
				}
				catch (const std::exception& e) {
					DebugOut(L"[ERROR] Skipping game object: %S\n", e.what());
				}
			}
		}
	}
	catch (const std::exception& e) 
	{
		DebugOut(L"[ERROR] JSON parse error in scene file: %S\n", e.what());
	}
	return config;
}
#pragma endregion

#pragma region GAME_STATE
SettingConfig JsonGameParser::_ParseSection_SETTING(const json& settings)
{
	try {
		if (!settings.contains("start") || !settings.contains("width") || !settings.contains("height")) {
			throw std::runtime_error("Missing settings fields");
		}
		SettingConfig config{};
		config.start = settings["start"].get<int>();
		config.width = settings["width"].get<int>();
		config.height = settings["height"].get<int>();
		return config;
	}
	catch (const std::exception& e) {
		DebugOut(L"[ERROR] Failed to parse setting: %S\n", e.what());
		throw;
	}
}

SceneConfig JsonGameParser::_ParseSection_SCENE(const json& scene)
{
	try {
		if (!scene.contains("scene_id") || !scene.contains("scene_path")) {
			throw std::runtime_error("Missing scene fields");
		}
		SceneConfig config;
		config.sceneID = scene["scene_id"].get<int>();
		config.scenePath = scene["scene_path"].get<string>();
		return config;
	}
	catch (const std::exception& e) {
		DebugOut(L"[ERROR] Failed to parse scene: %S\n", e.what());
		throw;
	}
}

TextureConfig JsonGameParser::_ParseSection_TEXTURE(const json& texture)
{
	try {
		if (!texture.contains("texture_id") || !texture.contains("texture_path")) {
			throw std::runtime_error("Missing texture fields");
		}
		TextureConfig config{};
		config.textureID = texture["texture_id"].get<int>();
		config.texturePath = texture["texture_path"].get<string>();
		return config;
	}
	catch (const std::exception& e) {
		DebugOut(L"[ERROR] Failed to parse texture: %S\n", e.what());
		throw;
	}
}

FileGameConfig JsonGameParser::_ParseGameConfigFile(const string& filename)
{
	FileGameConfig config{};
	try {
		ifstream f(filename);
		if (!f.is_open()) {
			throw std::runtime_error("Cannot open game config file: " + filename);
		}

		json gameConfigJson = json::parse(f);

		if (gameConfigJson.contains("settings")) {
			config.setting = _ParseSection_SETTING(gameConfigJson["settings"]);
		}

		if (gameConfigJson.contains("scenes") && gameConfigJson["scenes"].is_array()) {
			for (auto& scene : gameConfigJson["scenes"]) {
				config.scenes.push_back(_ParseSection_SCENE(scene));
			}
		}

		if (gameConfigJson.contains("textures") && gameConfigJson["textures"].is_array()) {
			for (auto& texture : gameConfigJson["textures"]) {
				config.textures.push_back(_ParseSection_TEXTURE(texture));
			}
		}
	}
	catch (const std::exception& e) {
		DebugOut(L"[ERROR] Failed to parse game config: %S\n", e.what());
	}
	return config;
}
#pragma endregion