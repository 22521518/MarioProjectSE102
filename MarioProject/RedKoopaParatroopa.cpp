#include "RedKoopaParatroopa.h"
#include "RedKoopaParatroopaState.h"
#include "CollisionEvent.h"

void CRedKoopaParatroopa::SetState(int state)
{
	if (state == KOOPA_STATE_PARATROOPA) {
		this->stateHandler = new CRedKoopaParatroopaState(this);
	}
	CRedKoopa::SetState(state);
}

void CRedKoopaParatroopa::OnNoCollision(DWORD dt)
{
	this->stateHandler->OnNoCollision(this, dt);
}