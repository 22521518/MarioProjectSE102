#pragma once
#include "HUDObject.h"
#include "vector"
#include "HUDConfig.h"
#include "HUDScoreboard.h"

using namespace std;

class CHUDContainer : public CHUDObject {
protected:
	const float height = HUD_CONTAINER_HEIGHT;
	vector<LPHUDOBJECT> items{};
public:
	CHUDContainer(ULONGLONG* time, ULONGLONG* score, ULONGLONG* life, ULONGLONG* coin);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {};
	void Render() override;

	~CHUDContainer() { items.clear(); };
};

typedef CHUDContainer* LPHUDCONTAINER;