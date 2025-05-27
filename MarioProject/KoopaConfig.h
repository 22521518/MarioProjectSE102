#pragma once

constexpr float KOOPA_GRAVITY = 1.25f * 0.0625f * 0.0625f * 0.0625f; // 3.f * 0.0625f * 0.0625f;// 0.0005f;
constexpr float SHELL_GRAVITY = 0.125 * 0.0625f;// 0.01f;
constexpr float KOOPA_WALKING_SPEED = 0.5f * 0.0625f; // 0.05f;
constexpr float KOOPA_SHELL_SPEED = 2.5f * 0.0625f;
constexpr float KOOPA_PARATROOPA_ACCELERATION_Y = 0.000075f;

constexpr float KOOPA_MAX_VY = (KOOPA_PARATROOPA_ACCELERATION_Y * 1000.0f); // fly range;
constexpr float KOOPA_JUMP_VY = 2.0f * 0.0625f; // 0.42f; // fly range;

constexpr float KOOPA_SHELL_TIMEOUT = 3500;
constexpr float KOOPA_DIE_TIMEOUT = 5500;