#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Scene.h"
#include "Game.h"
#include "Animations.h"
#include "Sprites.h"
#include "MarioPlayerKeyHandler.h"
#include "GameObject.h"
#include "stringUtil.h"
#include "debug.h"
#include "HUDContainer.h"

#include "GameParser.h"
#include "FileConfig.h"
using namespace std;

constexpr int SCENE_SECTION_UNKNOWN = -1;
constexpr int SCENE_SECTION_ASSETS = 1;
constexpr int SCENE_SECTION_OBJECTS = 2;

constexpr int ASSETS_SECTION_UNKNOWN = -1;
constexpr int ASSETS_SECTION_SPRITES = 1;
constexpr int ASSETS_SECTION_ANIMATIONS = 2;

constexpr int MAX_SCENE_LINE = 1024;

class CPhysicalObject; typedef CPhysicalObject* LPPHYSICALOBJECT;
class CHUDContainer;  typedef CHUDContainer* LPHUDCONTAINER;

class CPlayScene :
    public CScene
{
private:
	float camBoundTop, camBoundBot, camBoundLeft, camBoundRight = 0;

	UINT time_remaining = 300;
	UINT world = 1;
	LPHUDCONTAINER hud;
	ULONGLONG time_start;

protected:
	static LPGAMEOBJECT mainPlayer;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> decors;
	vector<LPGAMEOBJECT> colorBg;

	void _ParseSection_SPRITES(const vector<SpriteConfig>& sprites);
	void _ParseSection_ANIMATIONS(const vector<AnimationConfig>& animations);
	void _ParseSection_OBJECTS(const vector<GameObjectConfig>& gameObjects);
	void LoadAssets(LPCWSTR assetFile);
public:
	CPlayScene(int id, LPCWSTR filePath);
	
	void Load() override;
	void Update(DWORD dt) override;
	void UpdateCamera(DWORD dt) override;
	void Render() override;
	void Unload() override;
	void Reload() override;

	void UpdateMovingCamera(DWORD dt);
	void ReloadMovingCameraScene();

	void InitPlayer(LPGAMEOBJECT player);
	void DeletePlayer();

	// Object management
	void CheckObjectInPlayerArea(vector<LPPHYSICALOBJECT>* coObjects);
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void PurgeDeletedObjects();
	void Clear();

	~CPlayScene() {
		if (hud != nullptr) { delete hud; hud = nullptr; }
	}
	static LPGAMEOBJECT GetPlayer();

};

typedef CPlayScene* LPPLAYSCENE;

