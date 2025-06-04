#include "PlayScene.h"
#include "GameParserFactory.h"
#include "Mario.h"
#include "AssetIDs.h"
#include"debug.h"
#include "GameDecor.h"
#include "PhysicalObject.h"
#include "HUDContainer.h"
#include "CameraConfig.h"

using namespace std;

LPGAMEOBJECT CPlayScene::mainPlayer = nullptr;
LPGAMEOBJECT CPlayScene::GetPlayer() { return mainPlayer; }

#pragma region PLAYSCENE_CONSTRUCTOR
CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	this->keyHandler = new CMarioPlayerKeyHandler(this);
	this->hud = new CHUDContainer(&time_remaining, &scores, &lives, &coins);
}

void CPlayScene::InitPlayer(LPGAMEOBJECT player) {
	LPMARIO mario = dynamic_cast<LPMARIO>(player);
	if (mario == nullptr) {
		DebugOut(L"[ERROR] Player object is not a Mario object!\n");
		return;
	}

	LPMARIOPLAYERKEYHANDLER marioKeyHandler = dynamic_cast<LPMARIOPLAYERKEYHANDLER>(this->keyHandler);
	if (marioKeyHandler == nullptr) {
		DebugOut(L"[ERROR] Mario key handler is nullptr\n");
		return;
	}

	if (CPlayScene::mainPlayer == nullptr) {
		DebugOut(L"[INFO] Player object has been created!\n");
		CPlayScene::mainPlayer = mario;
	}

	if (CPlayScene::mainPlayer != nullptr) {
		marioKeyHandler->SetMario(dynamic_cast<LPMARIO>(CPlayScene::mainPlayer));
		this->keyHandler = marioKeyHandler;
		DebugOut(L"[INFO] Player object has been created!\n");
	}
}
#pragma endregion

#pragma region LOAD_RESOURCE

#pragma region CUSTOM_PARSE_SECTION
void CPlayScene::_ParseSection_SPRITES(const vector<SpriteConfig>& sprites)
{
	for (const SpriteConfig& sprite : sprites)
	{
		LPTEXTURE tex = CTextures::GetInstance()->Get(sprite.textureID);
		if (tex == nullptr) continue;
		CSprites::GetInstance()->Add(sprite.spriteID, sprite.left, sprite.top, sprite.right, sprite.bottom, tex);
	}
}

void CPlayScene::_ParseSection_ANIMATIONS(const vector<AnimationConfig>& animations)
{
	for (const AnimationConfig animation : animations)
	{
		LPANIMATION ani = new CAnimation();
		for (const AnimationFrameConfig aniFrame : animation.animationFrames)
		{
			ani->Add(aniFrame.spriteID, aniFrame.frameTime);
		}
		CAnimations::GetInstance()->Add(animation.animationID, ani);
	}
}

void CPlayScene::_ParseSection_OBJECTS(const vector<GameObjectConfig>& gameObjects)
{
	for (const GameObjectConfig gameObject : gameObjects)
	{
		LPGAMEOBJECT obj = CGameObject::CreateGameObject(gameObject.typeID, gameObject.x, gameObject.y, gameObject.additionalFieldInfo, CPlayScene::mainPlayer);

		if (obj == nullptr) {
			DebugOut(L"[ERROR] Failed to create player object!\n");
			continue;
		}

		if (gameObject.typeID == OBJECT_TYPE_MARIO) {
			this->InitPlayer(obj);
			CPlayScene::mainPlayer->SetPosition(gameObject.x, gameObject.y);
			continue;
		}

		obj->SetPosition(gameObject.x, gameObject.y);

		if (gameObject.typeID == OBJECT_TYPE_GAME_BACKGROUND_COLOR_9_SPRITE) colorBg.push_back(obj);
		else if (dynamic_cast<LPGAMEDECOR>(obj)) decors.push_back(obj);
		else objects.push_back(obj);
	}
}
#pragma endregion

#pragma region LOAD_SETTING
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	auto parser = GameParserFactory::Create(WSTRToString(sceneFilePath));
	FilePlaySceneConfig playSceneData = parser->_ParsePlaySceneFile(WSTRToString(sceneFilePath));

	_ParseSection_SPRITES(playSceneData.sprites);
	_ParseSection_ANIMATIONS(playSceneData.animations);
	_ParseSection_OBJECTS(playSceneData.gameObjects);

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}
#pragma endregion
#pragma endregion

