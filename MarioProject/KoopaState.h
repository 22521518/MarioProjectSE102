#pragma once
#include<Windows.h>
#include<vector>
#include "KoopaConfig.h"

using namespace std;

struct CCollisionEvent; typedef CCollisionEvent* LPCOLLISIONEVENT;
class CPhysicalObject; typedef CPhysicalObject* LPPHYSICALOBJECT;
class CKoopa; typedef CKoopa* LPKOOPA;

class CKoopaState {
protected:
public:
	CKoopaState() {};
	CKoopaState(LPKOOPA koopa);
	
	virtual void ChangeDirection(LPKOOPA koopa, float speed = KOOPA_WALKING_SPEED);

	virtual void OnNoCollision(LPKOOPA koopa, DWORD dt);
	virtual void OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& width, float& height);

	virtual int GetAnimationID(LPKOOPA koopa) = 0;
};

typedef CKoopaState* LPKOOPASTATE;