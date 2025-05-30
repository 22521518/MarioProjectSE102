#include "BigMarioState.h"
#include "Mario.h"
#include "MarioAniIDs.h"
#include "MarioConfig.h"

int CBigMarioState::GetAniId()
{
	int aniId = -1;
	if (!mario->isOnPlatform)
	{
		if (abs(mario->ax) == MARIO_ACCEL_RUN_X)
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_JUMP_RUN_RIGHT : ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_JUMP_WALK_RIGHT : ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else if (mario->isSitting)
	{
		aniId = mario->nx == DirectionXAxisType::Right ?
			ID_ANI_MARIO_SIT_RIGHT : ID_ANI_MARIO_SIT_LEFT;
	}

	else if (mario->kick_start > 0 && GetTickCount64() - mario->kick_start < MARIO_KICK_TIME)
	{
		aniId = mario->nx == DirectionXAxisType::Right ?
			ID_ANI_MARIO_KICK_RIGHT : ID_ANI_MARIO_KICK_LEFT;
	}
	else if (mario->vx == 0)
	{

		if (mario->holdingItem)
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_IDLE_HOLD_RIGHT : ID_ANI_MARIO_IDLE_HOLD_LEFT;
		}
		else
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_IDLE_RIGHT : ID_ANI_MARIO_IDLE_LEFT;
		}
	}
	else if (mario->vx > 0)
	{
		if (mario->ax < 0)
		{
			aniId = ID_ANI_MARIO_BRACE_RIGHT;
		}
		else if (mario->ax >= MARIO_ACCEL_RUN_X)
		{
			aniId = mario->holdingItem ?
				ID_ANI_MARIO_RUNNING_HOLD_RIGHT : ID_ANI_MARIO_RUNNING_RIGHT;
		}
		else if (mario->ax >= MARIO_ACCEL_WALK_X)
		{
			aniId = ID_ANI_MARIO_WALKING_RIGHT;
		}
	}
	else // vx < 0
	{
		if (mario->ax > 0)
		{
			aniId = ID_ANI_MARIO_BRACE_LEFT;
		}
		else if (mario->ax <= -MARIO_ACCEL_RUN_X)
		{
			aniId = mario->holdingItem ?
				ID_ANI_MARIO_RUNNING_HOLD_LEFT : ID_ANI_MARIO_RUNNING_LEFT;
		}
		else if (mario->ax <= -MARIO_ACCEL_WALK_X)
		{
			aniId = ID_ANI_MARIO_WALKING_LEFT;
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CBigMarioState::GetBoundingBox(float& width, float& height)
{
	if (mario->isSitting)
	{
		height = MARIO_BIG_SITTING_BBOX_HEIGHT;
		width = MARIO_BIG_SITTING_BBOX_WIDTH;
	}
	else
	{
		height = MARIO_BIG_BBOX_HEIGHT;
		width = MARIO_BIG_BBOX_WIDTH;
	}
}
