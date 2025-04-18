#pragma once
#include "KoopaState.h"
#include "Koopa.h"
#include "KoopaAniIDs.h"

class CGreenKoopaState : public CKoopaState {
public:
	CGreenKoopaState(LPKOOPA koopa) : CKoopaState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa)
	{
		return  koopa->nx == DirectionXAxisType::Left ? ID_ANI_GREEN_KOOPA_WALKING_LEFT : ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
	};
};