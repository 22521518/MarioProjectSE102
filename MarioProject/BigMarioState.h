#pragma once
#include "MarioState.h"
class CBigMarioState :
    public CMarioState
{
public:
	CBigMarioState(): CMarioState() {}
	virtual int GetAniId(LPMARIO mario) override;
	virtual void GetBoundingBox(LPMARIO mario, float& width, float& height) override;

	~CBigMarioState() {}
};

typedef CBigMarioState* LPBIGMARIOSTATE;