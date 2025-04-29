#pragma once
#include "PhysicalObject.h"
#include "CollidableWithMario.h"

class CItem :
	public CPhysicalObject, public CCollidableWithMario {
public:
	CItem(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left)
		: CPhysicalObject(x, y, vx, vy, ax, ay, nx) {};

	// game object method
	virtual void Render() = 0;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0;

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) = 0;

	virtual int IsCollidable() override { return 0; }
	virtual int IsBlocking() override { return 0; };
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
};

typedef CItem* LPITEM;