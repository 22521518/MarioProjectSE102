#pragma once
#include "InteractiveObject.h"
#include "BrickAniIDs.h"
#include "CollidableWithMario.h"
#include "BlockCoin.h"
#include "Block1Up.h"
#include "CollisionEvent.h"
#include "BrickStateIDs.h"
#include "GameObject.h"
#include "CoinAniIDs.h"

class CBlockQ : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPGAMEOBJECT mario;
	LPBLOCKCOIN coinB;
	LPBLOCK1UP itemB;
	float My;
	bool coinQ = false, upQ = false;
public:
	CBlockQ(LPGAMEOBJECT mario, int state = BRICK_STATE_COIN, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
		this->mario = mario;
		//SetState(BRICK_STATE_COIN);
		if (state == BRICK_STATE_COIN) {
			this->coinB = new CBlockCoin(mario, state, x, y);
			coinQ = true;
		}
		else if (state == BRICK_STATE_1UP) {
			this->itemB = new CBlock1Up(mario, state, x, y);
			upQ = true;
		}
		My = y;
	}

	// game object method
	virtual void Render() override {
		if (coinQ) coinB->Render();
		else if (upQ) itemB->Render();
		CAnimations* animations = CAnimations::GetInstance();
		if (state == BRICK_STATE_EMPTY)
			animations->Get(ID_ANI_BLOCK_E)->Render(x, y);
		else animations->Get(ID_ANI_BLOCK_Q)->Render(x, y);
		RenderBoundingBox();
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (e->normalY == DirectionYAxisType::Bottom)
		{
			SetState(BRICK_STATE_EMPTY);
			if (coinQ) coinB->OnMarioCollide(mario, e);
			else if (upQ) itemB->OnMarioCollide(mario, e);
			vy = -BRICK_Q_SPEED;
			ay = BRICK_Q_GAVITY;
		}
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		if (coinQ) coinB->Update(dt, coObjects);
		else if (upQ) {
			itemB->Update(dt, coObjects);
		}
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
		if (this->y > My) {
			this->vy = 0;
			this->ay = 0;
			this->y = My;
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
typedef CBlockQ* LPBLOCKQ;
