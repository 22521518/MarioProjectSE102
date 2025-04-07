#pragma once
#include "InteractiveObject.h"

class CCharacter: public CInteractiveObject
{

public:
	CCharacter(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) {}

	// game object method
	virtual void Render() = 0;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void GetBoundingBox(RECT& rect) override { CPhysicalObject::GetBoundingBox(rect); };
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 1; };
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) { return 1; };

	// interactive object method
	virtual void OnNoCollision(DWORD dt) override;
	//virtual void SetState(int state) {} // use default
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;

	//character method
	virtual bool IsDeadState() = 0;
};

typedef CCharacter* LPCHARACTER;