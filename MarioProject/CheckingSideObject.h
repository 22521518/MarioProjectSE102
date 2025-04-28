#pragma once
#include "CheckingDummyObject.h"

// interface for object that interact on the edge
class CInteractableWithSideCollision {
public:
	virtual void OnSideCollisionBehavior(LPCOLLISIONEVENT e) = 0;
	virtual void GetObjectBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual DirectionXAxisType GetObjectCurrentDirectionX() = 0;
};
typedef CInteractableWithSideCollision* LPINTERACTABLEWITHSIDECOLLISION;

class CCheckingSideObject : public CCheckingDummyObject {
	LPINTERACTABLEWITHSIDECOLLISION obj;
public:
	CCheckingSideObject(LPINTERACTABLEWITHSIDECOLLISION obj, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	virtual void OnNoCollision(DWORD dt) override {}; 
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override; 

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };


	virtual void Render() { RenderBoundingBox(); };
	virtual bool IsDeadState() { return false; };
};

typedef CCheckingSideObject* LPCHECKINGSIDEOBJECT;

/*
NOTE: this object check whether the front position make real obj collision or not (override OnCollisionWith)
*/
