#include "PlayScene.h"
#include "Mario.h"
#include "AssetIDs.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	this->player = NULL;
	this->keyHandler = new CMarioPlayerKeyHandler(this);
}

void CPlayScene::InitPlayer(LPGAMEOBJECT player) {
	if (this->player != NULL) {
		DebugOut(L"[ERROR] Player object was created before!\n");
		return;
	}
	LPMARIO mario = dynamic_cast<LPMARIO>(player);
	if (mario == NULL) {
		DebugOut(L"[ERROR] Player object is not a Mario object!\n");
		return;
	}
	
	LPMARIOPLAYERKEYHANDLER marioKeyHandler = dynamic_cast<LPMARIOPLAYERKEYHANDLER>(this->keyHandler);
	if (marioKeyHandler == NULL) {
		DebugOut(L"[ERROR] Mario key handler is NULL\n");
		return;
	}
	this->player = mario;
	marioKeyHandler->SetMario(mario);
	this->keyHandler = marioKeyHandler;
	DebugOut(L"[INFO] Player object has been created!\n");
}

#pragma region LOAD_RESOURCE
#pragma region PARSE_SECTION
void CPlayScene::_ParseSection_SPRITES(string line) {
	vector<string> tokens = split(line, "\t");
	
	// file format
	// id, left, top, right, bottom, texture_id
	if (tokens.size() < 6) return;	// skip invalid lines

	// ascii to integer (atoi)
	int id = atoi(tokens[0].c_str());
	int left = atoi(tokens[1].c_str());
	int top = atoi(tokens[2].c_str());
	int right = atoi(tokens[3].c_str());
	int bottom = atoi(tokens[4].c_str());
	int texId = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texId);
	if (tex == NULL) {
		return;
	}

	CSprites::GetInstance()->Add(id, left, top, right, bottom, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line) {
	vector<string> tokens = split(line, "\t");
	
	// ani_id, sprite1_id, time1, ..., spriteN_id, timeN
	// an animation must have at least 1 frame and 1 frame time
	if (tokens.size() < 3) return;

	LPANIMATION ani = new CAnimation();

	int aniId = atoi(tokens[0].c_str());

	for (int i = 1; i < tokens.size(); i += 2) // why i+=2 ? sprite_id | frame_time
	{
		int spriteId = atoi(tokens[i].c_str());
		int frameTime = atoi(tokens[i + 1].c_str());
		ani->Add(spriteId, frameTime);
	}

	CAnimations::GetInstance()->Add(aniId, ani);
}

void CPlayScene::_ParseSection_ASSETS(string line) {
	vector<string> tokens = split(line, "\t");

	// name.txt - file asset (file format)
	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_OBJECTS(string line) {
	vector<string> tokens = split(line, "\t");

	// an object set must have at least id, x, y
	// type	x	y	extra_settings per object type
	// type: 0 = Mario, 1 = Brick, 2 = Goomba, 3 = Koopas
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	LPGAMEOBJECT obj = CGameObject::CreateGameObject(object_type, x, y, tokens, player);

	if (obj == NULL) {
		DebugOut(L"[ERROR] Failed to create player object!\n");
		return;
	}

	if (object_type == OBJECT_TYPE_MARIO) {
		this->InitPlayer(obj);
	}

	obj->SetPosition(x, y);
	objects.push_back(obj);
}
#pragma endregion

#pragma region LOAD_ASSETS
int CPlayScene::GetAssetSection(string line) {
	if (line == "[SPRITES]") return ASSETS_SECTION_SPRITES;
	if (line == "[ANIMATIONS]") return ASSETS_SECTION_ANIMATIONS;
	if (line[0] == '[') return SCENE_SECTION_UNKNOWN;
	return -1000;
}

void CPlayScene::LoadAssetDataSection(int section, string line)
{
	switch (section) {
	case ASSETS_SECTION_SPRITES:
		_ParseSection_SPRITES(line); break;
	case ASSETS_SECTION_ANIMATIONS:
		_ParseSection_ANIMATIONS(line); break;
	}
}

void CPlayScene::LoadAssets(LPCWSTR assetFile) {
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);
	ifstream f;
	f.open(assetFile);

	if (!f.is_open()) {
		DebugOut(L"[ERROR] Failed to open file: %s\n", assetFile);
		return;
	}

	int section = ASSETS_SECTION_UNKNOWN;
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);
		if (line[0] == '#') continue; // skip comment lines

		if (GetAssetSection(line) >= -1) {
			section = GetAssetSection(line);
			continue;
		}

		LoadAssetDataSection(section, line);
	}
	f.close();
	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}
#pragma endregion

#pragma region LOAD_SETTING
int CPlayScene::GetSettingSection(string line) {
	if (line == "[ASSETS]") return SCENE_SECTION_ASSETS;
	if (line == "[OBJECTS]") return SCENE_SECTION_OBJECTS;
	if (line[0] == '[') return SCENE_SECTION_UNKNOWN;
	return -1000;
}

void CPlayScene::LoadSettingDataSection(int section, string line)
{
	switch (section) {
	case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
	case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
	}
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (GetSettingSection(line) >= -1) {
			section = GetSettingSection(line);
			continue;
		}

		LoadSettingDataSection(section, line);
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}
#pragma endregion
#pragma endregion

#pragma region SCENE_MANAGEMENT
void CPlayScene::Update(DWORD dt)
{
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPPHYSICALOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<LPPHYSICALOBJECT>(objects[i])) {
			coObjects.push_back(dynamic_cast<LPPHYSICALOBJECT>(objects[i]));
		}
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<LPPHYSICALOBJECT>(objects[i])) {
			((LPPHYSICALOBJECT)objects[i])->Update(dt, &coObjects);
		}
	}

	if (player == NULL) 
	{
		DebugOut(L"[ERROR] Player object is NULL\n");
		exit(0);
		return;
	};

	float cx, cy;
	player->GetPosition(cx, cy);
	cx += -CGame::GetInstance()->GetBackBufferWidth() / 2;
	cy += -CGame::GetInstance()->GetBackBufferHeight() / 2;
	cx = cx < 0 ? 0 : cx;

	//CGame::GetInstance()->SetCamPos(cx, 0);
	CGame::GetInstance()->SetCamPos(cx, cy);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	// Beside objects, we need to clean up sprites, animations and te
	CSprites::GetInstance()->Clear();
	//CTextures::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}
#pragma endregion

#pragma region OBJECT_MANAGEMENT
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

void CPlayScene::PurgeDeletedObjects() {
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++) {
		LPGAMEOBJECT currentObj = *it;
		if (currentObj->IsDeleted()) {
			delete currentObj;
			*it = NULL;
		}
	}

	objects.erase(remove_if(
		objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }
#pragma endregion