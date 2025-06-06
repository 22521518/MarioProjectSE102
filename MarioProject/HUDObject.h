#pragma once
#include "GameObject.h"

class CHUDObject : public CGameObject {
protected:
	float offsetX;
	float offsetY;
public:
	CHUDObject(float offX = 0, float offY = 0) { this->offsetX = offX, this->offsetY = offY; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {};
	void GetOffSet(float& offX, float& offY) const { offX = this->offsetX; offY = this->offsetY; }

	static CHUDObject* CreateHUDScoreboard(UINT* time = nullptr, ULONG* score = nullptr, UINT* life = nullptr, UINT* coin = nullptr, UINT* world = nullptr, float offX = 14.f, float offY = 8.f);
	static CHUDObject* CreateHUDWorld(UINT* pWorld, float offX = 46.f, float offY = 7.f / 16.f);
	static CHUDObject* CreateHUDLives(UINT* pLives, float offX = 38.f, float offY = 7.f / 16.f + 8.f);
	static CHUDObject* CreateHUDScores(ULONG* pScore, float offX = 62.f, float offY = 7.f / 16.f + 8.f);
	static CHUDObject* CreateHUDTimes(UINT* pTimes, float offX = 62.f + 62.f, float offY = 7.f / 16.f + 8.f);
	static CHUDObject* CreateHUDCoins(UINT* pCoins, float offX = 140.f, float offY = 7.f / 16.f);
	static CHUDObject* CreateHUDPowerP(float offX = 62.f, float offY = 7.f / 16.f);
	static CHUDObject* CreateHUDItems(float offX = 184.f, float offY = 8.f);
	
};

typedef CHUDObject* LPHUDOBJECT;