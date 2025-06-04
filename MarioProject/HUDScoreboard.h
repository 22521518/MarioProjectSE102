#pragma once
#include "HUDObject.h"
#include "HUDSpriteIDs.h"

class CHUDScoreboard : public CHUDObject {

	int backgroundId = ID_SPRITE_HUD_SCORE_BACKGROUND;
protected:
	vector<LPHUDOBJECT> items;
public:
	CHUDScoreboard(float offX = 14.f, float offY = 8.f) : CHUDObject(offX, offY) {}
	CHUDScoreboard(UINT* time = nullptr, ULONG* score = nullptr, UINT* life = nullptr, UINT* coin = nullptr, UINT* world = nullptr, float offX = 14.f, float offY = 8.f);
	void Render() override;

	~CHUDScoreboard() { items.clear(); }
};