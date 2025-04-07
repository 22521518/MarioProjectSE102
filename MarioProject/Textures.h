#pragma once
#include <unordered_map>
#include <d3dx10.h>

#include "Texture.h"
#include "Game.h"
#include "debug.h"

using namespace std;

class CTextures
{
	static CTextures* __instance;
	unordered_map<int, LPTEXTURE> textures;

	CTextures() {};
public:
	void Add(int id, LPCWSTR filePath);
	void Add(int id, LPTEXTURE tex);
	LPTEXTURE Get(unsigned int id);
	void Clear();
	~CTextures();
	static CTextures* GetInstance();
};