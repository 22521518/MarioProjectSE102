#pragma once
#include "KoopaShellState.h"
#include "KoopaAniIDs.h"

// Green Koopa
class CGreenKoopaShellIdleState :
	public CKoopaShellState {
public:
	CGreenKoopaShellIdleState(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_GREEN_KOOPA_SHELL_IDLE; }
};

class CGreenKoopaShellIdleStateRunOutOfTime :
	public CKoopaShellState {
public:
	CGreenKoopaShellIdleStateRunOutOfTime(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_GREEN_KOOPA_SHELL_IDLE_OUT_TIME; }
};

class CGreenKoopaShellIdleStateRunOutOfTimeHold :
	public CKoopaShellState {
public:
	CGreenKoopaShellIdleStateRunOutOfTimeHold(LPKOOPA koopa) : CKoopaShellState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_GREEN_KOOPA_SHELL_IDLE_OUT_TIME_HOLD; }
};

class CGreenKoopaShellMoveState :
	public CKoopaShellMoveState {
public:
	CGreenKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e) : CKoopaShellMoveState(koopa, e) {};

	virtual int GetAnimationID(LPKOOPA koopa) { return ID_ANI_GREEN_KOOPA_SHELL_MOVE; }
};

typedef CGreenKoopaShellIdleState* LPREDKOOPASHELLIDLE;
typedef CGreenKoopaShellMoveState* LPREDKOOPASHELLMOVE;