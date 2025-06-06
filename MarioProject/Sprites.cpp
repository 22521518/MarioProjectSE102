#include <sstream>
#include <stdexcept>
#include "Sprites.h"

CSprites* CSprites::__instance = nullptr;

CSprites* CSprites::GetInstance()
{
	if (__instance == nullptr) __instance = new CSprites();
	return __instance;
}

CSprites::CSprites() { sprites[0] = new CSprite(); }

void CSprites::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	if (id == 0)
	{
		std::ostringstream oss;
		oss << "Cannot add sprite with id: " << id;
		throw runtime_error(oss.str());
		return;
	}

	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	auto it = sprites.find(id);
	if (it != sprites.end())
		return it->second;

	DebugOut(L"Not found sprite id %d in the Sprites\n", id);
	return sprites[id];
}
	
/*
	Clear all loaded sprites
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
	sprites[0] = new CSprite();
}