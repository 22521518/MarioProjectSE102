#include "BreakBrickEffect.h"
#include "BrickAniIDs.h"

void CBreakBrickEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BREAK_BRICK_EFFECT)->Render(x, y);
}

void CBreakBrickEffect::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	this->vy += this->ay * dt;
	this->vx += this->ax * dt;
	this->x  += this->vx * dt;
	this->y  += this->vy * dt;
}
