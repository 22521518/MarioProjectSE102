#pragma once
#include "Character.h"
#include "CollidableWithMario.h"
#include "KoopaState.h"
#include "KoopaShellState.h"
#include "KoopaConfig.h"
#include "KoopaStateIDs.h"
#include "Goomba.h"

class CKoopa :
	public CCharacter, public CCollidableWithMario 
{
private:
	bool IsOutOfTime(ULONGLONG time);
	bool IsNearOutOfTime(ULONGLONG time);	

protected:
	LPKOOPASTATE stateHandler = NULL;
	ULONGLONG die_start = -1;
public:
	CKoopa(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = KOOPA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = KOOPA_STATE_WALKING);

	// game object method
	virtual void Render();

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	//virtual void SetState(int state) = 0;
	//virtual void OnNoCollision(DWORD dt) override; // use default
	virtual void SetState(int state) { CInteractiveObject::SetState(state); };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;

	// character object method
	virtual bool IsDeadState() override { return IsShellIdle() || IsShellMove(); }

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;

	// koopa method
	virtual void SetState(int state, LPCOLLISIONEVENT e) = 0;
	virtual bool IsShellState() { return this->IsShellIdle() || this->IsShellMove(); }
	virtual bool IsShellMove() { return this->state == KOOPA_STATE_SHELL_MOVE; }
	virtual bool IsShellIdle() { return (this->state == KOOPA_STATE_SHELL_IDLE || this->state == KOOPA_STATE_SHELL_IDLE_OUT_TIME); }

	friend class CKoopaState;
	friend class CRedKoopaState;
	friend class CKoopaShellState;
	friend class CKoopaShellMoveState;
};

typedef CKoopa* LPKOOPA;