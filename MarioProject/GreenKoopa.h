#pragma once
#include "Koopa.h"
class CGreenKoopa :
    public CKoopa
{
public:
	CGreenKoopa(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = KOOPA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = KOOPA_STATE_WALKING) : CKoopa(x, y, vx, vy, ax, ay, nx, state)
	{
		SetState(state);
	};
	// game object method
	// physical object method
	// interactive object method
	virtual void SetState(int state) override;
	virtual void SetState(int state, LPCOLLISIONEVENT e) override;
};

typedef CGreenKoopa* LPGREENKOOPA;
