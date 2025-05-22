#pragma once
#include "Brick.h"
#include "BrickAniIDs.h"
#include "BrickStateIDs.h"

class CBlockF : public CBrick {

public:
	CBlockF(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0)
		: CBrick(x, y, vx, vy, ax, ay) {
	}

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BLOCK_F)->Render(x, y);
	};
};