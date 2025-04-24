#pragma once
#include "PlantEnemy.h"
#include "CollidableWithMario.h"
#include "PlantEnemyConfig.h"
#include "GameObject.h"
#include "PlantFireBall.h"

class CPlantRedVenusFire :
	public CPlantEnemy, public CCollidableWithMario
{
protected:
	LPPLANTFIREBALL fire;
public:
	CPlantRedVenusFire(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CPlantEnemy(mario, x, y, vx, vy, ax, ay, nx, state) {
		lowerY = y;
		upperY = y - PLANT_BBOX_HEIGHT_R;
		fire = new CPlantFireBall(mario, x, y);
	};

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		mario->GetPosition(Mx, My);
		float XA = Mx - x;
		if (My < y - PLANT_Y_U) animations->Get(ID_ANI_PLANT_RVF_U)->Render(x, y);
		else if (XA < 0) animations->Get(ID_ANI_PLANT_RVF_L)->Render(x, y);
		else if (XA > 0) animations->Get(ID_ANI_PLANT_RVF_R)->Render(x, y);
		//RenderBoundingBox()
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
		//this->stateHandler->Update(this, dt);
		mario->GetPosition(Mx, My);
		if (this->state == PLANT_STATE_HIDE) {
			if (abs(this->x - Mx) < PLANT_HIDE_DISTANT) {
				SetState(PLANT_STATE_GO_UP);
				this->vy = -PLANT_SPEED;
			}
		}
		else if (this->state == PLANT_STATE_GO_UP && this->y <= upperY) {
			SetState(PLANT_STATE_UP);
			this->vy = 0;
			this->y = upperY;
		}
		else if (this->state == PLANT_STATE_UP) {
			if (abs(this->x - Mx) > PLANT_HIDE_DISTANT) {
				SetState(PLANT_STATE_GO_HIDE);
				this->vy = PLANT_SPEED;
			}
		}
		else if (this->state == PLANT_STATE_GO_HIDE && this->y >= lowerY) {
			SetState(PLANT_STATE_HIDE);
			this->vy = 0;
			this->y = lowerY;
		}
		CEnemy::Update(dt, coObjects);
	};
};

typedef CPlantRedVenusFire* LPPLANTENEMY_RVF;