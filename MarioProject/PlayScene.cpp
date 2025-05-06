#include "PlayScene.h"
#include "Mario.h"
#include "AssetIDs.h"

using namespace std;

#pragma region PLAYSCENE_CONSTRUCTOR
CPlayScene::CPlayScene(int id, LPCWSTR filePath, IGameParser* gameParser) : CScene(id, filePath)
{
	this->gameParser = gameParser;
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
void CPlayScene::_ParseSection_SPRITES(vector<SpriteConfig> sprites)
{
	for (const SpriteConfig sprite : sprites)
	{
		LPTEXTURE tex = CTextures::GetInstance()->Get(sprite.textureID);
		if (tex == NULL) continue;
		CSprites::GetInstance()->Add(sprite.spriteID, sprite.left, sprite.top, sprite.right, sprite.bottom, tex);
	}
}

void CPlayScene::_ParseSection_ANIMATIONS(vector<AnimationConfig> animations)
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

void CPlayScene::_ParseSection_OBJECTS(vector<GameObjectConfig> gameObjects)
{
	for (const GameObjectConfig gameObject : gameObjects)
	{
		LPGAMEOBJECT obj = CGameObject::CreateGameObject(gameObject.typeID, gameObject.x, gameObject.y, gameObject.additionalFieldInfo, player);

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

	FilePlaySceneConfig playSceneData = this->gameParser->_ParsePlaySceneFile(WSTRToString(sceneFilePath));
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