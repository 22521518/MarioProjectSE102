#pragma once
#include "PlayScene.h"

class GameObject;
typedef GameObject* LPGAMEOBJECT;

class CBonusScene : public CPlayScene
{
public:
	CBonusScene(int id, LPCWSTR filePath, LPGAMEOBJECT player) : CPlayScene(id, filePath) { this->InitPlayer(player); };
};