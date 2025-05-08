#include "RedGoomba.h"
#include "GoombaAniIDs.h"

void CRedGoomba::Render()
{
	int aniId = ID_ANI_RED_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_RED_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
