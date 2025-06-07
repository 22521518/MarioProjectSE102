#include "SemisolidFlimsyLiftPlatform.h"

void CSemisolidFlimsyLiftPlatform::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	mario_step_on_start = GetTickCount64();
}

void CSemisolidFlimsyLiftPlatform::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	x += vx;
	y += vy;
	if (x <= originX - LIFT_PLATFORM_RANGE_HORIZONTIAL_MOVEMENT || 
		x >= originX + LIFT_PLATFORM_RANGE_HORIZONTIAL_MOVEMENT) 
	{
		vx *= -1;
	}

	if (mario_step_on_start > 0 && GetTickCount64() - mario_step_on_start > LIFT_PLATFORM_VERTICAL_FALL_DELAY) {
		vy = LIFT_PLATFORM_VERTICAL_SPEED;
	}
}
