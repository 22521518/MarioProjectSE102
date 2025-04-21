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
		SetState(PLANT_STATE_HIDE);
	};

	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_PLANT_GP)->Render(x, y);
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
}

typedef CPlantGreenPiranha* LPPlantGP;