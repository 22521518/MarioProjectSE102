#pragma once
#include "HUDObject.h"
#include "SpriteFont.h"

class CHUDLives : public CHUDObject {
private:
	UINT* pLives = nullptr;
public:
	CHUDLives(float offX = 38.f, float offY = 7.f / 16.f + 8.f) : CHUDObject(offX, offY) {};
	CHUDLives(UINT* pLives, float offX = 38.f, float offY = 7.f / 16.f + 8.f) : CHUDObject(offX, offY)
	{
		this->pLives = pLives;
	}
	void Render() override {
		int lives = max(static_cast<int>(pLives ? *pLives : 0), 0);
		int len = lives > 0 ? static_cast<int>(log10(lives) + 0.5) : 1;
		CSpriteFont::GetInstance()
			->DrawFontNumber(lives, len, x + offsetX, y + offsetY);
	}
};