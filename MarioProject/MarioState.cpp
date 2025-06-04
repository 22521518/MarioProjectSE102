#include "MarioState.h"
#include "Mario.h"

void CMarioState::OnRun(bool isLeft)
{
	if (mario->isSitting) return;
	DirectionXAxisType dir = isLeft ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	int normX = static_cast<int>(dir);
	
	if (dir != mario->nx) {
		mario->nx = dir;
		mario->maxVx = normX * MARIO_WALKING_SPEED;
	}
	else if ((mario->running_start != 0 && GetTickCount64() - mario->running_start >= MARIO_TIME_POWER_P))	
	{
		mario->maxVx = MARIO_SPRINTNIG_SPEED * normX;
		if (mario->power_p_start == 0 || (GetTickCount64() - mario->power_p_start > MARIO_DURATION_POWER_P + MARIO_COOLDOWN_POWER_P)) 
		{
			mario->power_p_start = GetTickCount64();
		}
	}
	else {
		mario->maxVx = normX * MARIO_RUNNING_SPEED;
	}
	mario->ax = normX * MARIO_ACCEL_RUN_X;
}

void CMarioState::OnWalk(bool isLeft)
{
	if (mario->isSitting) return;
	mario->nx = isLeft ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	int normX = static_cast<int>(mario->nx);
	mario->maxVx = normX * MARIO_WALKING_SPEED;
	mario->ax = normX * MARIO_ACCEL_WALK_X;
}
void CMarioState::OnJump()
{
	if (mario->isSitting) return;
	if (mario->isOnPlatform)
	{
		float deflect = abs(mario->vx) == MARIO_RUNNING_SPEED ?
			-MARIO_JUMP_RUN_SPEED_Y : -MARIO_JUMP_SPEED_Y;
		mario->vy += deflect;
	}
}
void CMarioState::OnReleaseJump()
{
	if (mario->vy < 0)
	{
		mario->vy += MARIO_JUMP_SPEED_Y / 2;
	}
}
void CMarioState::OnSit()
{
	if (mario->isOnPlatform && mario->level != MARIO_LEVEL_SMALL)
	{
		float marioLeft = 0, marioTop = 0, marioRight = 0, marioBottom = 0;
		mario->GetBoundingBox(marioLeft, marioTop, marioRight, marioBottom);

		mario->state = MARIO_STATE_IDLE;
		mario->isSitting = true;
		mario->vx = 0;
		mario->vy = 0.0f;

		float bbWidth, bbHeight;
		this->GetBoundingBox(bbWidth, bbHeight);
		mario->y = marioBottom - bbHeight;

		/*float width, height;
		this->GetBoundingBox(width, height);
		mario->y += MARIO_SIT_HEIGHT_ADJUST;*/
	}
}
void CMarioState::OnReleaseSit()
{
	if (mario->isSitting)
	{
		float marioLeft = 0, marioTop = 0, marioRight = 0, marioBottom = 0;
		mario->GetBoundingBox(marioLeft, marioTop, marioRight, marioBottom);

		mario->isSitting = false;
		mario->state = MARIO_STATE_IDLE;

		float bbWidth, bbHeight;
		this->GetBoundingBox(bbWidth, bbHeight);
		mario->y = marioBottom - bbHeight;
	}
}
void CMarioState::OnIdle()
{
	mario->ax = 0.0f;
	mario->vx = 0.0f;
}
void CMarioState::OnDie()
{
	mario->vy = -MARIO_JUMP_DEFLECT_SPEED;
	mario->vx = 0;
	mario->ax = 0;
}

void CMarioState::HandleStateChange(int state)
{
	// DIE is the end state, cannot be changed! 
	if (mario->state == MARIO_STATE_DIE) return;
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
	case MARIO_STATE_RUNNING_LEFT:
	{
		this->OnRun(state == MARIO_STATE_RUNNING_LEFT);
		break;
	}
	case MARIO_STATE_WALKING_RIGHT:
	case MARIO_STATE_WALKING_LEFT:
	{
		this->OnWalk(state == MARIO_STATE_WALKING_LEFT);
		break;
	}
	case MARIO_STATE_JUMP:
	{
		this->OnJump();
		break;
	}
	case MARIO_STATE_RELEASE_JUMP:
	{
		this->OnReleaseJump();
		break;
	}
	case MARIO_STATE_SIT:
	{
		this->OnSit();
		break;
	}
	case MARIO_STATE_SIT_RELEASE:
	{
		this->OnReleaseSit();
		break;
	}
	case MARIO_STATE_IDLE:
	{
		this->OnIdle();
		break;
	}
	case MARIO_STATE_DIE:
	{
		return;
		DebugOut(L">>> Mario DIE >>> \n");
		this->OnDie();
		break;
	}
	default: return;
	}
	mario->state = state;
}
