#pragma once
#include "StaticObject.h"
#include "CollidableWithMario.h"

class CCoin :
    public CStaticObject, public CCollidableWithMario
{
protected:
public:
	CCoin(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0)
		: CStaticObject(x, y, vx, vy, ax, ay) {}
	// game object method
	virtual void Render() override;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual int IsBlocking() override { return 0; };

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;

};

typedef CCoin* LPCOIN;