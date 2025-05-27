#pragma once
#include "MarioState.h"

class CFlyMarioState :
    public CMarioState
{
protected:
	virtual void OnJump() override;
	virtual void OnReleaseJump() override;
public:
	CFlyMarioState(LPMARIO mario) : CMarioState(mario) {}
	virtual int GetAniId() override;
	virtual void GetBoundingBox(float& width, float& height) override;
	virtual void HandleStateChange(int state) override;
	
	~CFlyMarioState() {}
};

typedef CFlyMarioState* LPFLYMARIOSTATE;

