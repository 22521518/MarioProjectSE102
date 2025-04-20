#pragma once
#include "InteractiveObject.h"
#include "BrickIDs.h"
#include "CollidableWithMario.h"
#include "Coin.h"
#include "CollisionEvent.h"
#include "BrickStateIDs.h"

class CBlockQ : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPCOIN coinB = new CCoin(x, y);
public:
	CBlockQ(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
	}

	// game object method
	void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		if (state == -1) animations->Get(ID_ANI_BLOCK_Q)->Render(x, y);
		else animations->Get(ID_ANI_BLOCK_E)->Render(x, y);
		//RenderBoundingBox()
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
	int IsBlocking() override { return 1; };
	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		// jump on top >> kill RedKoop and deflect a bit 
		mario->OnCollisionWithCoin(coinB, e);
		if (e->normalY == DirectionYAxisType::Bottom)
		{
			//player->coin++;
			state = 0;
			//coinB->Delete();
		}
		/*else if ()
		{
			
		}*/
	}
};
