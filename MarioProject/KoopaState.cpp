#include "Koopa.h"
#include "debug.h"
#include"PhysicalObject.h"
#include "KoopaState.h"
#include "RedKoopaState.h"
#include "CollisionEvent.h"

#pragma region KOOPA_FAMILY
CKoopaState::CKoopaState(LPKOOPA koopa)
{
	int nxValue = static_cast<int>(koopa->nx);
	koopa->nx = koopa->nx == DirectionXAxisType::Left ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	koopa->vx = nxValue * KOOPA_WALKING_SPEED;
}

void CKoopaState::ChangeDirection(LPKOOPA koopa, float speed)
{
	int nxValue = static_cast<int>(koopa->nx);
	nxValue = nxValue != 0 ? nxValue : 1;
	koopa->nx = static_cast<DirectionXAxisType>(-nxValue);
	koopa->vx = -nxValue * speed;

	if (!koopa->IsShellState()) koopa->SetState(KOOPA_STATE_WALKING);
}

void CKoopaState::OnNoCollision(LPKOOPA koopa, DWORD dt)
{
	koopa->x += koopa->vx * dt;
	koopa->y += koopa->vy * dt;
}

void CKoopaState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<LPKOOPA>(e->obj)) return;


	if (e->normalY != DirectionYAxisType::None)
	{
		koopa->vy = 0;
	}
	if (e->normalX != DirectionXAxisType::None)
	{	
		this->ChangeDirection(koopa);
	}
}

void CKoopaState::GetBoundingBox(float& width, float& height)
{
	width = KOOPA_BBOX_WIDTH;
	height = KOOPA_BBOX_HEIGHT;
}
#pragma endregion