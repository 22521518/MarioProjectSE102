#pragma once
#include <unordered_map>

#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

#include "debug.h"

using namespace std;

class CSprite;
typedef CSprite* LPSPRITE;

class CSprites
{
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;
	
	CSprites();
public:
	void Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex);
	LPSPRITE Get(int id);
	void Clear();

	static CSprites* GetInstance();
};

