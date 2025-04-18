#include "CheckingEdgeObject.h"
#include "InteractableWithEdge.h"
#include "debug.h"
#include "CollisionEvent.h"

CCheckingEdgeObject::CCheckingEdgeObject(LPINTERACTABLEWITHEDGE obj, float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state)
	: CCharacter(x, y, vx, vy, ax, ay, nx, state)
{
	this->obj = obj;
}


void CCheckingEdgeObject::OnNoCollision(DWORD dt)
{
	this->obj->OnEdgeBehavior(dt);
}

void CCheckingEdgeObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CCheckingEdgeObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//			top
	// l-r_[l<-(x, y)->r]_l-r
	//			bot
	
	this->obj->GetObjectBoundingBox(left, top, right, bottom);
	DirectionXAxisType dir = this->obj->GetObjectCurrentDirectionX();

	float oldLeft = left, oldRight = right;

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

void CCheckingEdgeObject::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	// this cause bug no collision (REMEMBER)
	vy += ay * dt;
	vx += ax * dt;
	CCharacter::Update(dt, coObjects);
}
