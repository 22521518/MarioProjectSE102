#pragma once
#include "PlantEnemy.h"
#include "CollidableWithMario.h"
#include "PlantEnemyConfig.h"
#include "GameObject.h"
#include "PlantFireBall.h"
#include "Collision.h"

class CPlantGreenVenusFire :
	public CPlantEnemy
{
protected:
	LPPLANTFIREBALL fire;
	LPMARIO mm;
	bool IsFire;
public:
	CPlantGreenVenusFire(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CPlantEnemy(mario, x, y, vx, vy, ax, ay, nx, state) {
		mm = (LPMARIO)mario;
		lowerY = y;
		upperY = y - PLANT_BBOX_HEIGHT_G;
		fire = new CPlantFireBall(mario, x, upperY);
		IsFire = false;
	};

	// game object method
	virtual void Render() override {
		if (IsFire) fire->Render();
		CAnimations* animations = CAnimations::GetInstance();
		mario->GetPosition(Mx, My);
		if (x > Mx) {
			if (y < My) animations->Get(ID_ANI_PLANT_GVF_L_D)->Render(x, y);
			else animations->Get(ID_ANI_PLANT_GVF_L_U)->Render(x, y);
		}
		else {
			if (y < My) animations->Get(ID_ANI_PLANT_GVF_R_D)->Render(x, y);
			else animations->Get(ID_ANI_PLANT_GVF_R_U)->Render(x, y);
		}
	};
	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override
	{
		float boxHeight = PLANT_BBOX_HEIGHT_R;
		float boxWidth = PLANT_BBOX_WIDTH;
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
		// jump on top >> kill ___ and deflect a bit 
		mario->OnCollisionWithEnemy(this, e);
		if (e->normalY == DirectionYAxisType::Top)
		{
			if (!this->IsDeadState())
			{
				this->SetState(PLANT_STATE_DIE);
			}
		}
	};
};

typedef CPlantGreenVenusFire* LPPLANTENEMY_GVF;