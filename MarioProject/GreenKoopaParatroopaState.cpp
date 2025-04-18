#include "GreenKoopaParatroopaState.h"
#include "CollisionEvent.h"

CGreenKoopaParatroopaState::CGreenKoopaParatroopaState(LPKOOPA koopa, int state)
	: CKoopaState(koopa)
{
	koopa->vy = -KOOPA_JUMP_VY;
	this->state = state;
}

void CGreenKoopaParatroopaState::ChangeDirection(LPKOOPA koopa, float speed)
{
	int nxValue = static_cast<int>(koopa->nx);
	nxValue = nxValue != 0 ? nxValue : 1;
	koopa->nx = static_cast<DirectionXAxisType>(-nxValue);
	koopa->vx = -nxValue * speed;
}

void CGreenKoopaParatroopaState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<LPKOOPA>(e->obj)) return;

	
	if (e->normalY == DirectionYAxisType::Top)
	{
		koopa->vy = -KOOPA_JUMP_VY;
	} 
	else 
	{
		koopa->vy = 0;
	}

	if (e->normalX != DirectionXAxisType::None)
	{
		this->ChangeDirection(koopa);
	}
}
