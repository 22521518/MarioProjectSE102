#pragma once

#include "AnimationIDs.h"
#include "MarioStateIDs.h"

#pragma region FLY_MARIO_ANIMATION
constexpr int ID_ANI_MARIO_FLY							= static_cast<int>(1e7);
constexpr int ID_ANI_MARIO_FLY_KICK_RIGHT				= static_cast<int>(1e7 + 20);
constexpr int ID_ANI_MARIO_FLY_KICK_LEFT				= static_cast<int>(1e7 + 21);
constexpr int ID_ANI_MARIO_FLY_IDLE_RIGHT				= static_cast<int>(1e7 + 0);
constexpr int ID_ANI_MARIO_FLY_IDLE_LEFT				= static_cast<int>(1e7 + 1);
constexpr int ID_ANI_MARIO_FLY_IDLE_HOLD_RIGHT			= static_cast<int>(1e7 + 0 + 10);
constexpr int ID_ANI_MARIO_FLY_IDLE_HOLD_LEFT			= static_cast<int>(1e7 + 1 + 10);
constexpr int ID_ANI_MARIO_FLY_WALKING_RIGHT			= static_cast<int>(1e7 + MARIO_STATE_WALKING_RIGHT);
constexpr int ID_ANI_MARIO_FLY_WALKING_LEFT				= static_cast<int>(1e7 + MARIO_STATE_WALKING_LEFT);
constexpr int ID_ANI_MARIO_FLY_RUNNING_RIGHT			= static_cast<int>(1e7 + MARIO_STATE_RUNNING_RIGHT);
constexpr int ID_ANI_MARIO_FLY_RUNNING_LEFT				= static_cast<int>(1e7 + MARIO_STATE_RUNNING_LEFT);
constexpr int ID_ANI_MARIO_FLY_RUNNING_HOLD_RIGHT		= static_cast<int>(1e7 + MARIO_STATE_RUNNING_RIGHT + 10);
constexpr int ID_ANI_MARIO_FLY_RUNNING_HOLD_LEFT		= static_cast<int>(1e7 + MARIO_STATE_RUNNING_LEFT + 10);
constexpr int ID_ANI_MARIO_FLY_BRACE_RIGHT				= static_cast<int>(1e7 + 1000);
constexpr int ID_ANI_MARIO_FLY_BRACE_LEFT				= static_cast<int>(1e7 + 1001);
constexpr int ID_ANI_MARIO_FLY_JUMP_WALK_RIGHT			= static_cast<int>(1e7 + MARIO_STATE_JUMP * 100 + MARIO_STATE_WALKING_RIGHT);
constexpr int ID_ANI_MARIO_FLY_JUMP_WALK_LEFT			= static_cast<int>(1e7 + MARIO_STATE_JUMP * 100 + MARIO_STATE_WALKING_LEFT);
constexpr int ID_ANI_MARIO_FLY_JUMP_RUN_LEFT			= static_cast<int>(1e7 + MARIO_STATE_JUMP * 100 + MARIO_STATE_RUNNING_LEFT);
constexpr int ID_ANI_MARIO_FLY_JUMP_RUN_FLAPPING_LEFT	= ID_ANI_MARIO_FLY_JUMP_RUN_LEFT + 1;
constexpr int ID_ANI_MARIO_FLY_JUMP_RUN_RIGHT			= static_cast<int>(1e7 + MARIO_STATE_JUMP * 100 + MARIO_STATE_RUNNING_RIGHT);
constexpr int ID_ANI_MARIO_FLY_JUMP_RUN_FLAPPING_RIGHT	= ID_ANI_MARIO_FLY_JUMP_RUN_RIGHT + 1;
constexpr int ID_ANI_MARIO_FLY_JUMP_RELEASE_LEFT		= static_cast<int>(1e7 + MARIO_FLY_RELEASE + MARIO_STATE_WALKING_LEFT);
constexpr int ID_ANI_MARIO_FLY_JUMP_RELEASE_FLAPPING_LEFT = ID_ANI_MARIO_FLY_JUMP_RELEASE_LEFT + 1;
constexpr int ID_ANI_MARIO_FLY_JUMP_RELEASE_RIGHT		= static_cast<int>(1e7 + MARIO_FLY_RELEASE + MARIO_STATE_WALKING_RIGHT);
constexpr int ID_ANI_MARIO_FLY_JUMP_RELEASE_FLAPPING_RIGHT = ID_ANI_MARIO_FLY_JUMP_RELEASE_RIGHT + 1;
constexpr int ID_ANI_MARIO_FLY_SIT_RIGHT				= static_cast<int>(1e7 + MARIO_STATE_SIT);
constexpr int ID_ANI_MARIO_FLY_SIT_LEFT					= static_cast<int>(1e7 + MARIO_STATE_SIT + 10);
constexpr int ID_ANI_MARIO_FLY_ATTACK					= static_cast<int>(1e7 + MARIO_FLY_STATE_ATTACK);

