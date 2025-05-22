#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"
#include "Coin.h"
#include "CollisionEvent.h"
#include "BrickStateIDs.h"
#include "GameObject.h"

class CBlockCoin : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPGAMEOBJECT mario;
	LPCOIN coinB;
	float My;
public:
	CBlockCoin(LPGAMEOBJECT mario, int state, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
		this->mario = mario;
		this->coinB = new CCoin(x, y);
		My = y;
		SetState(BRICK_STATE_COIN);
	}
	// game object method
	virtual void Render() override {
		if (state != BRICK_STATE_EMPTY) {
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_COIN)->Render(x, y);
		}
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (state == BRICK_STATE_COIN) {
			if (state == BRICK_STATE_COIN) coinB->OnMarioCollide(mario, e);
			this->vy = -BRICK_Q_COIN_SPEED;
			this->ay = BRICK_Q_COIN_GAVITY;
			SetState(BRICK_STATE_EMPTYING);
		}
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
		if (this->y > My) {
			this->vy = 0;
			this->ay = 0;
			this->y = My;
			SetState(BRICK_STATE_EMPTY);
		}
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
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<LPINTERACTIVEOBJECT>(e->obj)) return;
		if (e->normalY != DirectionYAxisType::Bottom)
		{
			vy = 0;
		}
		else
		{
			vy = 0;
		}
	};
	virtual void SetState(int state)
	{
		CInteractiveObject::SetState(state);
	};
};
typedef CBlockCoin* LPBLOCKCOIN;
