#pragma once
#include "KoopaShellState.h"
#include "KoopaAniIDs.h"

// Red Koopa Idle Shell
class CRedKoopaShellIdleState :
	public CKoopaShellState {
public:
	CRedKoopaShellIdleState(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_IDLE; }
};

// Red Koopa Idle Run Out Of Time Shell
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

// Red Koopa Moving Shell
class CRedKoopaShellMoveState :
	public CKoopaShellMoveState {
public:
	CRedKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e) : CKoopaShellMoveState(koopa, e) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_RED_KOOPA_SHELL_MOVE; }
};

typedef CRedKoopaShellIdleState* LPREDKOOPASHELLIDLE;
typedef CRedKoopaShellMoveState* LPREDKOOPASHELLMOVE;