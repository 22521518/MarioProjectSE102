#pragma once
#include "MarioState.h"
class CSmallMarioState :
    public CMarioState
{
public:
	CSmallMarioState(LPMARIO mario) : CMarioState(mario) {}
	virtual int GetAniId() override;
	virtual void GetBoundingBox(float& width, float& height) override;
	~CSmallMarioState() {}
};

typedef CSmallMarioState* LPSMALLMARIOSTATE;
