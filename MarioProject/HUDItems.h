#pragma once
#include "HUDObject.h"
#include "HUDSpriteIDs.h"
#include "HUDConfig.h"
#include "Game.h"
#include "Mario.h"

class CHUDItems : public CHUDObject {

protected:
	vector<int> items;
public:
	CHUDItems(float offX = 164.f, float offY = 8.f) : CHUDObject(offX, offY)  {}
	void Render() override 
	{
		int currenI = 0;
		float xx, yy;
		for (; currenI < 3; currenI++) {
			yy = y + offsetY;
			xx = x + (HUD_ITEM_WIDTH + 4.f) * currenI + offsetX - 3.f;
			CSprites::GetInstance()->Get(ID_SPRITE_HUD_ITEM_BOX)->Draw(xx, yy);
			if (currenI < CMario::stageItem.size() && CSprites::GetInstance()->Get(CMario::stageItem[currenI]))
			{
				CSprites::GetInstance()->Get(CMario::stageItem[currenI])->Draw(xx + 3.f, yy + 5.f);
			}
		}
	
	}

	~CHUDItems() { items.clear(); }
};