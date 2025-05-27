#include "FlyMarioState.h"
#include "Mario.h"
#include "MarioAniIDs.h"
#include "MarioConfig.h"

bool CFlyMarioState::CanFly()
{
	return mario->maxVx < MARIO_SPRINTNIG_SPEED || GetTickCount64() - mario->running_start > MARIO_TIME_POWER_P + MARIO_DURATION_POWER_P;
}

void CFlyMarioState::OnJump()
{
	CMarioState::OnJump();
	if (!mario->isOnPlatform)
	{
		mario->StartFlap();
		//DebugOut(L"flap: %d: %d\n", mario->IsFlapping() , mario->flap_start);
		if (mario->IsFlapping() && mario->vy < 0 && CanFly())
		{
			mario->vy = -MARIO_FLAP_BOOST;
			mario->ay = MARIO_GRAVITY * 0.5f;;
		}
		else if (mario->IsFlapping() && mario->vy > 0)
		{
			mario->ay = -MARIO_GRAVITY * 0.5f;
			mario->vy = MARIO_MIN_VY > mario->vy ? MARIO_MIN_VY : mario->vy;
		}
		else {
			mario->ay = MARIO_GRAVITY * 0.2f;
		}
		DebugOut(L"ay: %d, vy: %d\n", mario->ay , mario->vy);
	}
}

void CFlyMarioState::OnReleaseJump()
{
	mario->ay = MARIO_GRAVITY;
	if (mario->vy < 0)
	{
		mario->vy += MARIO_JUMP_SPEED_Y / 2;
	}
}

int CFlyMarioState::GetAniId()
{
	int aniId = -1;
	if (!mario->isOnPlatform)
	{
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
	else if (mario->kick_start > 0 && GetTickCount64() - mario->kick_start < MARIO_KICK_TIME)
	{
		aniId = mario->nx == DirectionXAxisType::Right ?
			ID_ANI_MARIO_FLY_KICK_RIGHT : ID_ANI_MARIO_FLY_KICK_LEFT;
	}
	else if (mario->vx == 0)
	{

		if (mario->holdingItem)
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_FLY_IDLE_HOLD_RIGHT : ID_ANI_MARIO_FLY_IDLE_HOLD_LEFT;
		}
		else
		{
			aniId = mario->nx == DirectionXAxisType::Right ?
				ID_ANI_MARIO_FLY_IDLE_RIGHT : ID_ANI_MARIO_FLY_IDLE_LEFT;
		}
	}
	else if (mario->vx > 0)
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
	else // vx < 0
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

void CFlyMarioState::HandleStateChange(int state)
{
	CMarioState::HandleStateChange(state);
}
