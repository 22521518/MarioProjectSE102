#pragma once
#include "PlantEnemy.h"
#include "CollidableWithMario.h"
#include "PlantEnemyConfig.h"
#include "GameObject.h"

class CPlantGreenPiranha :
	public CPlantEnemy, public CCollidableWithMario
{
public:
	CPlantGreenPiranha(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CPlantEnemy(mario, x, y, vx, vy, ax, ay, nx, state) {
		lowerY = y;
		upperY = y + 24;
	};

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		mario->GetPosition(Mx, My);
		if (Mx - x > 0) animations->Get(ID_ANI_PLANT_GP_L)->Render(x, y);
		else if (Mx - x < 0) animations->Get(ID_ANI_PLANT_GP_R)->Render(x, y);
		//RenderBoundingBox()
	};
	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		// jump on top >> kill ___ and deflect a bit 
		mario->OnCollisionWithPlant(this, e);
		if (e->normalY == DirectionYAxisType::Top)
		{
			if (!this->IsDeadState())
			{
				this->SetState(PLANT_STATE_DIE);
			}
		}
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		//this->stateHandler->Update(this, dt);
		mario->GetPosition(Mx, My);
		if (this->state == PLANT_STATE_HIDE) {
			if (abs(this->y - Mx) < 800) {
				SetState(PLANT_STATE_GO_UP);
				this->vy = PLANT_SPEED;
			}
		}
		else if (this->state == PLANT_STATE_GO_UP) {
			if (this->y >= upperY) SetState(PLANT_STATE_UP);
		}
		else if (this->state == PLANT_STATE_UP) {
			if (abs(this->y - Mx) > 800) {
				SetState(PLANT_STATE_GO_HIDE);
				this->vy = -PLANT_SPEED;
			}
		}
		else if (this->state == PLANT_STATE_GO_HIDE) {
			if (this->y <= lowerY) SetState(PLANT_STATE_HIDE);
		}
		CEnemy::Update(dt, coObjects);
	};
};

typedef CPlantGreenPiranha* LPPLANTENEMY_GP;