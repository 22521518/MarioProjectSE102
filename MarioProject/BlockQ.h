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
	float My;
public:
	CBlockQ(LPGAMEOBJECT mario, int state = BRICK_STATE_COIN, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
		this->mario = mario;
		SetState(BRICK_STATE_COIN);
		this->coinB = new CCoin(x, y);
		My = y;
	}

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		if (state == BRICK_STATE_EMPTY || state == BRICK_STATE_EMPTYING)
			animations->Get(ID_ANI_BLOCK_W)->Render(x, y);
		else animations->Get(ID_ANI_BLOCK_Q)->Render(x, y);
		RenderBoundingBox();
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (e->normalY == DirectionYAxisType::Bottom)
		{
			if (!coinB->IsDeleted()) {
				coinB->Render();
				coinB->SetSpeed(0, BRICK_Q_COIN_SPEED);
				coinB->SetAcceleration(0, BRICK_Q_COIN_GAVITY);
				coinB->Delete();
			}
			SetState(BRICK_STATE_EMPTYING);
			vy = -BRICK_Q_SPEED;
			ay = BRICK_Q_GAVITY;
		}
		/*if (this->state != BRICK_STATE_EMPTY && this->y < My) {
			this->vy = 0;
			this->ay = 0;
		}
		float cx, cy;
		coinB->GetPosition(cx, cy);
		if (this->state != BRICK_STATE_EMPTY && cy < My) {
			coinB->Delete();
		}*/
		/*else if ()
		{

		}*/
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
