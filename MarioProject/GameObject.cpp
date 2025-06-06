#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"
#include "Brick.h"
#include "Coin.h"
#include "CloudPlatform.h"
#include "Portal.h"

#include "GameBackground9Sprite.h"
#include "SemisolidPlatform.h"
#include "SolidPlatform.h"
#include "BrickSuperItem.h"
#include "OneUpMushroom.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "DestroyableBrick.h"
#include "RedKoopa.h"
#include "RedKoopaParatroopa.h"
#include "GreenKoopa.h"
#include "GreenKoopaParatroopa.h"
#include "RedParagoomba.h"

#include "PlantGreenPiranha.h"
#include "PlantGreenVenusFire.h"
#include "PlantRedVenusFire.h"
#include "BlockQ.h"
#include "BrickStateIDs.h"
#include "BoomerangBrother.h"

#include "AssetIDs.h"
#include "mapUtil.h"

using namespace std;

CGameObject* CGameObject::CreateGameObject(int object_type, float x, float y, unordered_map<string, float> additionalFieldInfo, LPGAMEOBJECT player) {
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO: return new CMario(x, y);
	case OBJECT_TYPE_GOOMBA: return new CGoomba(x, y);
	case OBJECT_TYPE_RED_PARAGOOMBA: return new CRedParagoomba(x, y);
	case OBJECT_TYPE_BRICK: return new CBrick(x, y);
	case OBJECT_TYPE_DESTROYABLE_BRICK: return new CDestroyableBrick(x, y);
	case OBJECT_TYPE_COIN: return new CCoin(x, y);
	case OBJECT_TYPE_ITEM_BRICK: {
		LPMARIO mario = dynamic_cast<LPMARIO>(player);
		int ani_id_active = static_cast<int>(getOrDefault(additionalFieldInfo, "ani_id_active", ID_ANI_ITEM_BRICK));
		if (mario) return new CBrickSuperItem(mario, x, y);
		break;
	}
	case OBJECT_TYPE_SUPER_LEAF_ITEM: return new CSuperLeaf(x, y);
	case OBJECT_TYPE_SUPER_MUSHROOM_ITEM: return new CSuperMushroom(x, y);
	case OBJECT_TYPE_ONE_UP_MUSHROOM_ITEM: return new COneUpMushroom(x, y);
	case OBJECT_TYPE_RED_KOOPA: return new CRedKoopa(x, y);
	case OBJECT_TYPE_RED_KOOPA_TROOPA: return new CRedKoopaParatroopa(x, y);
	case OBJECT_TYPE_GREEN_KOOPA_TROOPA: return new CGreenKoopaParatroopa(x, y);
	case OBJECT_TYPE_GREEN_KOOPA: return new CGreenKoopa(x, y);
	case OBJECT_TYPE_SOLID_SEMISOLID_PLATFORM_9_SPRITE:
	case OBJECT_TYPE_SOLID_SOLID_PLATFORM_9_SPRITE:
	case OBJECT_TYPE_GAME_BACKGROUND_9_SPRITE:
	case OBJECT_TYPE_GAME_BACKGROUND_COLOR_9_SPRITE:
	{
		float cell_width = static_cast<float>(getOrDefault(additionalFieldInfo, "cell_width", 16.0f));
		float cell_height = static_cast<float>(getOrDefault(additionalFieldInfo, "cell_height", 16.0f));

		int height = static_cast<int>(getOrDefault(additionalFieldInfo, "height", 1.0f));
		int length = static_cast<int>(getOrDefault(additionalFieldInfo, "length", 1.0f));

		int sprite_id_top_begin = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_top_begin", 0.0f));
		int sprite_id_top_middle = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_top_middle", 0.0f));
		int sprite_id_top_end = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_top_end", 0.0f));

		int sprite_id_mid_begin = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_mid_begin", 0.0f));
		int sprite_id_mid_middle = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_mid_middle", 0.0f));
		int sprite_id_mid_end = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_mid_end", 0.0f));

		int sprite_id_bot_begin = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_bot_begin", 0.0f));
		int sprite_id_bot_middle = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_bot_middle", 0.0f));
		int sprite_id_bot_end = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_id_bot_end", 0.0f));
		
		if (object_type == OBJECT_TYPE_SOLID_SEMISOLID_PLATFORM_9_SPRITE)
		{
			return new CSemisolidPlatform(x, y, length, height, cell_width, cell_height,
				sprite_id_top_begin, sprite_id_top_middle, sprite_id_top_end,
				sprite_id_mid_begin, sprite_id_mid_middle, sprite_id_mid_end,
				sprite_id_bot_begin, sprite_id_bot_middle, sprite_id_bot_end);
		}
		else if (object_type == OBJECT_TYPE_SOLID_SOLID_PLATFORM_9_SPRITE)
		{
			return new CSolidPlatform(x, y, length, height, cell_width, cell_height,
				sprite_id_top_begin, sprite_id_top_middle, sprite_id_top_end,
				sprite_id_mid_begin, sprite_id_mid_middle, sprite_id_mid_end,
				sprite_id_bot_begin, sprite_id_bot_middle, sprite_id_bot_end);
		}
		else if (object_type == OBJECT_TYPE_GAME_BACKGROUND_9_SPRITE || object_type == OBJECT_TYPE_GAME_BACKGROUND_COLOR_9_SPRITE)
		{
			return new CGameBackground9Sprite(x, y, length, height, cell_width, cell_height,
				sprite_id_top_begin, sprite_id_top_middle, sprite_id_top_end,
				sprite_id_mid_begin, sprite_id_mid_middle, sprite_id_mid_end,
				sprite_id_bot_begin, sprite_id_bot_middle, sprite_id_bot_end);
		}
	}
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = static_cast<float>(getOrDefault(additionalFieldInfo, "cell_width", 16.0f));
		float cell_height = static_cast<float>(getOrDefault(additionalFieldInfo, "cell_height", 16.0f));
		int length = static_cast<int>(getOrDefault(additionalFieldInfo, "length", 1.0f));
		int sprite_begin = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_begin", 0.0f));
		int sprite_middle = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_middle", 0.0f));
		int sprite_end = static_cast<int>(getOrDefault(additionalFieldInfo, "sprite_end", 0.0f));

		return new CCloudPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = static_cast<float>(getOrDefault(additionalFieldInfo, "right", 0.0f));
		float b = static_cast<float>(getOrDefault(additionalFieldInfo, "bottom", 0.0f));
		int scene_id = static_cast<int>(getOrDefault(additionalFieldInfo, "scene_id", 0.0f));

		bool isPipe = (getOrDefault(additionalFieldInfo, "is_pipe", 0.f) != 0.f);
		bool isReturnToExist = (getOrDefault(additionalFieldInfo, "is_return_to_exist", 0.f) != 0.f);
		int px = static_cast<int>(getOrDefault(additionalFieldInfo, "px", 0.0f));
		int py = static_cast<int>(getOrDefault(additionalFieldInfo, "pu", 0.0f));

		return new CPortal(x, y, r, b, scene_id, isPipe, isReturnToExist, px, py);

	}
	case OBJECT_TYPE_PLANT_GP: return new CPlantGreenPiranha(player, x, y);
	case OBJECT_TYPE_PLANT_GVF: return new CPlantGreenVenusFire(player, x, y);
	case OBJECT_TYPE_PLANT_RVF: return new CPlantRedVenusFire(player, x, y);
	case OBJECT_TYPE_BLOCK_Q_COIN: return new CBlockQ(player, BRICK_STATE_COIN, x, y);
	case OBJECT_TYPE_BLOCK_Q_ITEM: return new CBlockQ(player, BRICK_STATE_1UP, x, y);
	case OBJECT_TYPE_BOOMMERANG_BROTHER: return new CBoomerangBrother(player, x, y);
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return nullptr;
	}
	return nullptr;
}

void CGameObject::GetBoundingBox(RECT& rect)
{
	float left, top, right, bottom;
	this->GetBoundingBox(left, top, right, bottom);
	rect.left = (LONG)left;
	rect.top = (LONG)top;
	rect.right = (LONG)right;
	rect.bottom = (LONG)bottom;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect{};

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;


	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	CGame::GetInstance()->Draw(x - camX, y - camY, bbox, &rect, BBOX_ALPHA);

}

