#pragma once
#include "HUDObject.h"
#include "vector"
#include "HUDConfig.h"

using namespace std;

class CHUDContainer : public CHUDObject {
protected:
	const float height = HUD_CONTAINER_HEIGHT;
	vector<LPHUDOBJECT> items{};
public:
	CHUDContainer(float offX = 0, float offY = 16 * 10.8) : CHUDObject(offX, offY) {};
	CHUDContainer(UINT* time, ULONG* score, UINT* life, UINT* coin, UINT* world, float offX = 0, float offY = 16 * 10.8);

	void Render() override;

	~CHUDContainer() { items.clear(); };
};

typedef CHUDContainer* LPHUDCONTAINER;