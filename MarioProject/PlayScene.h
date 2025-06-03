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
class CPlayScene :
    public CScene
{
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
	
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void InitPlayer(LPGAMEOBJECT player);

	// Object management
	void CheckObjectInPlayerArea(vector<LPPHYSICALOBJECT>* coObjects);
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void PurgeDeletedObjects();
	void Clear();

	static LPGAMEOBJECT GetPlayer();

};

typedef CPlayScene* LPPLAYSCENE;

