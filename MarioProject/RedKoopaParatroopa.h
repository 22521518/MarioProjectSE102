#pragma once
#include "Koopa.h"
#include "RedKoopa.h"

class CRedKoopaParatroopa
	: public CRedKoopa 
{	
public:
	CRedKoopaParatroopa(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = KOOPA_PARATROOPA_ACCELERATION_Y, DirectionXAxisType nx = DirectionXAxisType::Left, int state = KOOPA_STATE_PARATROOPA) : CRedKoopa(x, y, vx, vy, ax, ay, nx, state)
	{
		this->vx = 0;
		this->ax = 0;

		SetState(state);
	};
	// game object method
	// physical object method
	// interactive object method
	virtual void SetState(int state) override;
	virtual void OnNoCollision(DWORD dt) override;
};