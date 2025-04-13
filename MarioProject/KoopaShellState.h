#pragma once
#include "KoopaState.h"
#include "KoopaAniIDs.h"

class CKoopaShellState :
	public CKoopaState {
public:
	CKoopaShellState() {};
	CKoopaShellState(LPKOOPA koopa);
	virtual void Update(LPKOOPA koopa, DWORD dt) {};
	virtual int GetAnimationID(LPKOOPA koopa) = 0;
	virtual void GetBoundingBox(float& width, float& height);
};

class CKoopaShellMoveState :
	public CKoopaShellState {
public:
	CKoopaShellMoveState() {};
	CKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e);
	virtual void Update(LPKOOPA koopa, DWORD dt) {};
	virtual int GetAnimationID(LPKOOPA koopa) = 0;
};

// Red Koopa
class CRedKoopaShellIdleState :
	public CKoopaShellState {
public:
	CRedKoopaShellIdleState(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_IDLE; }
};

class CRedKoopaShellMoveState :
	public CKoopaShellMoveState {
public:
	CRedKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e) : CKoopaShellMoveState(koopa, e) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_MOVE; }
};

typedef CKoopaShellState* LPKOOPASHELL;
typedef CRedKoopaShellIdleState* LPREDKOOPASHELLIDLE;
typedef CRedKoopaShellMoveState* LPREDKOOPASHELLMOVE;
