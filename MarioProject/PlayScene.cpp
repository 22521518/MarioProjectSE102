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
	this->time_start = GetTickCount64();
	this->keyHandler = new CMarioPlayerKeyHandler(this);
	this->hud = new CHUDContainer(&time_remaining, &CMario::scores, &CMario::lives, &CMario::coins, &world);

	switch (id) {
	case 1000:
	{
		camBoundLeft = CAM_BOUND_LEFT; 
		camBoundRight = 16.f * 175;
		camBoundTop = CAM_BOUND_TOP;
		camBoundBot = CAM_BOUND_BOTTOM + 20;
		break;
	}
	case 1001:
	{
		camBoundLeft = 16.f * 123; 
		camBoundRight = camBoundRight + 16.f * 32;
		camBoundTop = CAM_BOUND_TOP_BONUS;
		camBoundBot = CAM_BOUND_BOTTOM_BONUS;
		break;
	}
	case 4000:
	{
		camBoundLeft = CAM_BOUND_LEFT;
		camBoundRight = 128 * 16.f;
		camBoundTop = CAM_BOUND_TOP + 16.f * 2;
		camBoundBot = 224.f + 16.f * 2;
		break;
	}
	case 4001:
	{
		camBoundLeft = 129 * 16.f;
		camBoundRight = camBoundLeft + 16 * 31.f;
		camBoundTop = CAM_BOUND_TOP + 16.f * 2;
		camBoundBot = 224.f + 16.f * 2;
		break;
	}
	default: 
	{
		camBoundLeft = CAM_BOUND_LEFT;
		camBoundRight = 16 * 176;
		camBoundTop = CAM_BOUND_TOP;
		camBoundBot = CAM_BOUND_BOTTOM;
		break;
	}
	}
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
		DebugOut(L"[INFO] Player object has been inserted, lives: %u!\n", CMario::lives);
	}
}
void CPlayScene::DeletePlayer()
{
	delete CPlayScene::mainPlayer;
	CPlayScene::mainPlayer = nullptr;
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
			dynamic_cast<LPMARIO>(CPlayScene::mainPlayer)->Init(gameObject.x, gameObject.y);
			continue;
		}
		obj->SetPosition(gameObject.x, gameObject.y);

		if (gameObject.typeID == OBJECT_TYPE_GAME_BACKGROUND_COLOR_9_SPRITE) colorBg.push_back(obj);
		else if (dynamic_cast<LPGAMEDECOR>(obj)) decors.push_back(obj);
		else objects.push_back(obj);
	}
}
void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
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
	static bool isReloading = false;

	if (isReloading) {
		return; // Skip update if already reloading
	}

	time_remaining = static_cast<UINT>(MAX_TIME_SCENE - (GetTickCount64() - time_start)) / 1000;  

	LPMARIO mainMario = dynamic_cast<LPMARIO>(CPlayScene::mainPlayer);

	if (CPlayScene::mainPlayer == nullptr || !mainMario)
	{
		DebugOut(L"[ERROR] Player object is nullptr\n");
		isReloading = true;
		Reload();
		isReloading = false;
		return;
	}
	else if (mainMario->IsMarioDieAndReload())
	{
		if (CMario::lives - 1 > CMario::lives)
		{
			DeletePlayer();
			Unload();
			CGame::GetInstance()->PlayFromStart();
			CMario::OnGameReset();
		}
		else 
		{
		CMario::lives = CMario::lives - 1 > CMario::lives ? 0 : CMario::lives - 1;
			isReloading = true;
			Reload();
			isReloading = false;
		}
		return;
	}
	else {
		if (mainMario->IsPipeMoving() || CGame::GetInstance()->IsTransition()) return;

		float px, py;
		CPlayScene::mainPlayer->GetPosition(px, py);
		float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());

		// exclude the bonus
		if (py > camBoundBot + 20 + screenHeight) {
			mainMario->SetDie();
		}

		// TO-DO: This is a "dirty" way, need a more organized way  
		vector<LPPHYSICALOBJECT> coObjects;
		coObjects.push_back(mainMario);
		CheckObjectInPlayerArea(&coObjects);

		for (auto phys : coObjects) {
			try {
				//if (dynamic_cast<LPPHYSICALOBJECT>(phys)) phys->Update(dt, &coObjects);
				if (phys)
				{
					auto physCast = dynamic_cast<LPPHYSICALOBJECT>(phys);
					if (physCast) {
						physCast->Update(dt, &coObjects);
					}
				}
			}
			catch (const std::exception& e) {
				DebugOutObjectClassName(phys);
				DebugOut(L"[ERROR] Exception caught: %s\n", e.what());
			}
		}
		UpdateCamera(dt);
		coObjects.clear();
	}
	PurgeDeletedObjects();
}

