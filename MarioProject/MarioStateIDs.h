#pragma once

#pragma region MARIO_STATE
constexpr int MARIO_STATE_DIE			= -666;
constexpr int MARIO_STATE_IDLE			= 0;
constexpr int MARIO_STATE_WALKING_RIGHT = 100;
constexpr int MARIO_STATE_WALKING_LEFT	= 200;
constexpr int MARIO_STATE_JUMP			= 300;
constexpr int MARIO_STATE_RELEASE_JUMP	= 301;
constexpr int MARIO_STATE_RUNNING_RIGHT = 400;
constexpr int MARIO_STATE_RUNNING_LEFT	= 500;
constexpr int MARIO_STATE_SIT			= 600;
constexpr int MARIO_STATE_SIT_RELEASE	= 601;

constexpr int MARIO_FLY_STATE_ATTACK	= 7e3;
constexpr int MARIO_FLY_RELEASE			= 31e3;
constexpr int MARIO_FLY_FLAPPING		= 1e7 + 1;
#pragma endregion

#pragma region MARIO_LEVEL
constexpr int MARIO_LEVEL_SMALL			= 1;
constexpr int MARIO_LEVEL_BIG			= 2;
constexpr int MARIO_LEVEL_FLY			= 3;
#pragma endregion

#pragma region MARIO_BBOX
constexpr float MARIO_FLY_BBOX_WIDTH			= 22;
constexpr float MARIO_FLY_BBOX_HEIGHT			= 28;
constexpr float MARIO_FLY_SITTING_BBOX_WIDTH	= 14;
constexpr float MARIO_FLY_SITTING_BBOX_HEIGHT	= 18;

constexpr float MARIO_BIG_BBOX_WIDTH			= 14;
constexpr float MARIO_BIG_BBOX_HEIGHT			= 24;
constexpr float MARIO_BIG_SITTING_BBOX_WIDTH	= 14;
constexpr float MARIO_BIG_SITTING_BBOX_HEIGHT	= 16;

constexpr float MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2);
constexpr float MARIO_SMALL_BBOX_WIDTH			= 13;
constexpr float MARIO_SMALL_BBOX_HEIGHT			= 12;
#pragma endregion
