#pragma once
#include "Character.h"
#include "CollidableWithMario.h"
#include "KoopaState.h"
#include "KoopaConfig.h"

class CKoopa : 
	public CCharacter, public CCollidableWithMario {

	LPKOOPASTATE stateHandler;
protected:
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
	virtual void SetState(int state) override;
	//virtual void OnNoCollision(DWORD dt) override; // use default
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;

	// character object method
	virtual bool IsDeadState() override { return this->state == GOOMBA_STATE_DIE; }

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;


};