//AFTER FLAP ON AIR LEFT(500) & RIGHT(400)
constexpr int ID_ANI_MARIO_FLY_JUMP_RUN_OPENARM_LEFT	= 10030503;
constexpr int ID_ANI_MARIO_FLY_JUMP_RUN_OPENARM_RIGHT	= 10030403;
#pragma endregion

// constexpr int ID_ANI_MARIO 0;
#pragma region BIG_MARIO_ANIMATION
constexpr int ID_ANI_MARIO = 0;
constexpr int ID_ANI_MARIO_KICK_RIGHT = 0 + 420;
constexpr int ID_ANI_MARIO_KICK_LEFT = 0 + 421;
constexpr int ID_ANI_MARIO_IDLE_RIGHT = 0 + 400;
constexpr int ID_ANI_MARIO_IDLE_LEFT = 0 + 401;
constexpr int ID_ANI_MARIO_IDLE_HOLD_RIGHT = 0 + 400 + 10;
constexpr int ID_ANI_MARIO_IDLE_HOLD_LEFT = 0 + 401 + 10;
constexpr int ID_ANI_MARIO_WALKING_RIGHT = 0 + 500;
constexpr int ID_ANI_MARIO_WALKING_LEFT = 0 + 501;
constexpr int ID_ANI_MARIO_RUNNING_RIGHT = 0 + 600;
constexpr int ID_ANI_MARIO_RUNNING_LEFT = 0 + 601;
constexpr int ID_ANI_MARIO_RUNNING_HOLD_RIGHT = 0 + 600 + 10;
constexpr int ID_ANI_MARIO_RUNNING_HOLD_LEFT = 0 + 601 + 10;
constexpr int ID_ANI_MARIO_JUMP_WALK_RIGHT = 0 + 700;
constexpr int ID_ANI_MARIO_JUMP_WALK_LEFT = 0 + 701;
constexpr int ID_ANI_MARIO_JUMP_RUN_RIGHT = 0 + 800;
constexpr int ID_ANI_MARIO_JUMP_RUN_LEFT = 0 + 801;
constexpr int ID_ANI_MARIO_SIT_RIGHT = 0 + 900;
constexpr int ID_ANI_MARIO_SIT_LEFT = 0 + 901;
constexpr int ID_ANI_MARIO_BRACE_RIGHT = 0 + 1000;
constexpr int ID_ANI_MARIO_BRACE_LEFT = 0 + 1001;
#pragma endregion	

constexpr int ID_ANI_MARIO_DIE = 999;

#pragma region SMALL_MARIO_ANIMATION
constexpr int ID_ANI_MARIO_SMALL				= static_cast<int>(1e4);
constexpr int ID_ANI_MARIO_SMALL_KICK_RIGHT		= static_cast<int>(1e4 + 1120);
constexpr int ID_ANI_MARIO_SMALL_KICK_LEFT		= static_cast<int>(1e4 + 1121);
constexpr int ID_ANI_MARIO_SMALL_IDLE_RIGHT		= static_cast<int>(1e4 + 1100);
constexpr int ID_ANI_MARIO_SMALL_IDLE_LEFT		= static_cast<int>(1e4 + 1102);
constexpr int ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT		= static_cast<int>(1e4 + 1100 + 10);
constexpr int ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT		= static_cast<int>(1e4 + 1102 + 10);
constexpr int ID_ANI_MARIO_SMALL_WALKING_RIGHT	= static_cast<int>(1e4 + 1200);
constexpr int ID_ANI_MARIO_SMALL_WALKING_LEFT	= static_cast<int>(1e4 + 1201);
constexpr int ID_ANI_MARIO_SMALL_RUNNING_RIGHT	= static_cast<int>(1e4 + 1300);
constexpr int ID_ANI_MARIO_SMALL_RUNNING_LEFT	= static_cast<int>(1e4 + 1301);
constexpr int ID_ANI_MARIO_SMALL_RUNNING_HOLD_RIGHT	= static_cast<int>(1e4 + 1300 + 10);
constexpr int ID_ANI_MARIO_SMALL_RUNNING_HOLD_LEFT	= static_cast<int>(1e4 + 1301 + 10);
constexpr int ID_ANI_MARIO_SMALL_BRACE_RIGHT	= static_cast<int>(1e4 + 1400);
constexpr int ID_ANI_MARIO_SMALL_BRACE_LEFT		= static_cast<int>(1e4 + 1401);
constexpr int ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT= static_cast<int>(1e4 + 1500);
constexpr int ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT	= static_cast<int>(1e4 + 1501);
constexpr int ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT	= static_cast<int>(1e4 + 1600);
constexpr int ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT	= static_cast<int>(1e4 + 1601);
#pragma endregion 