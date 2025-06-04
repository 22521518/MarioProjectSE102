#pragma once
#include "HUDObject.h"
#include "SpriteFont.h"

class CHUDScore : public CHUDObject {
private:
	ULONG* pScores = nullptr;
public:
	CHUDScore(float offX = 62.f, float offY = 7.f / 16.f + 8.f) : CHUDObject(offX, offY) {};
	CHUDScore(ULONG* pScores, float offX = 62.f, float offY = 7.f / 16.f + 8.f) : CHUDObject(offX, offY)
	{
		this->pScores = pScores;
	}
	void Render() override {
		CSpriteFont::GetInstance()->DrawFontNumber(min(9999999, static_cast<int>(pScores ? *pScores : 0)), 7, x + offsetX, y + offsetY);
	}
};