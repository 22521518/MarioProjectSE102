#pragma once

constexpr float MARIO_WALKING_SPEED			= 0.1f;	//speed when mario is walking
constexpr float MARIO_RUNNING_SPEED			= 0.2f;	//speed when mario is running
constexpr float MARIO_ACCEL_WALK_X			= 0.0005f; //acceleration when mario is walking
constexpr float MARIO_ACCEL_RUN_X			= 0.0007f; //acceleration when mario is running
constexpr float MARIO_JUMP_SPEED_Y			= 0.5f;	//speed when mario is jumping
constexpr float MARIO_GRAVITY				= 0.001f;	//gravity when mario is falling
constexpr float MARIO_JUMP_RUN_SPEED_Y		= 0.6f;	//speed when mario is running and jump
constexpr float MARIO_JUMP_DEFLECT_SPEED	= 0.4f;	//speed when mario jump on top of an enemy
constexpr float MARIO_UNTOUCHABLE_TIME		= 1000;	//ms
constexpr float MARIO_FLAPPING_TIME			= 300;	//ms
constexpr float MARIO_MIN_VY				= MARIO_JUMP_RUN_SPEED_Y / 10;
constexpr float MARIO_KICK_TIME				= 500;
