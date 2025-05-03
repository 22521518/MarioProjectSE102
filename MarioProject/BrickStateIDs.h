#pragma once

#pragma region Tri_BRICK_ITEM
#define BRICK_STATE_ACTIVE 1001
#define BRICK_STATE_INACTIVE 1000
#pragma endregion

#pragma region MARIO_BBOX
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#pragma endregion
#pragma region BRICK_STATE
#define BRICK_STATE_COIN 1
#define BRICK_STATE_1UP 2
#define BRICK_STATE_EMPTY 0
#define BRICK_STATE_EMPTYING -1
#pragma endregion
#define BRICK_Q_COIN_SPEED 0.3f
#define BRICK_Q_COIN_GAVITY 0.001f
#define BRICK_Q_SPEED 0.1f
#define BRICK_Q_GAVITY 0.0004f
#define BRICK_Q_1UP_SPEED_X 0.05f //need some check
#define BRICK_Q_1UP_GO_UP 0.01f
#define BRICK_Q_1UP_SPEED_Y 0.05f //need some check
#define BRICK_Q_1UP_GAVITY 0.0004f //need some check