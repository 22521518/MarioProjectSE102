#pragma once
#include "CheckingDummyObject.h"


class CInteractableWithEdge;
typedef CInteractableWithEdge* LPINTERACTABLEWITHEDGE;

class CCheckingEdgeObject : public CCheckingDummyObject {
	LPINTERACTABLEWITHEDGE obj;
public:
	CCheckingEdgeObject(LPINTERACTABLEWITHEDGE obj, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1);
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	virtual void OnNoCollision(DWORD dt) override;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override; // this leave empty

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };
};

typedef CCheckingEdgeObject* LPCHECKINGEDGEOBJECT;

/*
NOTE: this object check whether the front position make real obj fall or not (override OnNoCollision)
*/