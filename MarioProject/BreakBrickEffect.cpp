#include "BreakBrickEffect.h"
#include "BrickIDs.h"

void CBreakBrickEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BREAK_BRICK_EFFECT)->Render(x, y);
}
