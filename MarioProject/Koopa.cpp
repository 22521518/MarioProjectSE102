#include <algorithm>

#include "Koopa.h"
#include "CollisionEvent.h"

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

CKoopa::CKoopa(float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state)
	: CCharacter(x, y, vx, vy, ax, ay, nx, state)
{
	this->die_start = -1;
	this->stateHandler = NULL;
	SetState(state);
}

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
		else if (!this->IsShellState())
		{
			this->die_start = GetTickCount64();
			this->SetState(KOOPA_STATE_SHELL_IDLE);
		}
	}
	else if (this->IsShellIdle()) 
	{
		this->SetState(KOOPA_STATE_SHELL_MOVE, e);
		this->die_start = -1;
	}
}
#pragma endregion

#pragma region INTERACTIVE_OBJECT_METHOD
void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
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
	// 
	//this->stateHandler->Update(this, dt);

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

	CCharacter::Update(dt, coObjects);
}
#pragma endregion

#pragma region GAME_OBJECT_METHOD
void CKoopa::Render()
{
	int aniId = this->stateHandler->GetAnimationID(this);
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
#pragma endregion