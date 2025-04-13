#include "RedKoopa.h"

void CRedKoopa::SetState(int state) 
{
	switch (state)
	{
	case KOOPA_STATE_SHELL_IDLE:
		this->stateHandler = new CRedKoopaShellIdleState(this);
		break;
	case KOOPA_STATE_SHELL_MOVE:
		throw std::runtime_error("Invalid state passed !Move state should be in SetState(int, LPCOLLISIONEVENT)");
		break;
	case KOOPA_STATE_WALKING:
		this->stateHandler = new CRedKoopaState(this);
		break;
	}
	this->state = state;
}

void CRedKoopa::SetState(int state, LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVE) {
		this->stateHandler = new CRedKoopaShellMoveState(this, e);
	}
	else 
	{
		throw std::runtime_error("Invalid state passed to Koopa::SetState(int, LPCOLLISIONEVENT)");
	}
}

