#include "Koopa.h"
#include"PhysicalObject.h"
#include "KoopaState.h"
#include "CollisionEvent.h"

void CKoopaState::ChangeDirection(LPKOOPA koopa, ULONGLONG speed)
{
	int nxValue = static_cast<int>(koopa->nx);
	koopa->nx = static_cast<DirectionXAxisType>(-nxValue);
	koopa->vx = nxValue * speed;
}

CKoopaState::CKoopaState(LPKOOPA koopa)
{
	int nxValue = static_cast<int>(koopa->nx);
	koopa->nx = koopa->nx == DirectionXAxisType::Left ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	koopa->vx = nxValue * KOOPA_WALKING_SPEED;
}

void CKoopaState::Update(LPKOOPA koopa, DWORD dt)
{
	koopa->vy += koopa->ay * dt;
	//koopa->vx += koopa->ax * dt;
	koopa->vx += koopa->ax * dt;
}

void CKoopaState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<LPKOOPA>(e->obj)) return;
	if (dynamic_cast<LPCHARACTER>(e->obj)) return;

	if (e->normalY != DirectionYAxisType::None)
	{
		koopa->vy = 0;
	}
	if (e->normalX != DirectionXAxisType::None)
	{
		
		if (!koopa->IsShellState())
		{
			this->ChangeDirection(koopa, KOOPA_WALKING_SPEED);
			koopa->SetState(KOOPA_STATE_WALKING);
		}
		else if (koopa->IsShellMove())
		{
			this->ChangeDirection(koopa, KOOPA_SHELL_SPEED);
		}
		
	}
}

void CKoopaState::GetBoundingBox(float& width, float& height)
{
	width = KOOPA_BBOX_WIDTH;
	height = KOOPA_BBOX_HEIGHT;
}
