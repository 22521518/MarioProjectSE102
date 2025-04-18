#pragma once
	#include "KoopaState.h"
	#include "Koopa.h"
#include "KoopaAniIDs.h"

class CRedKoopaState : public CKoopaState {
public:
	CRedKoopaState(LPKOOPA koopa) : CKoopaState(koopa) {};

	virtual int GetAnimationID(LPKOOPA koopa) 
	{
		return  koopa->nx == DirectionXAxisType::Left ? ID_ANI_RED_KOOPA_WALKING_LEFT : ID_ANI_RED_KOOPA_WALKING_RIGHT;
	};

	virtual void OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e) override;
};