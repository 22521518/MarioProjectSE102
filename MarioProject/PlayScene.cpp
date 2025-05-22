#include "PlayScene.h"
#include "GameParserFactory.h"
#include "Mario.h"
#include "AssetIDs.h"

using namespace std;

#pragma region PLAYSCENE_CONSTRUCTOR
CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
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
#pragma endregion

#pragma region LOAD_RESOURCE

#pragma region CUSTOM_PARSE_SECTION
void CPlayScene::_ParseSection_SPRITES(const vector<SpriteConfig>& sprites)  
{  
   for (const SpriteConfig& sprite : sprites)  
   {  
       LPTEXTURE tex = CTextures::GetInstance()->Get(sprite.textureID);  
       if (tex == NULL) continue;  
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
		LPGAMEOBJECT obj = CGameObject::CreateGameObject(gameObject.typeID, gameObject.x, gameObject.y, gameObject.additionalFieldInfo, player);

		//if (!gameObject.typeID) return;

		if (obj == NULL) {
			DebugOut(L"[ERROR] Failed to create player object!\n");
			return;
		}

		if (gameObject.typeID == OBJECT_TYPE_MARIO) {
			this->InitPlayer(obj);
		}

		obj->SetPosition(gameObject.x, gameObject.y);
		objects.push_back(obj);
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
	if (player == NULL)
	{
		DebugOut(L"[ERROR] Player object is NULL\n");
		exit(0);
		return;
	};

	float screenWidth = static_cast<float>(CGame::GetInstance()->GetBackBufferWidth());
	float screenHeight = static_cast<float>(CGame::GetInstance()->GetBackBufferHeight());
	float px, py;
	player->GetPosition(px, py);

	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPPHYSICALOBJECT> coObjects;
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
                coObjects.push_back(phys);
        } else if (obj != player && !obj->IsRemovable() && !obj->IsVisible()) {
            obj->ResetState();
        }
    }


	for (auto phys : coObjects) {
		phys->Update(dt, &coObjects);
	}

	player->GetPosition(px, py);
	//player->SetPosition(px < 0 ? 0 : px, py);

	px += -screenWidth / 2;
	py += -screenHeight / 2;
	px = max(0, px);

	//CGame::GetInstance()->SetCamPos(px, 0);
	CGame::GetInstance()->SetCamPos(px, py);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() || !objects[i]->IsVisible()) continue;
		if (objects[i] == this->player) continue;
		objects[i]->Render();
	}
	this->player->Render();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

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
		delete (*it);
	}
	objects.clear();
}

void CPlayScene::PurgeDeletedObjects() {
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++) {
		LPGAMEOBJECT currentObj = *it;
		if (CBaseObject::IsDeleted(currentObj)) {
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