#include "KoopaShellState.h"
#include "KoopaConfig.h"
#include "CollisionEvent.h"
#include "Koopa.h"
#include "BrickSuperItem.h"
#include "Brick.h"

CKoopaShellState::CKoopaShellState(LPKOOPA koopa) 
{
    if (!koopa->IsShellState())
    {
        koopa->y += (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
    }
	koopa->SetSpeed(0, 0);
    koopa->SetAcceleration(0, SHELL_GRAVITY);
}

//void CKoopaShellState::Update(LPKOOPA koopa, DWORD dt)
//{
//    koopa->vy += koopa->ay * dt;
//}

void CKoopaShellState::GetBoundingBox(float& width, float& height)
{
	height = SHELL_BBOX_HEIGHT,
		width = SHELL_BBOX_WIDTH;
}

#pragma region SHELL_MOVE
void CKoopaShellMoveState::ChangeDirection(LPKOOPA koopa, float speed)
{
    CKoopaState::ChangeDirection(koopa, KOOPA_SHELL_SPEED);
}

CKoopaShellMoveState::CKoopaShellMoveState(LPKOOPA koopa, LPCOLLISIONEVENT e)
    : CKoopaShellState(koopa)
{
    float vx = KOOPA_SHELL_SPEED;

    if (e != nullptr && e->normalX != DirectionXAxisType::None)
    {
        int eNXValue = static_cast<int>(e->normalX);
        vx *= -eNXValue ;
    }

    koopa->SetSpeed(vx, 0);
    koopa->SetAcceleration(0, KOOPA_GRAVITY);
}
void CKoopaShellMoveState::OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
    if (koopa->IsShellMove())
    {
        LPDESTROYABLEOBJECT destroyableObj = dynamic_cast<LPDESTROYABLEOBJECT>(e->obj);
        if (destroyableObj)
        {
            if (dynamic_cast<LPBRICKSUPERITEM>(destroyableObj)) destroyableObj->OnDestroy(e);
            if (dynamic_cast<LPBRICK>(destroyableObj) && e->normalX == DirectionXAxisType::None) return;
            destroyableObj->OnDestroy(e);
        }
        //koopa->OnCollisionWith(e);
    }
    CKoopaState::OnCollisionWith(koopa, e);
}
#pragma endregion