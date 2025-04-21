#pragma once
#include "Enemy.h"
#include "PlantEnemyConfig.h"
#include "CollidableWithMario.h"
#include "GameObject.h"
#include "Collision.h"

class CPlantEnemy :
	public CEnemy , public CCollidableWithMario
{
protected:
	LPGAMEOBJECT mario;
	float Mx, My;
public:
	CPlantEnemy(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CEnemy(x, y, vx, vy, ax, ay, nx, state)
	{
		this->mario = mario;
	};

	// game object method
	virtual void Render(){};

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override
	{
		float boxHeight = PLANT_BBOX_HEIGHT;
		float boxWidth = PLANT_BBOX_WIDTH;
		/*switch (state)
		{
		case PLANT_STATE_HIDE:
			boxHeight = 0;
			break;
		case PLANT_STATE_UP:
			boxHeight = PLANT_BBOX_HEIGHT;
			break;
		default:
			boxHeight = PLANT_BBOX_HEIGHT / 2; //Tạm thời để vậy
		}*/
		left = x - boxWidth / 2;
		top = y - boxHeight / 2;
		right = left + boxWidth;
		bottom = top + boxHeight;
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		//this->stateHandler->Update(this, dt);
		mario->GetPosition(Mx, My);
		if (this->state == PLANT_STATE_HIDE) {
			if (abs(this->y - Mx) < 800) {
				SetState(PLANT_STATE_GO_UP);
				this->vy = 1;
			}
		}
		else if (this->state == PLANT_STATE_GO_UP) {

		}
		else if (this->state == PLANT_STATE_UP) {
			if (abs(this->y - Mx) > 800) {
				SetState(PLANT_STATE_GO_HIDE);
				this->vy = -1;
			}
		}
		else if (this->state == PLANT_STATE_GO_HIDE) {

		}
		CEnemy::Update(dt, coObjects);
	}

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	virtual void SetState(int state) override
	{
		this->SetState(state);
	};
	virtual void OnNoCollision(DWORD dt) override
	{
		x += vx * dt;
		y += vy * dt;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<LPPlantEnemy>(e->obj)) return;

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
	//virtual bool IsDeadState() override = 0;
};

typedef CPlantEnemy* LPPlantEnemy;