#pragma region SCENE_MANAGEMENT
void CPlayScene::Update(DWORD dt)
{
	if (CPlayScene::mainPlayer == nullptr)
	{
		DebugOut(L"[ERROR] Player object is nullptr\n");
		exit(0);
		return;
	};

	// TO-DO: This is a "dirty" way, need a more organized way 
	LPPHYSICALOBJECT physMain = dynamic_cast<LPPHYSICALOBJECT>(CPlayScene::mainPlayer);
	vector<LPPHYSICALOBJECT> coObjects;
	coObjects.push_back(physMain);
	CheckObjectInPlayerArea(&coObjects);
	
	for (auto phys : coObjects) {
		phys->Update(dt, &coObjects);
	}
	UpdateCamera(dt);
	PurgeDeletedObjects();
}

void CPlayScene::UpdateCamera(DWORD dt)
{
	float screenWidth = static_cast<float>(CGame::GetInstance()->GetBackBufferWidth());
	float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());
	float px, py;
	CPlayScene::mainPlayer->GetPosition(px, py);
	CPlayScene::mainPlayer->SetPosition(max(CAM_BOUND_LEFT + 10.0f, px), py);

	LPMARIO mario = dynamic_cast<LPMARIO>(CPlayScene::mainPlayer);

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	if (((mario->GetPowerPStart() > 0) || (mario->CanFly() && mario->IsFlapping())) ||
		(cy < CAM_BOUND_BOTTOM))
	{
		py += -screenHeight / 2;
	}
	else {
		py = max(CAM_BOUND_TOP, py);
	}

	py = min(CAM_BOUND_BOTTOM, py);
	px += -screenWidth / 2;
	px = max(CAM_BOUND_LEFT, px);

	hud->SetPosition(px, py);
	CGame::GetInstance()->SetCamPos(px, py);
}

void CPlayScene::CheckObjectInPlayerArea(vector<LPPHYSICALOBJECT>* coObjects) {
	float screenWidth = static_cast<float>(CGame::GetInstance()->GetBackBufferWidth());
	float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());
	float px, py;
	CPlayScene::mainPlayer->GetPosition(px, py);
	for (auto obj : objects) {
		float objLeft, objTop, objRight, objBottom;
		obj->GetBoundingBox(objLeft, objTop, objRight, objBottom);

		float padX = screenWidth;
		float padY = screenHeight;
		bool inX = objRight >= px - padX && objLeft <= px + padX;
		bool inY = objBottom >= py - padY && objTop <= py + padY;

		if (inX && inY)
		{
			obj->MakeAlive();
			obj->MakeVisible();
		}
		else
		{
			obj->MakeInvisible();
			obj->ResetState();
		}

		if (!obj->IsDeleted() && obj->IsVisible()) {
			if (auto phys = dynamic_cast<LPPHYSICALOBJECT>(obj))
				coObjects->push_back(phys);
		}
		else if (obj != CPlayScene::mainPlayer && !obj->IsRemovable() && !obj->IsVisible()) {
			obj->ResetState();
		}
	}
}

void CPlayScene::Render()
{
	for (size_t i = 0; i < colorBg.size(); i++) colorBg[i]->Render();
	for (size_t i = 0; i < decors.size(); i++) decors[i]->Render();
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() || !objects[i]->IsVisible()) continue;
		objects[i]->Render();
	}
	CPlayScene::mainPlayer->Render();
	hud->Render();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] == CPlayScene::mainPlayer) continue;
		delete objects[i];
	}

	objects.clear();
	delete hud;

	// Beside objects, we need to clean up sprites, animations
	CSprites::GetInstance()->Clear();
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
		if (*it == CPlayScene::mainPlayer) continue;
		delete (*it);
	}
	objects.clear();
}

void CPlayScene::PurgeDeletedObjects() {
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++) {
		LPGAMEOBJECT currentObj = *it;
		if (CBaseObject::IsDeleted(currentObj) && currentObj != CPlayScene::mainPlayer) {
			delete currentObj;
			*it = nullptr;
		}
	}

	objects.erase(remove_if(
		objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == nullptr; }
#pragma endregion