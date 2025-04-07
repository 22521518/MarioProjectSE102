#include "SmallMarioState.h"
#include "Mario.h"
#include "MarioAniIDs.h"
#include "MarioConfig.h"

int CSmallMarioState::GetAniId(LPMARIO mario)
{
	int aniId = -1;
	if (!mario->isOnPlatform)
	{
		if (abs(mario->ax) == MARIO_ACCEL_RUN_X)
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT : ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT : ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (mario->isSitting)
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_SIT_RIGHT : ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (mario->vx == 0)
			{
				aniId = mario->nx == DirectionXAxisType::Right ?
					ID_ANI_MARIO_SMALL_IDLE_RIGHT : ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (mario->vx > 0)
			{
				if (mario->ax < 0)
				{
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				}
				else if (mario->ax == MARIO_ACCEL_RUN_X)
				{
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				}
				else if (mario->ax == MARIO_ACCEL_WALK_X)
				{
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
			}
			else // mario->vx < 0
			{
				if (mario->ax > 0)
				{
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				}
				else if (mario->ax == -MARIO_ACCEL_RUN_X)
				{
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				}
				else if (mario->ax == -MARIO_ACCEL_WALK_X)
				{
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}
