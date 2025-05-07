#pragma once
#include "Platform9Sprite.h"
class CSemisolidPlatform :
    public CPlatform9Sprite
{
public:
	CSemisolidPlatform(float x = 0, float y = 0, int length = 1, int height = 1,
		float cell_width = 16, float cell_height = 16,
		int sprite_id_top_begin = 0, int sprite_id_top_middle = 0, int sprite_id_top_end = 0,
		int sprite_id_mid_begin = 0, int sprite_id_mid_middle = 0, int sprite_id_mid_end = 0,
		int sprite_id_bot_begin = 0, int sprite_id_bot_middle = 0, int sprite_id_bot_end = 0
	) : CPlatform9Sprite(x, y, length, height, cell_width, cell_height,
		sprite_id_top_begin, sprite_id_top_middle, sprite_id_top_end,
		sprite_id_mid_begin, sprite_id_mid_middle, sprite_id_mid_end,
		sprite_id_bot_begin, sprite_id_bot_middle, sprite_id_bot_end) {}


	int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override 
	{
		return ny == DirectionYAxisType::Top;
	};
};

