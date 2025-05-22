#pragma once

constexpr float MARIO_WALKING_SPEED			= 90e-3f; //0.0625f;	
constexpr float MARIO_WALKING_SPEED_MAX		= 90e-3f;
constexpr float MARIO_ACCEL_WALK_X			= 3.75e-3f; // 0.0005f
constexpr float MARIO_JUMP_SPEED_Y			= 240e-3f; //0.5f	

constexpr float MARIO_RUNNING_SPEED			= 150e-3f;	//0.2f
constexpr float MARIO_RUNNING_SPEED_MAX		= 150e-3f;	
constexpr float MARIO_ACCEL_RUN_X			= 7.5e-3f; //0.0007
constexpr float MARIO_JUMP_RUN_SPEED_Y		= 300e-3f;	//0.6f;

constexpr float MARIO_SPRINTNIG_SPEED		= 210e-3f; // using power meter	

constexpr float MARIO_GRAVITY				= 13.125e-6f; //0.001f; for vy < 0
constexpr float MARIO_FALL_GRAVITY			= 33.75e-6f; //0.001f; for vy > 0
constexpr float MARIO_JUMP_DEFLECT_SPEED	= 0.12f;	

constexpr float MARIO_UNTOUCHABLE_TIME		= 1000.0f;
constexpr float MARIO_FLAPPING_TIME			= 300.0f;
constexpr float MARIO_MIN_VY				= MARIO_JUMP_RUN_SPEED_Y / 10.0f;
constexpr float MARIO_KICK_TIME				= 500.0f;
