#pragma once
#include "Item.h"
#include "ItemConfig.h"

class CSuperLeaf : public CItem {
	unsigned int timelapse;
	float startX;
	float swaySpeed;
	float swayAmplitude;

public:
	CSuperLeaf(float x = 0, float y = 0, float vx = 0, float vy = SUPER_LEAF_FALL_SPEED, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, float swaySpeed = SUPER_LEAF_SWAY_SPEED, float swayAmplitude = SUPER_LEAF_SWAY_AMPLITUDE): CItem(x, y, vx, vy, ax, ay, nx), startX(x), swaySpeed(swaySpeed), swayAmplitude(swayAmplitude), timelapse(0) {}

	// game object method
	virtual void Render() override;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
};

typedef CSuperLeaf* LPSUPERLEAF;