#pragma once
#include "RedGoomba.h"
class CRedParagoomba :
    public CRedGoomba
{
	int start_fly;
public:
	CRedParagoomba(float x = 0, float y = 0, float vx = 0, float vy = -GOOMBA_JUMP_VY, float ax = 0, float ay = GOOMBA_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = GOOMBA_STATE_FLY)
		: CRedGoomba(x, y, vx, vy, ax, ay, nx, state) {
		start_fly = GetTickCount64();
		this->SetState(state);
	};

	//game object method
	void Render() override;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	
	// interactive object method
	void SetState(int state) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	void ResetState() override 
	{
		CRedGoomba::ResetState();
		start_fly = GetTickCount64();
	}
};

