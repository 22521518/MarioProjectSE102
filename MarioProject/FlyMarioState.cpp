#include "FlyMarioState.h"
#include "Mario.h"
#include "MarioAniIDs.h"
#include "MarioConfig.h"

void CFlyMarioState::OnJump(LPMARIO mario)
{
	CMarioState::OnJump(mario);
	if (!mario->isOnPlatform)
	{
		mario->StartFlap();
		//DebugOut(L"flap: %d: %d\n", mario->IsFlapping() , mario->flap_start);
		if (mario->IsFlapping() && mario->vy < 0)
		{
			mario->vy = -MARIO_JUMP_SPEED_Y;
			mario->ay = 0;
		}
		else if (mario->IsFlapping() && mario->vy > 0)
		{
			mario->ay = 0;
		}
		else
		{
			mario->ay = MARIO_GRAVITY;
		}
	}


}

void CFlyMarioState::OnReleaseJump(LPMARIO mario)
{
	mario->ay = MARIO_GRAVITY;
	if (mario->vy < 0)
	{
		mario->vy += MARIO_JUMP_SPEED_Y / 2;
	}
}

int CFlyMarioState::GetAniId(LPMARIO mario)
{
	int aniId = -1;
	if (!mario->isOnPlatform)
	{
		DebugOut(L"flap: %d: %d\n", mario->IsFlapping(), mario->flap_start);
		if (abs(mario->ax) == MARIO_ACCEL_RUN_X && mario->vy < 0)
		{
			if (mario->IsFlapping())
			{
				aniId = mario->nx == DirectionXAxisType::Right ?
					ID_ANI_MARIO_FLY_JUMP_RUN_FLAPPING_RIGHT : ID_ANI_MARIO_FLY_JUMP_RUN_FLAPPING_LEFT;
			}
			else
			{
				aniId = mario->nx == DirectionXAxisType::Right ?
					ID_ANI_MARIO_FLY_JUMP_RUN_RIGHT : ID_ANI_MARIO_FLY_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (mario->IsFlapping())
			{
				aniId = mario->nx == DirectionXAxisType::Right ?
					ID_ANI_MARIO_FLY_JUMP_RELEASE_FLAPPING_RIGHT : ID_ANI_MARIO_FLY_JUMP_RELEASE_FLAPPING_LEFT;
			}
			else
			{
				aniId = mario->nx == DirectionXAxisType::Right ?
					ID_ANI_MARIO_FLY_JUMP_RELEASE_RIGHT : ID_ANI_MARIO_FLY_JUMP_RELEASE_LEFT;
			}
		}
	}
	else if (mario->isSitting)
	{
		aniId = mario->nx == DirectionXAxisType::Right ?
			ID_ANI_MARIO_FLY_SIT_RIGHT : ID_ANI_MARIO_FLY_SIT_LEFT;
	}
	else if (mario->vx == 0)
	{
		aniId = mario->nx == DirectionXAxisType::Right ?
			ID_ANI_MARIO_FLY_IDLE_RIGHT : ID_ANI_MARIO_FLY_IDLE_LEFT;
	}
	else if (mario->vx > 0)
	{
		if (mario->ax < 0)
		{
			aniId = ID_ANI_MARIO_FLY_BRACE_RIGHT;
		}
		else if (mario->ax == MARIO_ACCEL_RUN_X)
		{
			aniId = ID_ANI_MARIO_FLY_RUNNING_RIGHT;
		}
		else if (mario->ax == MARIO_ACCEL_WALK_X)
		{
			aniId = ID_ANI_MARIO_FLY_WALKING_RIGHT;
		}
	}
	else // vx < 0
	{
		if (mario->ax > 0)
		{
			aniId = ID_ANI_MARIO_FLY_BRACE_LEFT;
		}
		else if (mario->ax == -MARIO_ACCEL_RUN_X)
		{
			aniId = ID_ANI_MARIO_FLY_RUNNING_LEFT;
		}
		else if (mario->ax == -MARIO_ACCEL_WALK_X)
		{
			aniId = ID_ANI_MARIO_FLY_WALKING_LEFT;
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_FLY_IDLE_RIGHT;

	return aniId;
}

void CFlyMarioState::GetBoundingBox(LPMARIO mario, float& width, float& height)
{
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

void CFlyMarioState::HandleStateChange(LPMARIO mario, int state)
{
	CMarioState::HandleStateChange(mario, state);
}
