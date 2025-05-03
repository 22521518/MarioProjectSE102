#pragma once
#include "BrickItem.h"

class CBrickSuperItem :
	public CBrickItem
{
	bool onBounce = false;
public:
	CBrickSuperItem(LPMARIO mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = BRICK_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = BRICK_STATE_ACTIVE, int numberOfCollision = 1)
		: CBrickItem (mario, x, y, vx, vy, ax, ay, nx, state, numberOfCollision) { }
	void CreateSuperLeaf(LPCOLLISIONEVENT e);
	void CreateSuperMushroom(LPCOLLISIONEVENT e);

	// game object method
	virtual void Render() override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	// on mario collide
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
	virtual void OnDestroy (LPCOLLISIONEVENT e) override;

	virtual void Bouncing();
};

typedef CBrickSuperItem* LPBRICKSUPERITEM;