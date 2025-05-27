#pragma once

constexpr float MARIO_WALKING_SPEED			= 1.5f * 0.0625f; //0.0625f;	
constexpr float MARIO_ACCEL_WALK_X			= 0.000546875f * 0.9f * 0.75f; // 3.75e-3f; // 0.0005f
constexpr float MARIO_BRAKE_WALK_ACCEL_X	= 0.00055f;
constexpr float MARIO_JUMP_SPEED_Y			= 3.5f * 0.0625f; //240e-3f; //0.5f	

constexpr float MARIO_RUNNING_SPEED			= 2.5f * 0.0625f;	//0.2f
constexpr float MARIO_ACCEL_RUN_X			= 0.000546875f * 0.75f;// 7.5e-3f; //0.0007
constexpr float MARIO_BRAKE_RUN_ACCEL_X		= 0.0007f;
constexpr float MARIO_JUMP_RUN_SPEED_Y		= 4.5f * 0.0625f; // 300e-3f;	//0.6f;

constexpr float MARIO_TIME_POWER_P			= 2000.f;
constexpr float MARIO_COOLDOWN_POWER_P		= 1000.f;
constexpr float MARIO_DURATION_POWER_P		= 5000.f;
constexpr float MARIO_SPRINTNIG_SPEED		= 3.5f * 0.0625f; //210e-3f; // using power meter
constexpr float MARIO_FLAP_BOOST			= 0.25f * 0.0625f; //240e-3f; //0.5f		
constexpr float MARIO_FLOAT_GRAVITY			= 0.15f * 0.0625f;  //240e-3f; //0.5f		

constexpr float MARIO_GRAVITY				= 0.21875f * 0.0625f * 0.0625f * 0.5f; //0.001f; for vy < 0
constexpr float MARIO_FALL_GRAVITY			= 0.5625f * 0.0625f * 0.0625f * 0.5f; //0.001f; for vy > 0
constexpr float MARIO_JUMP_DEFLECT_SPEED	= 3.0f * 0.0625f;

constexpr float MARIO_UNTOUCHABLE_TIME		= 1000.0f;
constexpr float MARIO_FLAPPING_TIME			= 500.0f;
constexpr float MARIO_MIN_VY				= MARIO_JUMP_RUN_SPEED_Y / 10.0f;
constexpr float MARIO_KICK_TIME				= 500.0f;