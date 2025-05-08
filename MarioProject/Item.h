#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"

class CItem :
	public CInteractiveObject, public CCollidableWithMario {
	bool isActive = true;
public:
	CItem(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1) : CInteractiveObject(x, y, vx, vy, ax, ay, nx, state) { isRemovable = true; };

	// game object method
	virtual void Render() = 0;

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) = 0;

	// interactive object method
	virtual void OnNoCollision(DWORD dt) = 0;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) = 0;

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) = 0;

	virtual int IsCollidable() override { return 0; }
	virtual int IsBlocking() override { return 0; };
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };

	virtual void SetActive(bool acitve) { this->isActive = acitve; }
	bool GetActive() const { return this->isActive; }

	void ResetState() override {}
};

typedef CItem* LPITEM;