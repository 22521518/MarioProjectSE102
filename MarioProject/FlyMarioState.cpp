#include "FlyMarioState.h"
#include "Mario.h"
#include "MarioAniIDs.h"
#include "MarioConfig.h"

void CFlyMarioState::OnRun(bool isLeft)
{
	CMarioState::OnRun(isLeft);

	DirectionXAxisType dir = isLeft ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	int normX = static_cast<int>(dir);

	if (mario->IsFlapping() && mario->CanFly())
	{
		mario->maxVx = MARIO_WALKING_SPEED * 1.05f * normX;
		mario->nx = dir;
	}
}

void CFlyMarioState::OnWalk(bool isLeft)
{
	CMarioState::OnWalk(isLeft);
}

void CFlyMarioState::OnJump()
{
	CMarioState::OnJump();
	mario->StartFlap();
}

void CFlyMarioState::OnReleaseJump()
{
	mario->ay = MARIO_GRAVITY;
	if (mario->IsFlapping())
	{
		mario->vy = -MARIO_FLAP_BOOST;
		mario->ay = MARIO_GRAVITY * 0.5f;
	}
	else {
		CMarioState::OnReleaseJump();
	}
}

int CFlyMarioState::GetAniId()
{
	int aniId = -1;
	bool isRight = mario->nx == DirectionXAxisType::Right;

	if (!mario->isOnPlatform)
	{
		if (mario->IsFlapping() && (mario->CanFly() || mario->power_p_start != 0)) // Power P mode
		{
			aniId = isRight ?
				ID_ANI_MARIO_FLY_JUMP_RUN_FLAPPING_RIGHT :
				ID_ANI_MARIO_FLY_JUMP_RUN_FLAPPING_LEFT;
			
		}
		else if (!mario->CanFly() && mario->power_p_start == 0) {
			if (mario->IsFlapping())
			{
				aniId = isRight ?
					ID_ANI_MARIO_FLY_JUMP_RELEASE_FLAPPING_RIGHT :
					ID_ANI_MARIO_FLY_JUMP_RELEASE_FLAPPING_LEFT;
			}
			else
			{
				aniId = isRight ?
					ID_ANI_MARIO_FLY_JUMP_RELEASE_RIGHT :
					ID_ANI_MARIO_FLY_JUMP_RELEASE_LEFT;
			}
		}
		else if (mario->flap_start >= 2)
		{
			aniId = isRight ?
				ID_ANI_MARIO_FLY_JUMP_RUN_OPENARM_RIGHT :
				ID_ANI_MARIO_FLY_JUMP_RUN_OPENARM_LEFT;
		} else if (abs(mario->ax) == MARIO_ACCEL_RUN_X && mario->vy < 0)
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_FLY_JUMP_RUN_RIGHT : ID_ANI_MARIO_FLY_JUMP_RUN_LEFT;
		}
		else
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_FLY_JUMP_RELEASE_RIGHT : ID_ANI_MARIO_FLY_JUMP_RELEASE_LEFT;
		}
	}
	else if (mario->state == MARIO_FLY_STATE_ATTACK) 
	{

	}
	else if (mario->isSitting)
	{
		aniId = isRight ?
			ID_ANI_MARIO_FLY_SIT_RIGHT : ID_ANI_MARIO_FLY_SIT_LEFT;
	}
	else if (mario->kick_start > 0 && GetTickCount64() - mario->kick_start < MARIO_KICK_TIME)
	{
		aniId = isRight ?
			ID_ANI_MARIO_FLY_KICK_RIGHT : ID_ANI_MARIO_FLY_KICK_LEFT;
	}
	else if (mario->vx == 0)
	{

		if (mario->holdingItem)
		{
			aniId = isRight ?
				ID_ANI_MARIO_FLY_IDLE_HOLD_RIGHT : ID_ANI_MARIO_FLY_IDLE_HOLD_LEFT;
		}
		else if (mario->IsAttacking())
		{
			aniId = ID_ANI_MARIO_FLY_ATTACK;
		}
		else
		{
			aniId = isRight ?
				ID_ANI_MARIO_FLY_IDLE_RIGHT : ID_ANI_MARIO_FLY_IDLE_LEFT;
		}
	}
	else if (mario->IsAttacking())
	{
		aniId = ID_ANI_MARIO_FLY_ATTACK;
	}
	else if (mario->vx > 0) // right
	{
		
		if (mario->ax < 0)
		{
			aniId = ID_ANI_MARIO_FLY_BRACE_RIGHT;
		}
		else if (mario->ax >= MARIO_ACCEL_RUN_X)
		{
			aniId = mario->holdingItem ?
				ID_ANI_MARIO_FLY_RUNNING_HOLD_RIGHT : ID_ANI_MARIO_FLY_RUNNING_RIGHT;
		}
		else if (mario->ax >= MARIO_ACCEL_WALK_X)
		{
			aniId = ID_ANI_MARIO_FLY_WALKING_RIGHT;
		}
	}
	else //left
	{
		if (mario->ax > 0)
		{
			aniId = ID_ANI_MARIO_FLY_BRACE_LEFT;
		}
		else if (mario->ax <= -MARIO_ACCEL_RUN_X)
		{
			aniId = mario->holdingItem ?
				ID_ANI_MARIO_FLY_RUNNING_HOLD_LEFT : ID_ANI_MARIO_FLY_RUNNING_LEFT;
		}
		else if (mario->ax <= -MARIO_ACCEL_WALK_X)
		{
			aniId = ID_ANI_MARIO_FLY_WALKING_LEFT;
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_FLY_IDLE_RIGHT;

	return aniId;
}

void CFlyMarioState::GetBoundingBox(float& width, float& height)
{
	if (mario->IsAttacking()) 
	{
		height = MARIO_FLY_BBOX_HEIGHT;
		width = MARIO_FLY_BBOX_WIDTH + 10;
	}
	if (mario->isSitting)
	{
		height = MARIO_FLY_SITTING_BBOX_HEIGHT;
		width = MARIO_FLY_SITTING_BBOX_WIDTH;
	}
	else
	{
		height = MARIO_FLY_BBOX_HEIGHT;
		width = MARIO_FLY_BBOX_WIDTH;
	}
}
