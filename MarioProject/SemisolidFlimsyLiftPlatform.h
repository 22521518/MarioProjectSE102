#pragma once
#include "SemisolidPlatform.h"
#include "CollidableWithMario.h"
#include "PlatformConfig.h"

class CSemisolidFlimsyLiftPlatform :
	public CSemisolidPlatform, public CCollidableWithMario
{
	ULONGLONG mario_step_on_start = 0;

public:
	CSemisolidFlimsyLiftPlatform(float x = 0, float y = 0, int length = 1, int height = 1,
		float cell_width = 16, float cell_height = 16,
		int sprite_id_top_begin = 0, int sprite_id_top_middle = 0, int sprite_id_top_end = 0,
		int sprite_id_mid_begin = 0, int sprite_id_mid_middle = 0, int sprite_id_mid_end = 0,
		int sprite_id_bot_begin = 0, int sprite_id_bot_middle = 0, int sprite_id_bot_end = 0
	) : CSemisolidPlatform(x, y, length, height, cell_width, cell_height,
		sprite_id_top_begin, sprite_id_top_middle, sprite_id_top_end,
		sprite_id_mid_begin, sprite_id_mid_middle, sprite_id_mid_end,
		sprite_id_bot_begin, sprite_id_bot_middle, sprite_id_bot_end) {
		this->SetOriginSpeed(LIFT_PLATFORM_HORIZONTIAL_SPEED, 0);
	}


	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
	void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override
	{
		return ny == DirectionYAxisType::Top;
	};

	void ResetState() override
	{
		CPhysicalObject::ResetState();
		mario_step_on_start = 0;
	};
};


