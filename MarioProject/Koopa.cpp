#include <algorithm>

#include "Koopa.h"
#include "CollisionEvent.h"
#include "DestroyableObject.h"
#include "Brick.h"
#include "BrickSuperItem.h"
#include "CheckingSideObject.h"

bool CKoopa::IsOutOfTime(ULONGLONG time)
{
	return time > KOOPA_DIE_TIMEOUT;
}

bool CKoopa::IsNearOutOfTime(ULONGLONG time)
{
	ULONGLONG litmitTime = static_cast<ULONGLONG>(KOOPA_DIE_TIMEOUT * 0.70);
	if (litmitTime < 1000) litmitTime = 1000;
	return litmitTime < time  && time < KOOPA_DIE_TIMEOUT;
}

//#pragma region SIDE_COLLISION_BEHAVIOR
//void CKoopa::OnSideCollisionBehavior(LPCOLLISIONEVENT e)
//{
//	if (!this->IsShellMove()) return;
//	LPDESTROYABLEOBJECT destroyableObj = dynamic_cast<LPDESTROYABLEOBJECT>(e->obj);
//	if (destroyableObj)
//	{
//		if (dynamic_cast<LPBRICKSUPERITEM>(destroyableObj)) destroyableObj->OnDestroy(e);
//		if (dynamic_cast<LPBRICK>(destroyableObj) && e->normalX == DirectionXAxisType::None) return;
//		destroyableObj->OnDestroy(e);
//	}
//	this->OnCollisionWith(e);
//}
//
//void CKoopa::GetObjectBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	this->GetBoundingBox(left, top, right, bottom);
//}
//
//DirectionXAxisType CKoopa::GetObjectCurrentDirectionX()
//{
//	return this->GetNX();
//}
//
//#pragma endregion
#pragma region COLLIDABLE_MARIO_METHOD
void CKoopa::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	// jump on top >> kill RedKoop and deflect a bit 
	mario->OnCollisionWithKoopa(this, e);
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (this->IsParatroopaState())
		{
			this->SetState(KOOPA_STATE_WALKING);
		}
		else if (this->IsShellMove() || this->state == KOOPA_STATE_WALKING)
		{
			this->die_start = GetTickCount64();
			this->SetState(KOOPA_STATE_SHELL_IDLE);
		}
	}
	else if (this->IsShellIdle() && GetTickCount64() - die_start > 50) 
	{
		mario->OnKick();
		this->SetState(KOOPA_STATE_SHELL_MOVE, e);
		this->die_start = -1;
	}
}
#pragma endregion
#pragma region HOLDABLE_MARIO_METHOD
void CKoopa::OnMarioRelease(LPMARIO mario)
{
	if (this->state != KOOPA_STATE_WALKING) 
	{
		DebugOut(L"direction %d\n", mario->GetNX());
		int curDir = static_cast<int>(mario->GetNX());
		LPCOLLISIONEVENT e = new CCollisionEvent(0, static_cast<DirectionXAxisType>(-curDir), DirectionYAxisType::None, 0, 0,
			nullptr, nullptr);
		this->SetState(KOOPA_STATE_SHELL_MOVE, e);
		delete e;
	}

	this->die_start = -1;
	this->isHeld = false;
	float marioLeft = 0, marioTop = 0, marioRight = 0, marioBottom = 0;
	mario->GetBoundingBox(marioLeft, marioTop, marioRight, marioBottom);
	float bbWidth, bbHeight;
	this->stateHandler->GetBoundingBox(bbWidth, bbHeight);
	this->y = marioBottom - bbHeight;
}
#pragma endregion

#pragma region INTERACTIVE_OBJECT_METHOD
void CKoopa::SetState(int state)
{
	CInteractiveObject::SetState(state);
}
void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isHeld) return;
	this->stateHandler->OnCollisionWith(this, e);
}
#pragma endregion

#pragma region PHYSICAL_OBJECT_METHOD
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxHeight, bboxWidth;
	this->stateHandler->GetBoundingBox(bboxWidth, bboxHeight);

	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}
void CKoopa::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	if (this->IsShellIdle())
	{
		ULONGLONG timeFromDie = GetTickCount64() - die_start;
		if (IsOutOfTime(timeFromDie))
		{
			this->SetState(KOOPA_STATE_WALKING);
			this->y -= (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
			die_start = -1;
			return;
		}
		else if (IsNearOutOfTime(timeFromDie))
		{
			this->SetState(KOOPA_STATE_SHELL_IDLE_OUT_TIME);
		}
	}
	
	if (isHeld) return;
	CEnemy::Update(dt, coObjects);
}
#pragma endregion

#pragma region GAME_OBJECT_METHOD
void CKoopa::Render()
{
	int aniId = this->stateHandler->GetAnimationID(this);
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
#pragma endregion