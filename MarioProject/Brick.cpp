#include "Brick.h"
#include "BrickIDs.h"
//#include "BrickStateIDs.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}