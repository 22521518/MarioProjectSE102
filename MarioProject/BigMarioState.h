#pragma once
#include "MarioState.h"
class CBigMarioState :
    public CMarioState
{
public:
	virtual int GetAniId(LPMARIO mario) override;

	~CBigMarioState() {}
};

typedef CBigMarioState* LPBIGMARIOSTATE;