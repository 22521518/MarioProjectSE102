#pragma once

#include "PhysicalObject.h"
#include "DirectionType.h"

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

class CInteractiveObject : public CPhysicalObject {
protected:
	int state = -1;
public:
	CInteractiveObject(float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state = -1)
		:CPhysicalObject(x, y, vx, vy, ax, ay, nx), state(state) {}
	
	// game object method
	virtual void Render() = 0;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void GetBoundingBox(RECT& rect) override { CPhysicalObject::GetBoundingBox(rect); };
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0;

	// interactive object method
	virtual void SetState(int state) { this->state = state; }
	virtual void OnNoCollision(DWORD dt) = 0;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;

	int GetState() const { return this->state; }
};

typedef CInteractiveObject* LPINTERACTIVEOBJECT;