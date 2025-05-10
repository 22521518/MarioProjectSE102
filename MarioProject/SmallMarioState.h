#pragma once
#include "MarioState.h"
class CSmallMarioState :
    public CMarioState
{
public:
	CSmallMarioState() : CMarioState() {}
	virtual int GetAniId(LPMARIO mario) override;
	virtual void GetBoundingBox(LPMARIO mario, float& width, float& height) override;
	~CSmallMarioState() {}
};

typedef CSmallMarioState* LPSMALLMARIOSTATE;
