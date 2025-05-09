#include "CheckingSideObject.h"

CCheckingSideObject::CCheckingSideObject(LPINTERACTABLEWITHSIDECOLLISION obj, float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state) 
	: CCheckingDummyObject(x, y, vx, vy, ax, ay, nx, state)
{
	this->obj = obj;
}

void CCheckingSideObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//			top
	// l-r_[l<-(x, y)->r]_l-r
	//			bot

	this->obj->GetObjectBoundingBox(left, top, right, bottom);
	DirectionXAxisType dir = this->obj->GetObjectCurrentDirectionX();

	float oldLeft = left, oldRight = right, height = bottom - top;
	bottom -= 0.05f;
	top += 0.05f;

	const float CHECK_PADDING = 2.0f;
	const float CHECK_WIDTH = 0.5f;

	if (this->obj->GetObjectCurrentDirectionX() == DirectionXAxisType::Right)
	{
		left = oldRight + CHECK_PADDING;
		right = left + CHECK_WIDTH;
	}
	else if (this->obj->GetObjectCurrentDirectionX() == DirectionXAxisType::Left)
	{
		right = oldLeft - CHECK_PADDING;
		left = right - CHECK_WIDTH;
	}
}

void CCheckingSideObject::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	CCharacter::Update(dt, coObjects);
}

void CCheckingSideObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	this->obj->OnSideCollisionBehavior(e);
}
