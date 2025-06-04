#pragma once
#include "HUDObject.h"
#include "HUDSpriteIDs.h"
#include "SpriteFont.h"
#include "Sprites.h"

class CHUDTime : public CHUDObject {
private:
	UINT* pTime = nullptr;
public:
	CHUDTime(float offX = 124.f, float offY = 7.f / 16.f + 8.f) : CHUDObject(offX, offY) {};
	CHUDTime(UINT* pTime, float offX = 124.f, float offY = 7.f / 16.f + 8.f) : CHUDObject(offX, offY)
	{
		this->pTime = pTime;
	}
	void Render() override {
		int time = min(999, static_cast<int>(pTime ? *pTime : 0));
		time = max(time, 0);
		CSprites::GetInstance()->Get(ID_SPRITE_HUD_TIME_ICON)->Draw(x + offsetX - 4.0f, y + offsetY - 4.0f);
		CSpriteFont::GetInstance()->DrawFontNumber(time, 3, x + 8.f + offsetX, y + offsetY);
	}
};