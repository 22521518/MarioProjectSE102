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
	DebugOutTitle(L"vy: %f, ay: %f", koopa->vy, koopa->ay);
	koopa->ay = -KOOPA_PARATROOPA_ACCELERATION_Y;
	if (koopa->vy > KOOPA_MAX_VY)
	{
		koopa->vy = KOOPA_MAX_VY;
		koopa->ay = -KOOPA_PARATROOPA_ACCELERATION_Y;
	}
	else if (koopa->vy < -KOOPA_MAX_VY)
	{
		koopa->vy = -KOOPA_MAX_VY;
		koopa->ay = KOOPA_PARATROOPA_ACCELERATION_Y;
	}
	CKoopaState::OnNoCollision(koopa, dt);
}

void CRedKoopaParatroopaState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	koopa->ay = -KOOPA_PARATROOPA_ACCELERATION_Y;
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
