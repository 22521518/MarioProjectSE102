#pragma once
#include "Enemy.h"
#include "GoombaConfig.h"
#include "GoombaStateIDs.h"
#include "CollidableWithMario.h"

class CGoomba :
	public CEnemy, public CCollidableWithMario
{
protected:
	ULONGLONG die_start = -1;

public:
	CGoomba(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = GOOMBA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = GOOMBA_STATE_WALKING) : CEnemy(x, y, vx, vy, ax, ay, nx, state), die_start(-1)
	{
		SetState(GOOMBA_STATE_WALKING);
	};;

	// game object method
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

	// physical object method
	void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	int IsBlocking() override { return 0; };
	int IsCollidable() override { return 1; };

	// interactive object method
	void SetState(int state) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	// character object method
	bool IsDeadState() override { return this->state == GOOMBA_STATE_DIE; }

	// collidable with mario interface
	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;

	// base game object
	void ResetState() override
	{
		CEnemy::ResetState();
		die_start = -1;
	}

};

typedef CGoomba* LPGOOMBA;

