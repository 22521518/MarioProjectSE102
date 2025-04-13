#pragma once
#include "Brick.h"
#include "BrickIDs.h"
#include "CollidableWithMario.h"

class CBlockQ : public CBrick, public CCollidableWithMario {

public:
	CBlockQ(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0)
		: CBrick(x, y, vx, vy, ax, ay) {
	}

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BLOCK_Q)->Render(x, y);
		//RenderBoundingBox()
	};
	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		//this->Delete();
		//mario->OnCollisionWithBlockQ(this, e);
	}
};
