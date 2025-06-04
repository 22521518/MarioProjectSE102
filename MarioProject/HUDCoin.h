#pragma once
#include "HUDObject.h"
#include "HUDSpriteIDs.h"
#include "SpriteFont.h"
#include "Sprites.h"

class CHUDCoin : public CHUDObject {
private:
	float orgOffsetX;
	UINT* pCoins = nullptr;
public:
	CHUDCoin(float offX = 140.f, float offY = 7.f / 16.f) : CHUDObject(offX, offY), orgOffsetX(offX) {};
	CHUDCoin(UINT* pCoin, float offX = 140.f, float offY = 7.f / 16.f) : CHUDObject(offX, offY), orgOffsetX(offX)
	{
		this->pCoins = pCoin;
	}
	void Render() override {
		int coins = static_cast<int>(pCoins ? *pCoins : 0);
		int len = (coins > 0) ? static_cast<int>(log10(coins) + 1) : 1;
		offsetX = orgOffsetX - (len - 1) * 8.0f;

		CSprites::GetInstance()->Get(ID_SPRITE_HUD_COIN_ICON)->Draw(x + offsetX - 4.0f, y + offsetY - 4.0f);
		CSpriteFont::GetInstance()->DrawFontNumber(coins, len, x + 8.f + offsetX, y + offsetY);
	}
};