#include "HUDContainer.h"
#include "HUDSpriteIDs.h"
#include "HUDBackground9Sprite.h"

CHUDContainer::CHUDContainer(ULONGLONG* time, ULONGLONG* score, ULONGLONG* life, ULONGLONG* coin)
{
	offsetX = 0;
	offsetY = 16 * 12;
	items.push_back(CHUDBackground9Sprite::FromSingleSprite(1002, y, 32, 13, 16, 16, ID_SPRITE_HUD_BACKGROUND));
	//items.push_back(new CHUDScoreboard(time, score, life, coin));
}
void CHUDContainer::Render()
{
	for (auto it : items) {
		it->SetPosition(x + offsetX, y + offsetY);
		it->Render();
	}
}
