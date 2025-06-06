#include "HUDContainer.h"
#include "HUDSpriteIDs.h"
#include "HUDObject.h"
#include "HUDBackground9Sprite.h"

CHUDContainer::CHUDContainer(UINT* time, ULONG* score, UINT* life, UINT* coin, UINT* world, float offX, float offY) :
	CHUDObject(offX, offY)
{
	items.push_back(CHUDBackground9Sprite::FromSingleSprite(x, y, 32, 3, 16, 16, ID_SPRITE_HUD_BACKGROUND));
	items.push_back(CHUDObject::CreateHUDScoreboard(time, score, life, coin, world));
	items.push_back(CHUDObject::CreateHUDItems());
	//items.push_back(new CHUDScoreboard(time, score, life, coin, world));
}

void CHUDContainer::Render()
{
	for (auto it : items) {
		it->SetPosition(x + offsetX, y + offsetY);
		it->Render();
	}
}
