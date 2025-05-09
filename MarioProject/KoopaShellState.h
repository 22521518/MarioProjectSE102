#pragma once
#include "KoopaState.h"

class CKoopaShellState :
	public CKoopaState {
public:
	CKoopaShellState() {};
	CKoopaShellState(LPKOOPA koopa);
	//virtual void Update(LPKOOPA koopa, DWORD dt);
	virtual int GetAnimationID(LPKOOPA koopa) = 0;
	virtual void GetBoundingBox(float& width, float& height) override;
};

class CKoopaShellMoveState :
	public CKoopaShellState {
protected:
	virtual void ChangeDirection(LPKOOPA koopa, float speed) override;
public:
	CKoopaShellMoveState() {};
	CKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e);
	void OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e);
	virtual int GetAnimationID(LPKOOPA koopa) = 0;
};

typedef CKoopaShellState* LPKOOPASHELL;
