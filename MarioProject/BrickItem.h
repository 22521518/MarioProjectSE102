#pragma once
#include "StaticObject.h"
#include "DestroyableObject.h"
#include "CollidableWithMario.h"
#include "BrickStateIDs.h"
#include "BrickConfig.h"
#include "Item.h"

class CBrickItem
	: public CStaticObject, public CCollidableWithMario, public CDestroyableObject{
protected:
	float startY;
	int state;
	int numberOfCollision = 1;
	vector<LPITEM> items;

public:
	CBrickItem(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = BRICK_STATE_ACTIVE, int numberOfCollision = 1) : CStaticObject(x, y, vx, vy, ax, ay, nx), startY(y), state(state), numberOfCollision(numberOfCollision) {}

	virtual int IsActive() { return this->state == BRICK_STATE_ACTIVE; }
	virtual void SetState(int state) { this->state = state; }
	static bool IsItemsDeleted(const LPITEM& o) { return o == nullptr; }
	void PurgeDeletedItems();

	// game object method
	virtual void Render() override;
	void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

	// on mario collide
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e);
	virtual void OnDestroy(LPCOLLISIONEVENT e);
};