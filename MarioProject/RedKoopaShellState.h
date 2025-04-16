#pragma once
#include "KoopaShellState.h"
#include "KoopaAniIDs.h"

// Red Koopa
class CRedKoopaShellIdleState :
	public CKoopaShellState {
public:
	CRedKoopaShellIdleState(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_IDLE; }
};

class CRedKoopaShellIdleStateRunOutOfTime :
	public CKoopaShellState {
public:
	CRedKoopaShellIdleStateRunOutOfTime(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_IDLE_OUT_TIME; }
};

class CRedKoopaShellIdleStateRunOutOfTimeHold :
	public CKoopaShellState {
public:
	CRedKoopaShellIdleStateRunOutOfTimeHold(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_IDLE_OUT_TIME_HOLD; }
};

class CRedKoopaShellMoveState :
	public CKoopaShellMoveState {
public:
	CRedKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e) : CKoopaShellMoveState(koopa, e) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_MOVE; }
};

typedef CRedKoopaShellIdleState* LPREDKOOPASHELLIDLE;
typedef CRedKoopaShellMoveState* LPREDKOOPASHELLMOVE;