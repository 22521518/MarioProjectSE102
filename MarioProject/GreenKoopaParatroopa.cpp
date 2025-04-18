#include "GreenKoopaParatroopa.h"
#include "GreenKoopaParatroopaState.h"

void CGreenKoopaParatroopa::SetState(int state)
{
	if (state == KOOPA_STATE_PARATROOPA) {
		this->stateHandler = new CGreenKoopaParatroopaState(this);
	}
	else if (state == GREEN_KOOPA_STATE_PARATROOPA_JUMP || state == GREEN_KOOPA_STATE_PARATROOPA_WALK)
	{
		this->stateHandler = new CGreenKoopaParatroopaState(this, state);
	}
	CGreenKoopa::SetState(state);
}

void CGreenKoopaParatroopa::OnNoCollision(DWORD dt)
{
	this->stateHandler->OnNoCollision(this, dt);
}
