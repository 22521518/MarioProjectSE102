#include "Goomba.h"
#include "GoombaAniIDs.h"
#include "Collision.h"

#pragma region COLLIDABLE_MARIO_METHOD
void CGoomba::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	// jump on top >> kill Goomba and deflect a bit 
	mario->OnCollisionWithGoomba(this, e);
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (state == GOOMBA_STATE_FLY)
		{
			this->SetState(GOOMBA_STATE_WALKING);
		}
		else if (!this->IsDeadState())
		{
			this->SetState(GOOMBA_STATE_DIE);
		}
	}
	
}
#pragma endregion

#pragma region INTERACTIVE_OBJECT_METHOD
void CGoomba::SetState(int state)
{
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
	CEnemy::SetState(state);
}

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->normalY != DirectionYAxisType::None )
	{
		vy = 0;
	}
	if (e->normalX != DirectionXAxisType::None)
	{
		vx = -vx;
	}	
}
#pragma endregion

#pragma region PHYSICAL_OBJECT_METHOD
void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxHeight = this->IsDeadState() ? GOOMBA_BBOX_HEIGHT_DIE : GOOMBA_BBOX_HEIGHT,
		bboxWidth = GOOMBA_BBOX_WIDTH;

	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CGoomba::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CEnemy::Update(dt, coObjects);
}
#pragma endregion

#pragma region GAME_OBJECT_METHOD
void CGoomba::Render()
{
	int aniId = -1; 
	if (state == GOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_GOOMBA_WALKING;
	}
	else if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
#pragma endregion