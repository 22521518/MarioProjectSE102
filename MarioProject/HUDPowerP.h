#pragma once

#include "HUDObject.h"
#include "HUDSpriteIDs.h"
#include "Game.h"
#include "PlayScene.h"
#include "Mario.h"

class HUDPowerP : public CHUDObject {

protected:
public:
	HUDPowerP(float offX = 62.f, float offY = 7.f / 16.f) : CHUDObject(offX, offY) {};
	
	void Render() override {
		int currenI = 0;
		float xx, yy;
		LPPLAYSCENE ps = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		if (ps) {
			LPMARIO mr = dynamic_cast<LPMARIO>(ps->GetPlayer());
			if (mr) {
				for (; currenI < mr->GetPowerP(); currenI++) {
					yy = y + offsetY - 4.f;
					xx = x + 8.f * currenI + offsetX - 4.f;
					if (currenI < 6) {
						CSprites::GetInstance()->Get(ID_SPRITE_HUD_POWER_P_ARROW_FILL)->Draw(xx, yy);
					}
					else {
						CSprites::GetInstance()->Get(ID_SPRITE_HUD_POWER_P_P_FILL)->Draw(xx + 4.f, yy);
					}
				}
			}
		}
		for (; currenI < 7; currenI++) {
			yy = y + offsetY - 4.f;
			xx = x + 8.f * currenI + offsetX - 4.f;
			if (currenI < 6) {
				CSprites::GetInstance()->Get(ID_SPRITE_HUD_POWER_P_ARROW)->Draw(xx, yy);
			}
			else {
				CSprites::GetInstance()->Get(ID_SPRITE_HUD_POWER_P_P)->Draw(xx + 4.f, yy);
			}
		}
	}
};