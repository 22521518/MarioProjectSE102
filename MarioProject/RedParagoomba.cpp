#include "RedParagoomba.h"
#include "GoombaAniIDs.h"
#include "CollisionEvent.h"

void CRedParagoomba::SetState(int state)
{
	if (state == GOOMBA_STATE_FLY)
	{
		this->vy = -GOOMBA_JUMP_VY;
		this->vx = -GOOMBA_WALKING_SPEED * 0.65;
		return;
	}
	CRedGoomba::SetState(state);
}

void CRedParagoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->normalY == DirectionYAxisType::Top && GetTickCount64() - start_fly > GOOMBA_FLY_COOL_DOWN)
	{
		DebugOut(L"DM: %d, %d", GetTickCount64() - start_fly > GOOMBA_FLY_COOL_DOWN, start_fly);
		this->vy = -GOOMBA_JUMP_VY;
		start_fly = GetTickCount64();
		int dir = static_cast<int>(this->nx);
		this->vx = dir * GOOMBA_WALKING_SPEED;
	}
	else
	{
		this->vx = GOOMBA_WALKING_SPEED;
		int dir = static_cast<int>(this->nx);
		this->vx *= dir;
	}
	this->vy = min(0, this->vy);

	if (e->normalX != DirectionXAxisType::None)
	{
		int dir = static_cast<int>(this->nx);
		this->nx = static_cast<DirectionXAxisType>(-dir);
		this->vx = -dir * GOOMBA_WALKING_SPEED;
	}
}

void CRedParagoomba::Render()
{
	int aniId = -1;
	if (state == GOOMBA_STATE_FLY)
	{
		aniId = ID_ANI_RED_PARA_GOOMBA;
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		RenderBoundingBox();
		return;
	}
	CRedGoomba::Render();
}

void CRedParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxHeight = this->IsDeadState() ? GOOMBA_BBOX_HEIGHT_DIE : GOOMBA_BBOX_FLY_HEIGHT,
		bboxWidth = GOOMBA_BBOX_FLY_WIDTH;

	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}