void CPlayScene::UpdateCamera(DWORD dt)
{
	if (id == 4000) 
	{
		UpdateMovingCamera(dt);
		return;
	}

	float screenWidth = static_cast<float>(CGame::GetInstance()->GetBackBufferWidth());
	float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());
	float px, py;
	CPlayScene::mainPlayer->GetPosition(px, py);
	CPlayScene::mainPlayer->SetPosition(max(camBoundLeft + 10.0f, px), py);
	LPMARIO mario = dynamic_cast<LPMARIO>(CPlayScene::mainPlayer);

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	if (((mario->GetPowerPStart() > 0) || (mario->CanFly() && mario->IsFlapping() && py > cy + screenWidth / 2)) ||
		(cy < camBoundBot + 60))
	{
		py += -screenHeight / 2;
	}
	
	py = max(camBoundTop, py);
	py = min(camBoundBot, py);

	px += -screenWidth / 2;
	px = max(camBoundLeft, px);
	float cam_bound_right = camBoundRight - screenWidth;
	px = min(px, cam_bound_right);

	//DebugOutTitle(L"top: %f, bot: %f\n", px, py);

	hud->SetPosition(px, py);
	CGame::GetInstance()->SetCamPos(px, py);
}

void CPlayScene::CheckObjectInPlayerArea(vector<LPPHYSICALOBJECT>* coObjects) {
	float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());
	float px, py;
	float screenWidth = static_cast<float>(CGame::GetInstance()->GetBackBufferWidth());
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

	if (CPlayScene::mainPlayer)
	{
		LPMARIO mr = dynamic_cast<LPMARIO>(CPlayScene::mainPlayer);
		if (mr && (!mr->IsPipeMoving() && !CGame::GetInstance()->IsTransition())) mr->Render();
	}
	hud->Render();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}

	for (int i = 0; i < decors.size(); i++)
	{
		delete decors[i];
	}

	for (int i = 0; i < colorBg.size(); i++)
	{
		delete colorBg[i];
	}

	objects.clear();
	decors.clear();
	colorBg.clear();

	// Beside objects, we need to clean up sprites, animations
	//CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}
void CPlayScene::Reload()
{
	if (id == 4000) {

		ReloadMovingCameraScene();
		return;
	}

	static bool isCurrentlyReloading = false;
	if (isCurrentlyReloading) {
		DebugOut(L"[WARNING] Reload already in progress, skipping duplicate reload request\n");
		return;
	}
	isCurrentlyReloading = true;

	time_start = GetTickCount64();
	Clear();
	DeletePlayer();
	DebugOut(L"[INFO] Mario existed: %d, Scene %d reloaded!\n", id, CPlayScene::mainPlayer != nullptr);
	Load();

	isCurrentlyReloading = false;
}
void CPlayScene::UpdateMovingCamera(DWORD dt)
{
	float screenWidth = static_cast<float>(CGame::GetInstance()->GetBackBufferWidth());
	float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());

	// Base autoscroll speed (adjust according to level needs)
	const float BASE_SCROLL_SPEED = 0.08f * 0.15;
	float scrollSpeed = BASE_SCROLL_SPEED;

	// Get current camera position
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	// Calculate new camera position
	float new_cx = cx + (scrollSpeed * dt);

	DebugOutTitle(L"x: %f, y: %f", cx, cy);
	// Apply camera bounds
	float cam_bound_right = camBoundRight - screenWidth;
	new_cx = max(camBoundLeft, min(new_cx, cam_bound_right));
	
	// Handle player position relative to scrolling
	float px, py;
	CPlayScene::mainPlayer->GetPosition(px, py);

	// Push player right if camera moves beyond 
	float pushAmountX = 0, pushAmountY = 0;
	if (px < new_cx + HORIZONTAL_DEADZONE)
	{
		float targetX = new_cx + HORIZONTAL_DEADZONE;
		pushAmountX = (targetX - px) ;
	}
	// Never push left in autoscroll levels - let player move ahead freely

	// Vertical containment (prevent falling below camera)
	float verticalThreshold = cy + VERTICAL_DEADZONE;
	if (py < verticalThreshold)
	{
		pushAmountY = (verticalThreshold - py) ;
	}

	CPlayScene::mainPlayer->SetPosition(px + pushAmountX, py + pushAmountY);

	// Update camera position
	CGame::GetInstance()->SetCamPos(new_cx, cy);

	// Maintain vertical camera logic from original UpdateCamera
	py = max(camBoundTop, py);
	py = min(camBoundBot, py);

	// Update HUD position
	hud->SetPosition(new_cx, py);
	CGame::GetInstance()->SetCamPos(new_cx, py);
}

void CPlayScene::ReloadMovingCameraScene()
{
	static bool isCurrentlyReloading = false;
	if (isCurrentlyReloading) {
		DebugOut(L"[WARNING] Moving camera reload already in progress\n");
		return;
	}
	isCurrentlyReloading = true;
		
	float initialCamX = camBoundLeft;
	float initialCamY = (camBoundTop + camBoundBot) / 2;  // Center vertically
	CGame::GetInstance()->SetCamPos(initialCamX, initialCamY);
	hud->SetPosition(initialCamX, initialCamY);

	// Standard reload sequence
	Clear();
	DeletePlayer();
	Load();  // Reloads level layout and entities
	DebugOut(L"[INFO] Autoscroll scene %d reloaded (Camera X: %f)\n", id, initialCamX);
	isCurrentlyReloading = false;
}

#pragma endregion

#pragma region OBJECT_MANAGEMENT
void CPlayScene::Clear()
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}

	for (auto it = decors.begin(); it != decors.end(); it++)
	{
		delete (*it);
	}

	for (auto it = colorBg.begin(); it != colorBg.end(); it++)
	{
		delete (*it);
	}

	objects.clear();
	decors.clear();
	colorBg.clear();
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