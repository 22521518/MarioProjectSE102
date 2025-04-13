#pragma once
#include "StaticObject.h"
#include "BrickStateIDs.h"

class CBlock : public CStaticObject {
public:
	CBlock(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left)
		: CStaticObject(x, y, vx, vy, ax, ay, nx) {
	};
	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {
		left = x - BRICK_BBOX_WIDTH / 2;
		top = y - BRICK_BBOX_HEIGHT / 2;
		right = left + BRICK_BBOX_WIDTH;
		bottom = top + BRICK_BBOX_HEIGHT;
	};
};

typedef CBlock* LPBlock;
