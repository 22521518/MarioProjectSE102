#pragma once

#include "PhysicalObject.h"
#include "DirectionType.h"

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

class CInteractiveObject : public CPhysicalObject {
	const int originState;
protected:
	int state = -1;
public:
	CInteractiveObject(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1)
		:CPhysicalObject(x, y, vx, vy, ax, ay, nx), state(state), originState(state) {}
	
	// game object method
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;

	// physical object method
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0;

	// interactive object method
	virtual void SetState(int state) { this->state = state; }
	virtual void OnNoCollision(DWORD dt) = 0;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;

	int GetState() const { return this->state; }
	void ResetState() override
	{
		CPhysicalObject::ResetState();
		this->state = originState;
		this->SetState(state);
	};
};

typedef CInteractiveObject* LPINTERACTIVEOBJECT;