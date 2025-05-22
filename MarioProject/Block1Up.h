#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"
#include "CollisionEvent.h"
#include "BrickStateIDs.h"
#include "GameObject.h"
#include "BrickAniIDs.h"

class CBlock1Up : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPMARIO mm;
	float My;
public:
	bool out = false;
	CBlock1Up(LPGAMEOBJECT mario, int state, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
		mm = (LPMARIO)mario;
		My = y;
		SetState(BRICK_STATE_1UP);
	}
	// game object method
	virtual void Render() override {
		if (state != BRICK_STATE_EMPTY) {
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_BLOCK_Q_ITEM)->Render(x, y);
		}
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (state == BRICK_STATE_1UP) {
			this->vy = -BRICK_Q_1UP_GO_UP;
			this->ay = 0;
			SetState(BRICK_STATE_EMPTYING);
		}
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		if (out) {
			CCollision::GetInstance()->Process(this, dt, coObjects);
			if (!coObjects) this->OnNoCollision(dt);
		}
		else this->OnNoCollision(dt);
		if (this->y < My - BRICK_BBOX_HEIGHT) {
			this->ay = BRICK_Q_1UP_GAVITY;
			this->vy = BRICK_Q_1UP_SPEED_Y;
			float mx, my;
			mm->GetPosition(mx, my);
			if (mx < this->x) this->vx = BRICK_Q_1UP_SPEED_X;
			else this->vx = -BRICK_Q_1UP_SPEED_X;
			out = true;
		}
		mm->Collide1UP(this);
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	};

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	virtual void OnNoCollision(DWORD dt) override
	{
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CBlock1Up*>(e->obj)) return;

		if (e->normalY != DirectionYAxisType::None)
		{
			vy = 0;
		}
		else if (e->normalX != DirectionXAxisType::None)
		{
			vx = -vx;
		}
	};
	virtual void SetState(int state)
	{
		CInteractiveObject::SetState(state);
	};
};
typedef CBlock1Up* LPBLOCK1UP;
