#pragma once
#pragma region ITEM_BBOX
constexpr float SUPER_LEAF_BBOX_WIDTH = 16;	
constexpr float SUPER_LEAF_BBOX_HEIGHT = 14;

constexpr float MUSHROOM_BBOX_WIDTH = 16;
constexpr float MUSHROOM_BBOX_HEIGHT = 16;
#pragma endregion

#pragma region SUPER_LEAF_ITEM
constexpr float SUPER_LEAF_FALL_SPEED = 0.025f;
constexpr float SUPER_LEAF_FALL_GRAVITY = 0.000005f;
constexpr float SUPER_LEAF_SWAY_SPEED = 0.005f;
constexpr float SUPER_LEAF_SWAY_AMPLITUDE = 30.0f;
#pragma endregion

#pragma region MUSHROOM_ITEM
constexpr float MUSHROOM_RISE_DISTANCE = MUSHROOM_BBOX_HEIGHT;
constexpr float MUSHROOM_GROW_WAIT_TIME = 200;
constexpr float MUSHROOM_GROW_SPEED = 0.025f;

constexpr float MUSHROOM_GRAVITY = 0.002f;
constexpr float MUSHROOM_SPPED = 0.05f;
#pragma endregion

