#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"

constexpr float ACHIEVEMENT_HEIGHT = 16.f;
constexpr float ACHIEVEMENT_WIDTH = 16.f;

class CAchievementObject :
	public CInteractiveObject, public CCollidableWithMario {
	ULONGLONG mario_touch_start = 0;
public:
	CAchievementObject(float x = 0, float y = 0);
	void Render() override;
	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
	void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	virtual void OnNoCollision(DWORD dt) override { y += vy; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;

	virtual int IsCollidable() override { return 0; }
	virtual int IsBlocking() override { return 0; };
	int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return true; };
};