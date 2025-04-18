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

void CCollisionEvent::printInfo()
{
	DebugOut(L"[Collision Event]\n");
	DebugOut(L"Time: %.4f\n", time);
	DebugOut(L"NormalX: %d\n", (int)normalX);
	DebugOut(L"NormalY: %d\n", (int)normalY);
	DebugOut(L"DistanceX: %.4f\n", distanceX);
	DebugOut(L"DistanceY: %.4f\n", distanceY);
	DebugOut(L"Deleted: %d\n", isDeleted);

	DebugOut(L"Source Object Class: ");
	DebugOutObjectClassName(src_obj);

	DebugOut(L"Target Object Class: ");
	DebugOutObjectClassName(obj);
}