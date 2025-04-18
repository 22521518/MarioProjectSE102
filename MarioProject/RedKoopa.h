#pragma once
#include "Koopa.h"
#include "Goomba.h"
#include "InteractableWithEdge.h"

class CRedKoopa : public CKoopa, public CInteractableWithEdge
{
	bool isFirstLanded = false;
public:
	CRedKoopa(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = KOOPA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = KOOPA_STATE_WALKING) : CKoopa(x, y, vx, vy, ax, ay, nx, state) 
	{ 
		SetState(state); 
	};
	// game object method
	// physical object method
	// interactive object method
	virtual void SetState(int state) override;
	virtual void SetState(int state, LPCOLLISIONEVENT e) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	// interactive with edge methods
	virtual void OnEdgeBehavior(DWORD dt);
	virtual void GetObjectBoundingBox(float& left, float& top, float& right, float& bottom) { this->GetBoundingBox(left, top, right, bottom); };
	virtual DirectionXAxisType GetObjectCurrentDirectionX() override { return this->nx; };

	

	friend class CRedKoopaState;
};

typedef CRedKoopa* LPREDKOOPA;

/*
NOTE: Red Koop Variation while change their direction on the edge of the platform
LOGIC: Create a dummy object (inherit from character or interactive or maybe koopa) to check fall (OnNoCollision)
ERROR: 
	+ This dummy (CheckingEdgeObject) should have all behavior as an usual object to simulate behavior 
	(in update, initially no update vecolity with acceleration cause no collision)
	+ Because this object born randomly on the sky so should check landed first (IsFirstLanded), 
	if not, the dummy (CheckingEdgeObject) will cause the OnEdgeBehavior 
*/