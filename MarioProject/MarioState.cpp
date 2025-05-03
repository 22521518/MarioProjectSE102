#include "MarioState.h"
#include "Mario.h"

void CMarioState::OnRun(LPMARIO mario, bool isLeft)
{
	if (mario->isSitting) return;
	mario->nx = isLeft ? 
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	int normX = static_cast<int>(mario->nx);
	mario->maxVx = normX * MARIO_RUNNING_SPEED;
	mario->ax = normX * MARIO_ACCEL_RUN_X;
}
void CMarioState::OnWalk(LPMARIO mario, bool isLeft)
{
	if (mario->isSitting) return;
	mario->nx = isLeft ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	int normX = static_cast<int>(mario->nx);
	mario->maxVx = normX * MARIO_WALKING_SPEED;
	mario->ax = normX * MARIO_ACCEL_WALK_X;
}
void CMarioState::OnJump(LPMARIO mario)
{
	if (mario->isSitting) return;
	if (mario->isOnPlatform)
	{
		mario->vy = abs(mario->vx) == MARIO_RUNNING_SPEED ? 
			-MARIO_JUMP_RUN_SPEED_Y : -MARIO_JUMP_SPEED_Y;
	}
}
void CMarioState::OnReleaseJump(LPMARIO mario)
{
	if (mario->vy < 0)
	{
		mario->vy += MARIO_JUMP_SPEED_Y / 2;
	}
}
void CMarioState::OnSit(LPMARIO mario)
{
	if (mario->isOnPlatform && mario->level != MARIO_LEVEL_SMALL)
	{
		mario->state = MARIO_STATE_IDLE;
		mario->isSitting = true;
		mario->vx = 0; 
		mario->vy = 0.0f;

		//float width, height;
		//this->GetBoundingBox(mario, width, height);
		//mario->y += MARIO_SIT_HEIGHT_ADJUST;
	}
}
void CMarioState::OnReleaseSit(LPMARIO mario)
{
	if (mario->isSitting)
	{
		mario->isSitting = false;
		mario->state = MARIO_STATE_IDLE;
		mario->y -= MARIO_SIT_HEIGHT_ADJUST;
	}
}
void CMarioState::OnIdle(LPMARIO mario)
{
	mario->ax = 0.0f;
	mario->vx = 0.0f;
}
void CMarioState::OnDie(LPMARIO mario)
{
	mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
	mario->vx = 0;
	mario->ax = 0;
}

void CMarioState::HandleStateChange(LPMARIO mario, int state)
{
	if (mario->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
	case MARIO_STATE_RUNNING_LEFT:
		this->OnRun(mario, state == MARIO_STATE_RUNNING_LEFT);
		return;
	case MARIO_STATE_WALKING_RIGHT:
	case MARIO_STATE_WALKING_LEFT:
		this->OnWalk(mario, state == MARIO_STATE_WALKING_LEFT);
		return;
	case MARIO_STATE_JUMP:
		this->OnJump(mario);
		return;
	case MARIO_STATE_RELEASE_JUMP:
		this->OnReleaseJump(mario);
		return;
	case MARIO_STATE_SIT:
		this->OnSit(mario);
		return;
	case MARIO_STATE_SIT_RELEASE:
		this->OnReleaseSit(mario);
		return;

	case MARIO_STATE_IDLE:
		this->OnIdle(mario);
		return;
	case MARIO_STATE_DIE:
		this->OnDie(mario);
		return;
	}
}
