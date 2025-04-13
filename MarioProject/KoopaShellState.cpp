#include "KoopaShellState.h"
#include "KoopaConfig.h"
#include "CollisionEvent.h"
#include "Koopa.h"

CKoopaShellState::CKoopaShellState(LPKOOPA koopa) 
{
	koopa->die_start = GetTickCount64();
	if (!koopa->IsShellState())
		koopa->y += (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
	koopa->SetSpeed(0, 0);
	koopa->ay = 0;
}

void CKoopaShellState::GetBoundingBox(float& width, float& height)
{
	height = SHELL_BBOX_HEIGHT,
		width = SHELL_BBOX_WIDTH;
}

#pragma region SHELL_MOVE
CKoopaShellMoveState::CKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e)
    : CKoopaShellState(koopa)
{
    float vx = 0;
    int eNXValue = static_cast<int>(e->normalX);
    if (e != nullptr)
    {
        vx = -eNXValue * KOOPA_SHELL_SPEED;
    
    }
    else
    {
        vx = KOOPA_SHELL_SPEED;
    }

    koopa->SetSpeed(vx, 0);
}
#pragma endregion