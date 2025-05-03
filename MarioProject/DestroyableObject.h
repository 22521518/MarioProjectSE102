#pragma once
struct CCollisionEvent; typedef CCollisionEvent* LPCOLLISIONEVENT;

class CDestroyableObject {
public:
	virtual void OnDestroy(LPCOLLISIONEVENT e) = 0;
};

typedef CDestroyableObject* LPDESTROYABLEOBJECT;