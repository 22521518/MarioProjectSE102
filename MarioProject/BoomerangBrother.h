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
	LPGAMEOBJECT mario;
	float Mx, My;
	//float upperX, lowerX;
	LPBOOMERANG fire;
	LPMARIO mm;
	bool IsFire;
public:
	CBoomerangBrother(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CEnemy(x, y, vx, vy, ax, ay, nx, state)
	{
		this->mario = mario;
		SetState(BB_STATE_NO_HIT);
	};

	// game object method
	virtual void Render() override {
		if (!IsDeadState()) {
			if (IsFire) fire->Render();
			CAnimations* animations = CAnimations::GetInstance();
			mario->GetPosition(Mx, My);
			float XA = Mx - x;
			if (x > Mx) {
				animations->Get(ID_ANI_BOOMMERANG_BROTHER_L)->Render(x, y);
			}
			else {
				animations->Get(ID_ANI_BOOMMERANG_BROTHER_R)->Render(x, y);
			}
		}
	};

	// physical object method
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
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
	virtual bool IsHitState1() { return this->state == BB_STATE_HIT_ONE; }
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
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
		if (IsFire) mm->CollideBullet(fire);
		if (this->state == PLANT_STATE_HIDE) {
			if (abs(this->x - Mx) < PLANT_HIDE_DISTANT && (fire->Distant(this) > FIREBALL_COMEBACK || !IsFire)) {
				SetState(PLANT_STATE_GO_UP);
				this->vy = -PLANT_SPEED_R;
			}
		}
		else if (this->state == PLANT_STATE_GO_UP && this->y <= upperY) {
			SetState(PLANT_STATE_UP);
			this->vy = 0;
			this->y = upperY;
		}
		else if (this->state == PLANT_STATE_UP) {
			if (fire->Distant(this) > FIREBALL_COMEBACK || !IsFire) {
				fire->SetPosition(x, y);
				fire->WhereToShoot(this);
				IsFire = true;
			}
			mario->GetPosition(Mx, My);
			if (abs(this->x - Mx) > PLANT_HIDE_DISTANT || fire->Distant(this) > PLANT_FIREBALL_HIDE_DISTANT) {
				SetState(PLANT_STATE_GO_HIDE);
				this->vy = PLANT_SPEED_R;
			}
		}
		else if (this->state == PLANT_STATE_GO_HIDE && this->y >= lowerY) {
			SetState(PLANT_STATE_HIDE);
			this->vy = 0;
			this->y = lowerY;
			//fire->SetPosition(x, y);
			//IsFire = false;
		}
		fire->Update(dt, coObjects);
		CEnemy::Update(dt, coObjects);
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
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
};
typedef CBoomerangBrother* LPBOOMERANGBROTHER;