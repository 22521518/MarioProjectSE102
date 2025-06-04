#pragma once
#include "HUDObject.h"
#include "SpriteFont.h"

class CHUDWorld : public CHUDObject {
private:
	UINT* pWorld = nullptr;
public:
	CHUDWorld(float offX = 46.f, float offY = 7.f / 16.f) : CHUDObject(offX, offY) {};
	CHUDWorld(UINT* pWorld, float offX = 46.f, float offY = 7.f / 16.f) : CHUDObject(offX, offY)
	{
		this->pWorld = pWorld;
	}
	void Render() override {
		CSpriteFont::GetInstance()->DrawFontNumber(static_cast<int>(pWorld ? *pWorld : 1), 1, x + offsetX, y + offsetY);
	}
};