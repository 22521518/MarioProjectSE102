#pragma once
#include "MarioState.h"

class CFlyMarioState :
    public CMarioState
{
protected:
	void OnRun (bool isLeft) override;
	void OnJump() override;
	void OnReleaseJump() override;
public:
	CFlyMarioState(LPMARIO mario) : CMarioState(mario) {}
	int GetAniId() override;
	void GetBoundingBox(float& width, float& height) override;
	
	~CFlyMarioState() {}
};

typedef CFlyMarioState* LPFLYMARIOSTATE;

