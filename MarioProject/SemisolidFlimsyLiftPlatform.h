#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"
#include "PlatformConfig.h"

class CSemisolidFlimsyLiftPlatform :
	public CInteractiveObject, public CCollidableWithMario
{
	ULONGLONG mario_step_on_start = 0;
	int length, height;
	float cellWidth, cellHeight; // Unit: cell 
	int spriteIdTopBegin, spriteIdTopMiddle, spriteIdTopEnd,
		spriteIdMidBegin, spriteIdMidMiddle, spriteIdMidEnd,
		spriteIdBotBegin, spriteIdBotMiddle, spriteIdBotEnd;

public:
	CSemisolidFlimsyLiftPlatform(float x = 0, float y = 0, int length = 1, int height = 1,
		float cell_width = 16, float cell_height = 16,
		int sprite_id_top_begin = 0, int sprite_id_top_middle = 0, int sprite_id_top_end = 0,
		int sprite_id_mid_begin = 0, int sprite_id_mid_middle = 0, int sprite_id_mid_end = 0,
		int sprite_id_bot_begin = 0, int sprite_id_bot_middle = 0, int sprite_id_bot_end = 0
	);

	// game object method
	void Render() override;
	void RenderByRow(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) const;

	void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
	void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	virtual void OnNoCollision(DWORD dt) override { x += vx, y += vy; };
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;

	virtual int IsCollidable() override { return 0; }
	virtual int IsBlocking() override { return 1; };
	int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override
	{
		return ny == DirectionYAxisType::Top;
	};

	void ResetState() override
	{
		CPhysicalObject::ResetState();
		mario_step_on_start = 0;
	};
};


