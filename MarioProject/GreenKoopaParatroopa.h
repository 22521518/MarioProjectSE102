#pragma once
#include "Koopa.h"
#include "GreenKoopa.h"

class CGreenKoopaParatroopa
	: public CGreenKoopa
{
public:
	CGreenKoopaParatroopa(float x = 0, float y = 0, float vx = 0, float vy = -KOOPA_JUMP_VY, float ax = 0, float ay = KOOPA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = KOOPA_STATE_PARATROOPA) : CGreenKoopa(x, y, vx, vy, ax, ay, nx, state)
	{
		SetState(state);
	};
	// game object method
	// physical object method
	// interactive object method
	virtual void SetState(int state) override;
	virtual void OnNoCollision(DWORD dt) override;
};
