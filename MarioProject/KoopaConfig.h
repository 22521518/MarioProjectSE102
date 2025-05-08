#pragma once

constexpr float KOOPA_GRAVITY = 0.0005f;
constexpr float SHELL_GRAVITY = 0.01f;
constexpr float KOOPA_WALKING_SPEED = 0.05f;
constexpr float KOOPA_SHELL_SPEED = 0.2f;
constexpr float KOOPA_PARATROOPA_ACCELERATION_Y = 0.000075f;

constexpr float KOOPA_MAX_VY = (KOOPA_PARATROOPA_ACCELERATION_Y * 1000.0f); // fly range;
constexpr float KOOPA_JUMP_VY = 0.2f; // fly range;

constexpr float KOOPA_SHELL_TIMEOUT = 3500;
constexpr float KOOPA_DIE_TIMEOUT = 5500;