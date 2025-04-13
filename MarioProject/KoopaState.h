#pragma once
#include<Windows.h>
#include<vector>

using namespace std;

struct CCollisionEvent; typedef CCollisionEvent* LPCOLLISIONEVENT;
class CPhysicalObject; typedef CPhysicalObject* LPPHYSICALOBJECT;
class CKoopa; typedef CKoopa* LPKOOPA;

class CKoopaState {
protected:
	void ChangeDirection(LPKOOPA koopa, ULONGLONG speed);
public:
	CKoopaState() {};
	CKoopaState(LPKOOPA koopa);

	virtual void Update(LPKOOPA koopa, DWORD dt);
	virtual void OnCollisionWith(LPKOOPA koopa, LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& width, float& height);

	virtual int GetAnimationID(LPKOOPA koopa) = 0;
};

typedef CKoopaState* LPKOOPASTATE;