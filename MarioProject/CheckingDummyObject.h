#pragma once
#include "Character.h"

class CInteractableWithEdge;
typedef CInteractableWithEdge* LPINTERACTABLEWITHEDGE;

class CCheckingDummyObject : public CCharacter {
public:
	CCheckingDummyObject(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1)
		: CCharacter(x, y, vx, vy, ax, ay, nx, state) {};

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0; // its size
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0; // how to simulate the source object
	virtual void OnNoCollision(DWORD dt) = 0; // interact before falling
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0; // interact before colision

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };

	virtual void Render() override { RenderBoundingBox(); }; // maybe you want to check where it is
	virtual bool IsDeadState() override { return false; }; // the must override method
};

typedef CCheckingDummyObject* LPCHECKINGDUMMYOBJECT;

/*
NOTE:		this abstract object used to make simulate some situation and interact before the actual one happen
WEAKNESS:	this just logic may handle the simulation at specific position (not really actual behavior)
*/