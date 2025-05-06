#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"
#include "Brick.h"
#include "Coin.h"
#include "CloudPlatform.h"
#include "Portal.h"

#include "BrickSuperItem.h"
#include "OneUpMushroom.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "DestroyableBrick.h"
#include "RedKoopa.h"
#include "RedKoopaParatroopa.h"
#include "GreenKoopa.h"
#include "GreenKoopaParatroopa.h"

#include "PlantGreenPiranha.h"
#include "PlantGreenVenusFire.h"
#include "PlantRedVenusFire.h"
#include "BlockQ.h"
#include "BrickStateIDs.h"

#include "AssetIDs.h"

using namespace std;

CGameObject* CGameObject::CreateGameObject(int object_type, float x, float y, unordered_map<string, float> additionalFieldInfo, LPGAMEOBJECT player) {
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO: return new CMario(x, y);
	case OBJECT_TYPE_GOOMBA: return new CGoomba(x, y);
	case OBJECT_TYPE_BRICK: return new CBrick(x, y);
	case OBJECT_TYPE_DESTROYABLE_BRICK: return new CDestroyableBrick(x, y);
	case OBJECT_TYPE_COIN: return new CCoin(x, y);
	case OBJECT_TYPE_ITEM_BRICK: {
		LPMARIO mario = dynamic_cast<LPMARIO>(player);
		if (mario) return new CBrickSuperItem(mario, x, y);
		break;
	}
	case OBJECT_TYPE_SUPER_LEAF_ITEM: return new CSuperLeaf(x, y);
	case OBJECT_TYPE_SUPER_MUSHROOM_ITEM: return new CSuperMushroom(x, y);
	case OBJECT_TYPE_ONE_UP_MUSHROOM_ITEM: return new COneUpMushroom(x, y);
	case OBJECT_TYPE_RED_KPOOPA: return new CRedKoopa(x, y);
	case OBJECT_TYPE_RED_KPOOPA_TROOPA: return new CRedKoopaParatroopa(x, y);
	case OBJECT_TYPE_GREEN_KPOOPA_TROOPA: return new CGreenKoopaParatroopa(x, y);
	case OBJECT_TYPE_GREEN_KPOOPA: return new CGreenKoopa(x, y);
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = additionalFieldInfo["cell_width"];
		float cell_height = additionalFieldInfo["cell_height"];
		int length = additionalFieldInfo["length"];
		int sprite_begin = additionalFieldInfo["sprite_begin"];
		int sprite_middle = additionalFieldInfo["sprite_middle"];
		int sprite_end = additionalFieldInfo["sprite_end"];

		return new CCloudPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = additionalFieldInfo["r"];
		float b = additionalFieldInfo["b"];
		int scene_id = additionalFieldInfo["scene_id"];
		return new CPortal(x, y, r, b, scene_id);

	}
	case OBJECT_TYPE_PLANT_GP: return new CPlantGreenPiranha(player, x, y);
	case OBJECT_TYPE_PLANT_GVF: return new CPlantGreenVenusFire(player, x, y);
	case OBJECT_TYPE_PLANT_RVF: return new CPlantRedVenusFire(player, x, y);
	case OBJECT_TYPE_BLOCK_Q_COIN: return new CBlockQ(player, BRICK_STATE_COIN, x, y);
	case OBJECT_TYPE_BLOCK_Q_ITEM: return new CBlockQ(player, BRICK_STATE_1UP, x, y);
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return NULL;
	}
}