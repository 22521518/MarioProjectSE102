#pragma once
#include "KoopaStateIDs.h"

#pragma region RED_KOOPA
// constexpr int ID_ANI_RED_KOOPA 1000000
constexpr int ID_ANI_RED_KOOPA							= static_cast<int>(1e6);
constexpr int ID_ANI_RED_KOOPA_WALKING_LEFT				= static_cast<int>(1e6 + 0);
constexpr int ID_ANI_RED_KOOPA_WALKING_RIGHT			= static_cast<int>(1e6 + 100);

constexpr int ID_ANI_RED_KOOPA_SHELL_IDLE				= static_cast<int>(1e6 + KOOPA_STATE_SHELL_IDLE);
constexpr int ID_ANI_RED_KOOPA_SHELL_IDLE_OUT_TIME		= static_cast<int>(1e6 + KOOPA_STATE_SHELL_IDLE_OUT_TIME);
constexpr int ID_ANI_RED_KOOPA_SHELL_IDLE_OUT_TIME_HOLD = static_cast<int>(1e6 + KOOPA_STATE_SHELL_IDLE_OUT_TIME_HOLD);
constexpr int ID_ANI_RED_KOOPA_SHELL_MOVE				= static_cast<int>(1e6 + KOOPA_STATE_SHELL_MOVE);

constexpr int ID_ANI_RED_KOOPA_TROOPA					= static_cast<int>(1e6 + KOOPA_STATE_PARATROOPA);
constexpr int ID_ANI_RED_KOOPA_PARATROOPA_LEFT			= static_cast<int>(1e6 + 0 + KOOPA_STATE_PARATROOPA);
constexpr int ID_ANI_RED_KOOPA_PARATROOPA_RIGHT			= static_cast<int>(1e6 + 100 + KOOPA_STATE_PARATROOPA);
#pragma endregion

#pragma region GREEN_KOOPA
// constexpr int ID_ANI_GREEN_KOOPA 1001000
constexpr int ID_ANI_GREEN_KOOPA							= static_cast<int>(1e6 + 1e3);
constexpr int ID_ANI_GREEN_KOOPA_WALKING_LEFT				= static_cast<int>(1e6 + 1e3 + 0);
constexpr int ID_ANI_GREEN_KOOPA_WALKING_RIGHT				= static_cast<int>(1e6 + 1e3 + 100);
constexpr int ID_ANI_GREEN_KOOPA_SHELL_IDLE					= static_cast<int>(1e6 + 1e3 + KOOPA_STATE_SHELL_IDLE);
constexpr int ID_ANI_GREEN_KOOPA_SHELL_IDLE_OUT_TIME		= static_cast<int>(1e6 + 1e3 + KOOPA_STATE_SHELL_IDLE_OUT_TIME);
constexpr int ID_ANI_GREEN_KOOPA_SHELL_IDLE_OUT_TIME_HOLD	= static_cast<int>(1e6 + 1e3 + KOOPA_STATE_SHELL_IDLE_OUT_TIME_HOLD);
constexpr int ID_ANI_GREEN_KOOPA_SHELL_MOVE					= static_cast<int>(1e6 + 1e3 + KOOPA_STATE_SHELL_MOVE);

constexpr int ID_ANI_GREEN_KOOPA_TROOPA						= static_cast<int>(1e6 + 1e3 + KOOPA_STATE_PARATROOPA);
constexpr int ID_ANI_GREEN_KOOPA_PARATROOPA_LEFT			= static_cast<int>(1e6 + 1e3 + 0 + KOOPA_STATE_PARATROOPA);
constexpr int ID_ANI_GREEN_KOOPA_PARATROOPA_RIGHT			= static_cast<int>(1e6 + 1e3 + 100 + KOOPA_STATE_PARATROOPA);
#pragma endregion