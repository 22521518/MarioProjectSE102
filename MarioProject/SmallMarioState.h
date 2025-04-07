#pragma once
#include "MarioState.h"
class CSmallMarioState :
    public CMarioState
{
public:
	virtual int GetAniId(LPMARIO mario) override;
	~CSmallMarioState() {}
};

typedef CSmallMarioState* LPSMALLMARIOSTATE;
