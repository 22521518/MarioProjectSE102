#pragma once
#include "MarioState.h"

class CFlyMarioState :
    public CMarioState
{
protected:
	virtual void OnJump(LPMARIO mario) override;
	virtual void OnReleaseJump(LPMARIO mario) override;
public:
	CFlyMarioState() : CMarioState() {}
	virtual int GetAniId(LPMARIO mario) override;
	virtual void GetBoundingBox(LPMARIO mario, float& width, float& height) override;
	virtual void HandleStateChange(LPMARIO mario, int state) override;
	
	~CFlyMarioState() {}
};

typedef CFlyMarioState* LPFLYMARIOSTATE;

