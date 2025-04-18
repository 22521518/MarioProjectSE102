#include "RedKoopaState.h"
#include "RedKoopa.h"
#include "CollisionEvent.h"

void CRedKoopaState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	CKoopaState::OnCollisionWith(koopa, e);

	LPREDKOOPA redKoopa = dynamic_cast<LPREDKOOPA>(koopa);
	if (e->normalY != DirectionYAxisType::None && !redKoopa->isFirstLanded)
	{
		redKoopa->isFirstLanded = true;
	}

}
