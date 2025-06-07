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
	void Render() override;

	~CHUDItems() { items.clear(); }
};