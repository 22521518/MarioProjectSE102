#pragma once
#include "Character.h"


class CInteractableWithEdge;
typedef CInteractableWithEdge* LPINTERACTABLEWITHEDGE;

class CCheckingEdgeObject : public CCharacter {
	LPINTERACTABLEWITHEDGE obj;
public:
	CCheckingEdgeObject(LPINTERACTABLEWITHEDGE obj, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1);
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	virtual void OnNoCollision(DWORD dt) override;

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 1; };
	virtual int IsCollidable() override { return 1; };


	virtual void Render() { RenderBoundingBox(); };
	virtual bool IsDeadState() { return false; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

typedef CCheckingEdgeObject* LPCHECKINGEDGEOBJECT;