#include "RedParagoomba.h"
#include "GoombaAniIDs.h"
#include "CollisionEvent.h"

void CRedParagoomba::SetState(int state)
{
	if (state == GOOMBA_STATE_FLY)
	{
		float orgLeft = 0, orgTop = 0, orgRight = 0, orgBottom = 0;
		this->GetBoundingBox(orgLeft, orgTop, orgRight, orgBottom);

		this->vy = -GOOMBA_JUMP_VY;
		this->vx = -GOOMBA_WALKING_SPEED * 0.65f;
		CEnemy::SetState(state);

		float left = 0, top = 0, right = 0, bottom = 0;
		this->GetBoundingBox(left, top, right, bottom);
		float height = bottom - top;
		this->y = orgBottom - height / 2;
		return;
	}
	CRedGoomba::SetState(state);
	//if (state != GOOMBA_STATE_DIE);
	int dir = static_cast<int>(this->nx);
	this->ax = GOOMBA_ACCELERATION * dir;

}

void CRedParagoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->normalY == DirectionYAxisType::Top && GetTickCount64() - start_fly > GOOMBA_FLY_COOL_DOWN && this->state == GOOMBA_STATE_FLY)
	{
		this->vy = -GOOMBA_JUMP_VY;
		start_fly = GetTickCount64();
		this->vx = static_cast<int>(this->nx) * GOOMBA_WALKING_SPEED;
	}
	else if (this->state == GOOMBA_STATE_FLY && e->normalY != DirectionYAxisType::None)
	{
		LPPLAYSCENE ps = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		// chasing mario
		if (ps)
		{
			float marioX, marioY;
			ps->GetPlayer()->GetPosition(marioX, marioY);
			float distance = marioX - this->x;
			this->ax = (distance > 0 ? 1 : -1) * GOOMBA_ACCELERATION;
		}

	}
	this->nx = static_cast<DirectionXAxisType>(this->vx > 0 ? 1 : -1);
	this->vy = min(0, this->vy);
	if (abs(this->vx) > GOOMBA_MAX_SPEED) this->vx = static_cast<int>(this->nx) * GOOMBA_MAX_SPEED;

	if (e->normalX != DirectionXAxisType::None)
	{
		int dir = static_cast<int>(this->nx);
		this->nx = static_cast<DirectionXAxisType>(-dir);
		this->vx = -dir * GOOMBA_WALKING_SPEED;
		this->ax = vx * GOOMBA_ACCELERATION;
	}
}

void CRedParagoomba::Render()
{
	int aniId = -1;
	if (state == GOOMBA_STATE_FLY)
	{
		aniId = ID_ANI_RED_PARA_GOOMBA;
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		return;
	}
	CRedGoomba::Render();
}

void CRedParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxHeight, bboxWidth;

	if (GOOMBA_BBOX_FLY_HEIGHT)
	{
		bboxHeight = this->IsDeadState() ? GOOMBA_BBOX_HEIGHT_DIE : GOOMBA_BBOX_FLY_HEIGHT,
			bboxWidth = GOOMBA_BBOX_FLY_WIDTH;
		left = x - bboxWidth / 2;
		top = y - bboxHeight / 2;
		right = left + bboxWidth;
		bottom = top + bboxHeight;
		return;
	}
	CRedGoomba::GetBoundingBox(left, top, right, bottom);
}