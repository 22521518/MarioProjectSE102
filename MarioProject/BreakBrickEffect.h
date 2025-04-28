#pragma once
#include "Brick.h"

class CBreakBrickEffect : public CBrick
{
public:
	CBreakBrickEffect(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0)
		: CBrick(x, y, vx, vy, ax, ay) {}

	// game object method
	virtual void Render() override;
};

typedef CBreakBrickEffect* LPBREAKBRICKEFFECT;