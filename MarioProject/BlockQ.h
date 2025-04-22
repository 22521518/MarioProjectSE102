#pragma once
#include "InteractiveObject.h"
#include "BrickIDs.h"
#include "CollidableWithMario.h"
#include "Coin.h"
#include "CollisionEvent.h"
#include "BrickStateIDs.h"
#include "GameObject.h"

class CBlockQ : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPGAMEOBJECT mario;
	LPCOIN coinB;
public:
	CBlockQ(LPGAMEOBJECT mario, int state = BRICK_STATE_COIN, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
		this->mario = mario;
		SetState(BRICK_STATE_COIN);
		this->coinB = new CCoin(x, y);
	}

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		if (state == BRICK_STATE_EMPTY) animations->Get(ID_ANI_BLOCK_E)->Render(x, y);
		else animations->Get(ID_ANI_BLOCK_Q)->Render(x, y);
		//RenderBoundingBox()
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (e->normalY == DirectionYAxisType::Bottom)
		{
			mario->OnCollisionWithCoin(coinB, e);
			this->SetState(0);
			coinB->Delete();
		}
		/*else if ()
		{

		}*/
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		//not write yet
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	};

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 1; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	virtual void OnNoCollision(DWORD dt) override
	{
		x += vx * dt;
		y += vy * dt;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<LPINTERACTIVEOBJECT>(e->obj)) return;

		if (e->normalY != DirectionYAxisType::None)
		{
			vy = 0;
		}
		else if (e->normalX != DirectionXAxisType::None)
		{
			vx = -vx;
		}
	};
};
typedef CBlockQ* LPBLOCKQ;
