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
#include "PhysicalObject.h"
#include "GameObject.h"
#include "stringUtil.h"
#include "debug.h"

using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

class CPlayScene :
    public CScene
{
protected:
	LPGAMEOBJECT player;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
public:
	CPlayScene(int id, LPCWSTR filePath);
	
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void InitPlayer(LPGAMEOBJECT player);
	
	// Load resource
	int GetAssetSection(string line);
	void LoadAssetDataSection(int section, string line);
	int GetSettingSection(string line);
	void LoadSettingDataSection(int section, string line);

	// Object management
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void PurgeDeletedObjects();
	void Clear();

	LPGAMEOBJECT GetPlayer() const { return player; }

};

typedef CPlayScene* LPPLAYSCENE;

