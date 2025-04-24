#pragma once
#include "Enemy.h"
#include "PlantEnemyConfig.h"
#include "CollidableWithMario.h"
#include "GameObject.h"
#include "Collision.h"

class CPlantEnemy :
	public CEnemy, public CCollidableWithMario
{
protected:
	LPGAMEOBJECT mario;
	float Mx, My;
	float upperY, lowerY;
public:
	CPlantEnemy(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CEnemy(x, y, vx, vy, ax, ay, nx, state)
	{
		this->mario = mario;
		SetState(PLANT_STATE_HIDE);
	};

	// game object method
	virtual void Render() {};

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
		if (dynamic_cast<LPPLANTENEMY>(e->obj)) return;

		if (e->normalY != DirectionYAxisType::None)
		{
			vy = 0;
		}
		else if (e->normalX != DirectionXAxisType::None)
		{
			vx = -vx;
		}
	};
	virtual bool IsDeadState() override { return this->state == PLANT_STATE_DIE; }
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		// jump on top >> kill ___ and deflect a bit 
		mario->OnCollisionWithPlant(this, e);
	};
};

typedef CPlantEnemy* LPPLANTENEMY;