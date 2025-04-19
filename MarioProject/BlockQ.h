#pragma once
#include "InteractiveObject.h"
#include "BrickIDs.h"
#include "CollidableWithMario.h"

class CBlockQ : public CInteractiveObject, public CCollidableWithMario {

public:
	CBlockQ(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
	}

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		if (state == -1) animations->Get(ID_ANI_BLOCK_Q)->Render(x, y);
		else animations->Get(ID_ANI_BLOCK_E)->Render(x, y);
		//RenderBoundingBox()
	};
	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		
	}
};
