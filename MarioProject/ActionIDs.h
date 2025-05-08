#pragma once

// Action
constexpr int MOVE_LEFT = 10;
constexpr int MOVE_RIGHT = 20;

// State Middle
constexpr int JUMP_WALK = 250;
constexpr int JUMP_RUN = 500;

// State
constexpr int STATE_IDLE = 1000;
constexpr int STATE_WALKING = 2000;
constexpr int STATE_RUNNING = 3000;
constexpr int STATE_JUMP = 4000;
constexpr int STATE_SIT = 5000;
constexpr int STATE_BRACE = 6000;
constexpr int STATE_ATTACK = 7000;