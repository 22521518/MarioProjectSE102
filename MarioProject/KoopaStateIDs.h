#pragma once
#pragma region KOOPA_BBOX
constexpr float KOOPA_BBOX_WIDTH = 16;
constexpr float KOOPA_BBOX_HEIGHT = 26;

constexpr float SHELL_BBOX_WIDTH = 20;
constexpr float SHELL_BBOX_HEIGHT = 15;
#pragma endregion

#pragma region KOOPA_STATE
constexpr int KOOPA_STATE_WALKING = 0;
constexpr int KOOPA_STATE_SHELL_IDLE = 200;
constexpr int KOOPA_STATE_SHELL_IDLE_OUT_TIME = 210;
constexpr int KOOPA_STATE_SHELL_IDLE_OUT_TIME_HOLD = 211;
constexpr int KOOPA_STATE_SHELL_MOVE = 300;
constexpr int KOOPA_STATE_DIE = 666;
constexpr int KOOPA_STATE_PARATROOPA = 2000;
#pragma endregion

#pragma region GREEN_KOOPA_STATE
constexpr int GREEN_KOOPA_STATE_PARATROOPA_JUMP = 3000;
constexpr int GREEN_KOOPA_STATE_PARATROOPA_WALK = 3001;
#pragma endregion

