#pragma once
#include "KoopaState.h"
#include "KoopaAniIDs.h"
#include "Koopa.h"

class CRedKoopaParatroopaState : public CKoopaState {
public:
	CRedKoopaParatroopaState(LPKOOPA koopa);
	virtual void ChangeDirection(LPKOOPA koopa, float speed) override;

	virtual int GetAnimationID(LPKOOPA koopa)
	{
		return  koopa->nx == DirectionXAxisType::Left ? ID_ANI_RED_KOOPA_PARATROOPA_LEFT : ID_ANI_RED_KOOPA_PARATROOPA_RIGHT;
	};

	virtual void OnNoCollision(LPKOOPA koopa, DWORD dt) override;
	virtual void OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e) override;
};
 