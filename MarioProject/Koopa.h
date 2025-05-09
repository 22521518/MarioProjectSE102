#pragma once
#include "Enemy.h"
#include "CollidableWithMario.h"
#include "KoopaState.h"
#include "KoopaShellState.h"
#include "KoopaConfig.h"
#include "KoopaStateIDs.h"
#include "Goomba.h"
#include "DestroyableObject.h"

class CKoopa :
	public CEnemy, public CCollidableWithMario, public CDestroyableObject
{
private:
	const DirectionYAxisType originNY;

	bool IsOutOfTime(ULONGLONG time);
	bool IsNearOutOfTime(ULONGLONG time);	

protected:
	DirectionYAxisType ny = DirectionYAxisType::Bottom;

	LPKOOPASTATE stateHandler = NULL;
	ULONGLONG die_start = -1;
public:
	CKoopa(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = KOOPA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = KOOPA_STATE_WALKING) : CEnemy(x, y, vx, vy, ax, ay, nx, state), die_start(-1), stateHandler(nullptr), originNY(ny)
	{
		SetState(state);
	};

	// game object method
	void Render();
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
	bool IsDeadState() override { return IsShellIdle(); }

	// collidable with mario interface
	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;

	// koopa method
	virtual void SetState(int state, LPCOLLISIONEVENT e) = 0;
	virtual bool IsShellState() { return this->IsShellIdle() || this->IsShellMove(); }
	virtual bool IsShellMove() { return this->state == KOOPA_STATE_SHELL_MOVE; }
	virtual bool IsShellIdle() { return (this->state == KOOPA_STATE_SHELL_IDLE || this->state == KOOPA_STATE_SHELL_IDLE_OUT_TIME); }
	virtual bool IsParatroopaState() { return this->state == KOOPA_STATE_PARATROOPA; }

	// interactive with side methods
	//virtual void OnSideCollisionBehavior(LPCOLLISIONEVENT e) override;
	//virtual void GetObjectBoundingBox(float& left, float& top, float& right, float& bottom) override;
	//virtual DirectionXAxisType GetObjectCurrentDirectionX() override;

	void OnDestroy(LPCOLLISIONEVENT e) { this->Delete(); }

	void ResetState() override
	{
		CEnemy::ResetState();
		this->die_start = -1;
		this->ny = originNY;
		SetState(this->state);
	};

	friend class CKoopaState;
	friend class CRedKoopaState;
	friend class CRedKoopaParatroopaState;
	friend class CGreenKoopaParatroopaState;
	friend class CGreenKoopaState;
	friend class CKoopaShellState;
	friend class CKoopaShellMoveState;
};

typedef CKoopa* LPKOOPA;