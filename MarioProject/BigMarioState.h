#pragma once
#include "MarioState.h"
class CBigMarioState :
    public CMarioState
{
public:
	CBigMarioState(LPMARIO mario) : CMarioState(mario) {}
	virtual int GetAniId() override;
	virtual void GetBoundingBox(float& width, float& height) override;

	~CBigMarioState() {}
};

typedef CBigMarioState* LPBIGMARIOSTATE;