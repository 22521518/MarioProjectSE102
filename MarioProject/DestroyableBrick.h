#pragma once
#include "Brick.h"
#include "DestroyableObject.h"

class CBreakBrickEffect;
typedef CBreakBrickEffect* LPBREAKBRICKEFFECT;

class CDestroyableBrick : public CBrick, public CDestroyableObject
{
	bool isDestroy = false;
	ULONGLONG timeDestroy = 0;
	vector<LPBREAKBRICKEFFECT> pieces;
protected:
	bool isRemovable = true;

public:
	CDestroyableBrick(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0)
		: CBrick(x, y, vx, vy, ax, ay) {
	}

	// game object method
	virtual void Render() override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

	// destroyable object method
	virtual void OnDestroy(LPCOLLISIONEVENT e) override;
};

typedef CDestroyableBrick* LPDESTROYABLEBRICK;

