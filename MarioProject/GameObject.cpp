#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"
#include "Brick.h"
#include "Coin.h"
#include "CloudPlatform.h"
#include "Portal.h"

#include "RedKoopa.h"

#include "AssetIDs.h"

using namespace std;

CGameObject* CGameObject::CreateGameObject(int object_type, float x, float y, vector<string> tokens) {
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO: return new CMario(x, y);
	case OBJECT_TYPE_GOOMBA: return new CGoomba(x, y);
	case OBJECT_TYPE_BRICK: return new CBrick(x, y);
	case OBJECT_TYPE_COIN: return new CCoin(x, y);
	case OBJECT_TYPE_RED_KPOOPA: return new CRedKoopa(x, y);
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		return new CCloudPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		return new CPortal(x, y, r, b, scene_id);

	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return NULL;
	}
}