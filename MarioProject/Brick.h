#pragma once
#include "Block.h"

class CBrick : public CBlock {

public:
	CBrick(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0)
		: CBlock(x, y, vx, vy, ax, ay) {}

	// game object method
	virtual void Render() override;
};