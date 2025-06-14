#pragma once
#include "Enemy.h"
#include "BoomerangBrotherConfig.h"
#include "CollidableWithMario.h"
#include "GameObject.h"
#include "Collision.h"
#include "Boomerang.h"

class CBoomerangBrother :
	public CEnemy, public CCollidableWithMario
{
protected:
	//LPGAMEOBJECT mario;
	float Mx, My;
	//float upperX, lowerX;
	LPBOOMERANG fire;
	LPMARIO mm;
	//int BThow;
	ULONGLONG trow_start = 0;
public:
	float oldx, oldy;
	float Fx, Fy;
	CBoomerangBrother(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = 0)
		: CEnemy(x, y, vx, vy, ax, ay, nx, state)
	{
		mm = (LPMARIO)mario;
		SetState(BB_STATE_NO_HIT);
		fire = new CBoomerang(mario, BOOMERANG_STATE_NO_TROW_R, x - BOOMERANG_X_OFFSET, y - BOOMERANG_Y_OFFSET);
		//BThow = BOOMERANG_STATE_NO_TROW;
		Fx = x; Fy = y;
	};

	// game object method
	virtual void Render() override {
		if (!IsDeadState()) {
			fire->Render();
			CAnimations* animations = CAnimations::GetInstance();
			LPPLAYSCENE ps = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			LPMARIO mario = dynamic_cast<LPMARIO> (ps->GetPlayer());

			if (!mario) {
				animations->Get(ID_ANI_BOOMMERANG_BROTHER_L_TROWED)->Render(x, y);
				return;
			}

			mario->GetPosition(Mx, My);
			//if (x > Mx) animations->Get(ID_ANI_BOOMMERANG_BROTHER_L_TROWING)->Render(x, y);
			//else animations->Get(ID_ANI_BOOMMERANG_BROTHER_R_TROWING)->Render(x, y);
			if (fire->GetState() < BOOMERANG_STATE_TROWING) {
				if (x > Mx) animations->Get(ID_ANI_BOOMMERANG_BROTHER_L_TROWING)->Render(x, y);
				else animations->Get(ID_ANI_BOOMMERANG_BROTHER_R_TROWING)->Render(x, y);
			}
			else {
				if (x > Mx) animations->Get(ID_ANI_BOOMMERANG_BROTHER_L_TROWED)->Render(x, y);
				else animations->Get(ID_ANI_BOOMMERANG_BROTHER_R_TROWED)->Render(x, y);
			}
		}
	};

	// physical object method
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 1; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	virtual void SetState(int state)
	{
		CInteractiveObject::SetState(state);
	};
	virtual void OnNoCollision(DWORD dt) override
	{
		x += vx * dt;
		y += vy * dt;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<LPBOOMERANGBROTHER>(e->obj)) return;

		if (e->normalY != DirectionYAxisType::None)
		{
			vy = 0;
		}
		else if (e->normalX != DirectionXAxisType::None)
		{
			vx = -vx;
		}
	};
	bool IsHitState1() { return this->state == BB_STATE_HIT_ONE; }
	virtual bool IsDeadState() override { return this->state == BB_STATE_DIE; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override
	{
		float boxHeight = BOOMERANG_BROTHER_BBOX_HEIGHT;
		float boxWidth = BOOMERANG_BROTHER_BBOX_WIDTH;
		left = x - boxWidth / 2;
		top = y - boxHeight / 2;
		right = left + boxWidth;
		bottom = top + boxHeight;
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		if (!IsDeadState()) {
			this->vy += this->ay * dt;
			this->vx += this->ax * dt;
			this->x += this->vx * dt;
			this->y += this->vy * dt;

			LPPLAYSCENE ps = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			LPMARIO mario = dynamic_cast<LPMARIO> (ps->GetPlayer());
			if (!mario) return;

			mario->GetPosition(Mx, My);
			Fx = x; Fy = y;
			if (x > Mx) vx = -BOOMERANG_BROTHER_SPEED;
			else vx = BOOMERANG_BROTHER_SPEED;
			mm->CollideBullet(fire);
			fire->SetPosition(x, y);
			if ((fire->GetState() == BOOMERANG_STATE_NO_TROW_L) || (fire->GetState() == BOOMERANG_STATE_NO_TROW_R)) {
				fire->WhereToShoot(Fx, Fy);
				oldx = this->x;
				oldy = this->y;
				fire->SetState(BOOMERANG_STATE_TROWING);
				trow_start = GetTickCount64();
			}
			if (fire->DistantOld(oldx, oldy) > BOOMERANG_COMEBACK) fire->BoomerangReturn(oldx, oldy);
			if (((fire->DistantOld(oldx, oldy) < BOOMERANG_SNAP_COMEBACK) ||
				(fire->DistantOld(this->x, this->y) < BOOMERANG_SNAP_COMEBACK))
				&& (fire->GetState() == BOOMERANG_STATE_TROWED)) {
				if (x > Mx) {
					fire->SetPosition(this->x + BOOMERANG_X_OFFSET, this->y - BOOMERANG_Y_OFFSET);
					fire->SetState(BOOMERANG_STATE_NO_TROW_L);
				}
				else {
					fire->SetPosition(this->x - BOOMERANG_X_OFFSET, this->y - BOOMERANG_Y_OFFSET);
					fire->SetState(BOOMERANG_STATE_NO_TROW_R);
				}
				fire->SetSpeed(0, 0);
			}
			if ((fire->GetState() == BOOMERANG_STATE_TROWING) && ((GetTickCount64() - trow_start > BOOMERANG_TROW_TIME)
				|| (fire->DistantOld(this->x, this->y) > BOOMERANG_SNAP_COMEBACK))) {
				fire->SetState(BOOMERANG_STATE_TROWED);
			}
			fire->Update(dt, coObjects);
			CEnemy::Update(dt, coObjects);
		}
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override
	{
		if (!IsDeadState()) {
			// jump on top >> kill ___ and deflect a bit 
			mario->OnCollisionWithEnemy(this, e);
			if (e->normalY == DirectionYAxisType::Top)
			{
				if (!this->IsHitState1())
				{
					this->SetState(BB_STATE_DIE);
				}
				else {
					this->SetState(BB_STATE_HIT_ONE);
				}
			}
		}
	};
	virtual void GetOldPosition(float& x, float& y) const { x = this->oldx; y = this->oldy; };
};

typedef CBoomerangBrother* LPBOOMERANGBROTHER;