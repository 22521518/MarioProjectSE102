#pragma once

constexpr int ID_TEX_MARIO									= 0;
constexpr int ID_TEX_ENEMY									= 10;
constexpr int ID_TEX_MISC									= 20;

constexpr int OBJECT_TYPE_MARIO								= 0;
constexpr int OBJECT_TYPE_BRICK								= 1;
constexpr int OBJECT_TYPE_GOOMBA							= 2;
constexpr int OBJECT_TYPE_KOOPAS							= 3;
constexpr int OBJECT_TYPE_COIN								= 4;
constexpr int OBJECT_TYPE_PLATFORM							= 5;
constexpr int OBJECT_TYPE_PORTAL							= 50;

#pragma region TRI_OBJ
// background

constexpr int OBJECT_TYPE_GAME_BACKGROUND_9_SPRITE = static_cast <int>(5e6 + 800);
constexpr int OBJECT_TYPE_GAME_BACKGROUND_COLOR_9_SPRITE = static_cast <int>(5e6 + 900);

// platform
constexpr int OBJECT_TYPE_SOLID_SEMISOLID_PLATFORM_9_SPRITE = static_cast<int>(3e6);
constexpr int OBJECT_TYPE_SOLID_SOLID_PLATFORM_9_SPRITE		= static_cast<int>(3e6 + 1e3);

// item
constexpr int OBJECT_TYPE_ITEM_BRICK						= static_cast<int>(2e6 + 2e4);
constexpr int OBJECT_TYPE_ONE_UP_MUSHROOM_ITEM				= static_cast<int>(2e6 + 2e3);
constexpr int OBJECT_TYPE_SUPER_MUSHROOM_ITEM				= static_cast<int>(2e6 + 1e3);
constexpr int OBJECT_TYPE_SUPER_LEAF_ITEM					= static_cast<int>(2e6);

constexpr int OBJECT_TYPE_DESTROYABLE_BRICK					= static_cast<int>(1e6 + 2e4);

// enemy
constexpr int OBJECT_TYPE_RED_KOOPA							= static_cast<int>(1e6);
constexpr int OBJECT_TYPE_GREEN_KOOPA						= static_cast<int>(1e6 + 1e4);
constexpr int OBJECT_TYPE_RED_KOOPA_TROOPA					= static_cast<int>(1e6 + 2e3);
constexpr int OBJECT_TYPE_GREEN_KOOPA_TROOPA				= static_cast<int>(1e6 + 3e3);
constexpr int OBJECT_TYPE_RED_PARAGOOMBA					= static_cast<int>(1e6 + 5e4 + 100);
#pragma endregion

constexpr int ID_SPRITE_MARIO								= static_cast<int>(1e5);
constexpr int ID_SPRITE_BRICK								= static_cast<int>(2e5);
constexpr int ID_SPRITE_GOOMBA								= static_cast<int>(3e5);
constexpr int ID_SPRITE_COIN								= static_cast<int>(4e5);
constexpr int ID_SPRITE_CLOUD								= static_cast<int>(5e5);

constexpr int ID_SPRITE_BLOCK_Q_COIN = static_cast<int>(2e5 + 11e3);
constexpr int ID_SPRITE_BLOCK_Q_ITEM = static_cast<int>(2e5 + 12e3);

#pragma region THANH_OBJ
constexpr int OBJECT_TYPE_PLANT_ENEMY = 650;
constexpr int OBJECT_TYPE_PLANT_GP = 651;
constexpr int OBJECT_TYPE_PLANT_GVF = 652;
constexpr int OBJECT_TYPE_PLANT_RVF = 653;
constexpr int OBJECT_TYPE_BLOCK_Q_COIN = 11;
constexpr int OBJECT_TYPE_BLOCK_Q_ITEM = 12;
constexpr int OBJECT_TYPE_BLOCK_W = 13;
constexpr int OBJECT_TYPE_BLOCK_F = 14;
#pragma endregion