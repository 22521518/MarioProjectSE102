#include "Textures.h"

CTextures* CTextures::__instance = NULL;


CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}

void CTextures::Add(int id, LPTEXTURE tex)
{
	textures[id] = tex;
}

LPTEXTURE CTextures::Get(unsigned int id)
{
	LPTEXTURE t = textures[id];
	if (t == NULL)
		DebugOut(L"[ERROR] Texture Id %d not found !\n", id);

	return t;
}

void CTextures::Clear()
{
	DebugOut(L"[INFO] Clearing all textures...\n");
	for (auto x : textures)
	{
		LPTEXTURE tex = x.second;
		if (tex != NULL) delete tex;
	}

	textures.clear();
}

CTextures::~CTextures()
{
	Clear();
}