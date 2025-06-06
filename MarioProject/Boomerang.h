#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "BoomerangBrotherConfig.h"

class CBoomerang : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPGAMEOBJECT mario;
public:
	CBoomerang(LPGAMEOBJECT mario, int state, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {
		this->mario = mario;
	}
	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		if (this->GetState() < BOOMERANG_STATE_TROWING) {
			if(this->GetState() == BOOMERANG_STATE_NO_TROW_L) animations->Get(ID_ANI_BOOMMERANG_L)->Render(x, y);
			else animations->Get(ID_ANI_BOOMMERANG_R)->Render(x, y);
		}
		else {
			animations->Get(ID_ANI_BOOMMERANG_TROW)->Render(x, y);
		}
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (mario->IsUntouchable() == 0) // hit FIRE BALL!
		{
			if (mario->GetLevel() > MARIO_LEVEL_SMALL)
			{
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				mario->SetState(MARIO_STATE_DIE);
			}
		}
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = x - BOOMERANG_WIDTH / 2;
		t = y - BOOMERANG_HEIGHT / 2;
		r = l + BOOMERANG_WIDTH;
		b = t + BOOMERANG_HEIGHT;
	};

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
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
	virtual int GetState()
	{
		return this->state;
	};
	void WhereToShoot(float &Fx, float &Fy) {
		float Mx, My, Px, Py;
		//plant->GetPosition(Px, Py);
		Px = Fx;
		Py = Fy;
		mario->GetPosition(Mx, My);
		float GOx = Mx - Px, GOy = Py - My;
		float rate = GOx / GOy;
		float BY = sqrt(powf(BOOMERANG_SPEED, (float)2) / (powf(rate, (float)2) + 1));
		float BX = BY * rate;
		if (Py <= My)this->SetSpeed(-BX, BY);
		else if (Py > My)this->SetSpeed(BX, -BY);
	};
	void BoomerangReturn(float& Fx, float& Fy) {
		float Mx, My;
		//plant->GetOldPosition(Mx, My);
		Mx = Fx;
		My = Fy;
		float GOx = Mx - x, GOy = y - My;
		float rate = GOx / GOy;
		float BY = sqrt(powf(BOOMERANG_SPEED, (float)2) / (powf(rate, (float)2) + 1));
		float BX = BY * rate;
		if (y <= My)this->SetSpeed(-BX, BY);
		else if (y > My)this->SetSpeed(BX, -BY);
	};
	float DistantOld(float& Fx, float& Fy) {
		float Px, Py;
		//plant->GetOldPosition(Px, Py);
		Px = Fx;
		Py = Fy;
		return sqrt(powf((x - Px), (float)2) + powf((Py - y), (float)2));
	};
};

typedef CBoomerang* LPBOOMERANG;