#include "RedKoopa.h"
#include "RedKoopaShellState.h"
#include "RedKoopaState.h"

void CRedKoopa::SetState(int state) 
{
	switch (state)
	{
	case KOOPA_STATE_SHELL_IDLE:
	{
		delete this->stateHandler;
		this->stateHandler = new CRedKoopaShellIdleState(this);
		break;
	}
	case KOOPA_STATE_SHELL_IDLE_OUT_TIME:
	{
		delete this->stateHandler;
		this->stateHandler = new CRedKoopaShellIdleStateRunOutOfTime(this);
		break;
	}
	case KOOPA_STATE_SHELL_MOVE:
	{
		throw std::runtime_error("Invalid state passed !Move state should be in SetState(int, LPCOLLISIONEVENT)");
		break;
	}
	case KOOPA_STATE_WALKING:
	{
		if (this->state == KOOPA_STATE_SHELL_IDLE_OUT_TIME)
		{
			float left, top, right, bottom;
			this->GetBoundingBox(left, top, right, bottom);

			delete this->stateHandler;
			this->stateHandler = new CRedKoopaState(this);

			float currentHeight, currentWidth;
			this->stateHandler->GetBoundingBox(currentWidth, currentHeight);
			this->y = bottom - currentHeight / 2;
			break;
		}
		delete this->stateHandler;
		this->stateHandler = new CRedKoopaState(this);
		break;
	}}
	//this->state = state;
	CKoopa::SetState(state);
}

void CRedKoopa::SetState(int state, LPCOLLISIONEVENT e)
{
	if (state == KOOPA_STATE_SHELL_MOVE) {
		delete this->stateHandler;
		this->stateHandler = new CRedKoopaShellMoveState(this, e);
		//this->state = state;
		CKoopa::SetState(state);
	}
	else 
	{
		throw std::runtime_error("Invalid state passed to Koopa::SetState(int, LPCOLLISIONEVENT)");
	}
}

void CRedKoopa::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	CKoopa::Update(dt, coObjects);
	if (this->isFirstLanded && !this->IsShellState())
	{
		float left, top, right, bottom;
		this->GetBoundingBox(left, top, right, bottom);
		float width = right - left,
			height = bottom - top;

		LPCHECKINGEDGEOBJECT checkingEdgeObj 
			= new CCheckingEdgeObject(this, x, y, vx, vy, ax, ay, nx);
		checkingEdgeObj->Update(dt, coObjects);
		delete checkingEdgeObj;
	}
}

void CRedKoopa::OnEdgeBehavior(DWORD dt)
{
	if (this->isFirstLanded && !this->IsShellState())
	{
	  	this->stateHandler->ChangeDirection(this);
	}
}
