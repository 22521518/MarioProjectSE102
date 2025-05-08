#pragma once
#include "Goomba.h"

class CRedGoomba : public CGoomba {
public:
	CRedGoomba(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = GOOMBA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = GOOMBA_STATE_WALKING) 
		: CGoomba(x, y, vx, vy, ax, ay, nx, state) {
		this->SetState(state);
	};

	void Render() override;
};