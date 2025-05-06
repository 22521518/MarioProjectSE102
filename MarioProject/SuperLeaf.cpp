#define _USE_MATH_DEFINES
#include <cmath>
#include "SuperLeaf.h"
#include "DirectionType.h"
#include "ItemAniIDs.h"
#include "ItemConfig.h"
#include "Collision.h"

void CSuperLeaf::Render()
{
	this->RenderBoundingBox();
	int aniId = this->GetNX() == DirectionXAxisType::Right ?
		ID_ANI_SUPER_LEAF_ITEM_RIGHT : ID_ANI_SUPER_LEAF_ITEM_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CSuperLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - (SUPER_LEAF_BBOX_WIDTH / 2.0f);
	top = y - (SUPER_LEAF_BBOX_HEIGHT / 2.0f);
	right = left + SUPER_LEAF_BBOX_WIDTH;
	bottom = top + SUPER_LEAF_BBOX_HEIGHT;
}

void CSuperLeaf::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	this->timelapse += dt;

	float sway = swayAmplitude * sin(swaySpeed * timelapse);
	this->x = startX + sway;
	this->y += this->vy * dt;

	this->nx = sway > 0 ?
		DirectionXAxisType::Right : DirectionXAxisType::Left;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSuperLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	LPMARIO mario = dynamic_cast<LPMARIO>(e->obj);
	if (mario)
	{
		this->OnMarioCollide(mario, e);
		return;
	}	
}

void CSuperLeaf::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	this->Delete();
	mario->OnCollisionWithSuperLeaf(this, e);
}
