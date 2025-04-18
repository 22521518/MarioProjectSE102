#include "RedKoopaParatroopaState.h"
#include "CollisionEvent.h"

CRedKoopaParatroopaState::CRedKoopaParatroopaState(LPKOOPA koopa)
{
	int nyValue = static_cast<int>(koopa->ny);
	koopa->ny = koopa->ny == DirectionYAxisType::Top ?
		DirectionYAxisType::Top : DirectionYAxisType::Bottom;
	koopa->vy = 0;
	koopa->ay = nyValue * KOOPA_WALKING_SPEED;
}

void CRedKoopaParatroopaState::ChangeDirection(LPKOOPA koopa, float speed = KOOPA_PARATROOPA_ACCELERATION_Y)
{
	koopa->ay = -koopa->ay;
}

void CRedKoopaParatroopaState::OnNoCollision(LPKOOPA koopa, DWORD dt)
{
	CKoopaState::OnNoCollision(koopa, dt);
	if (koopa->vy > maxVy)
	{
		koopa->vy = maxVy;
		koopa->ay = -KOOPA_PARATROOPA_ACCELERATION_Y;
	}
	else if (koopa->vy < -maxVy)
	{
		koopa->vy = -maxVy;
		koopa->ay = KOOPA_PARATROOPA_ACCELERATION_Y;
	}
}

void CRedKoopaParatroopaState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<LPKOOPA>(e->obj)) return;


	if (e->normalY != DirectionYAxisType::None)
	{
		koopa->vy = 0;
		this->ChangeDirection(koopa);
	}
	if (e->normalX != DirectionXAxisType::None)
	{
		koopa->vx = 0;
	}
}
