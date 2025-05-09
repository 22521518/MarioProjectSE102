#pragma once

class CMario;
typedef CMario* LPMARIO;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

class CHoldableWithMario
{
public:
	//virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects);
	virtual void SetObjectPosision(float x, float y) = 0;
	virtual void RenderObject() = 0;
	virtual bool IsHoldableState() = 0;
	virtual bool IsBeingHeld() = 0;
	virtual void OnMarioHold(LPMARIO mario, LPCOLLISIONEVENT e) = 0;
	virtual void OnMarioRelease(LPMARIO mario) = 0;
};

typedef CHoldableWithMario* LPHOLDABLEWITHMARIO;