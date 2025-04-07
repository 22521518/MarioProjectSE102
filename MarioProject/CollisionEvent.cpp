#include "CollisionEvent.h"

CCollisionEvent::CCollisionEvent(float t, DirectionXAxisType nx, DirectionYAxisType ny, float dx, float dy, LPPHYSICALOBJECT obj, LPPHYSICALOBJECT src_obj)
{
	this->time = t;
	this->normalX = nx;
	this->normalY = ny;
	this->distanceX = dx;
	this->distanceY = dy;
	this->obj = obj;
	this->src_obj = src_obj;
	this->isDeleted = false;
}

int CCollisionEvent::WasCollided() {
	if (obj == NULL) return 0;
	return
		time >= 0.0f && time <= 1.0f && obj->IsDirectionColliable(normalX, normalY) == 1;
}

bool CCollisionEvent::compare(CCollisionEvent*& a, CCollisionEvent*& b) {
	return a->time < b->time;
}