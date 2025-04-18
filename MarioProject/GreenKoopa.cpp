#include "GreenKoopa.h"
#include "GreenKoopaShellState.h"
#include "GreenKoopaState.h"

void CGreenKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_SHELL_IDLE:
		delete this->stateHandler;
		this->stateHandler = new CGreenKoopaShellIdleState(this);
		break;
	case KOOPA_STATE_SHELL_IDLE_OUT_TIME:
		delete this->stateHandler;
		this->stateHandler = new CGreenKoopaShellIdleStateRunOutOfTime(this);
		break;
	case KOOPA_STATE_SHELL_MOVE:
		throw std::runtime_error("Invalid state passed !Move state should be in SetState(int, LPCOLLISIONEVENT)");
		break;
	case KOOPA_STATE_WALKING:
		delete this->stateHandler;
		this->stateHandler = new CGreenKoopaState(this);
		break;
	}
	this->state = state;
}

void CGreenKoopa::SetState(int state, LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVE) {
		delete this->stateHandler;
		this->stateHandler = new CGreenKoopaShellMoveState(this, e);
		this->state = state;
	}
	else
	{
		throw std::runtime_error("Invalid state passed to Koopa::SetState(int, LPCOLLISIONEVENT)");
	}
}

