#include "HUDItems.h"

void CHUDItems::Render()
{
	int currenI = 0;
	float xx, yy;
	for (; currenI < 3; currenI++) {
		yy = y + offsetY;
		xx = x + (HUD_ITEM_WIDTH + 4.f) * currenI + offsetX - 3.f;
		CSprites::GetInstance()->Get(ID_SPRITE_HUD_ITEM_BOX)->Draw(xx, yy);
		if (currenI < CMario::stageItem.size() && CSprites::GetInstance()->Get(CMario::stageItem[currenI]))
		{
			CSprites::GetInstance()->Get(CMario::stageItem[currenI])->Draw(xx, yy);
		}
	}

}
