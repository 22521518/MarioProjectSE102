#pragma once
#include "KoopaState.h"
#include "KoopaAniIDs.h"
#include "Koopa.h"

class CGreenKoopaParatroopaState : public CKoopaState {
	float maxVy = KOOPA_MAX_VY;
	int state = GREEN_KOOPA_STATE_PARATROOPA_JUMP;
public:
	CGreenKoopaParatroopaState(LPKOOPA koopa, int state = GREEN_KOOPA_STATE_PARATROOPA_JUMP);

	virtual int GetAnimationID(LPKOOPA koopa)
	{
		return  koopa->nx == DirectionXAxisType::Left ? ID_ANI_GREEN_KOOPA_PARATROOPA_LEFT : ID_ANI_GREEN_KOOPA_PARATROOPA_RIGHT;
	};
	virtual void ChangeDirection(LPKOOPA koopa, float speed = KOOPA_WALKING_SPEED) override;
	virtual void OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e) override;
};

