#pragma once

#include "CollisionEvent.h"
#include "DirectionType.h"

class CPhysicalObject;
typedef CPhysicalObject* LPPHYSICALOBJECT;

#define BLOCK_PUSH_FACTOR 0.1f

class CCollision {
	static CCollision* __instance;
	CCollision() {};

	static bool IsOverlap(const RECT* obj1, const RECT* obj2);
	static bool IsOverlap(float l1, float t1, float r1, float b1, float l2, float t2, float r2, float b2);
	LPCOLLISIONEVENT SweptAABB(LPPHYSICALOBJECT objSrc, DWORD dt, LPPHYSICALOBJECT objDest);

	// Find all the collision events between objSrc and objDests
	void Scan(
		LPPHYSICALOBJECT objSrc, DWORD dt,
		vector<LPPHYSICALOBJECT>* objDests,
		vector<LPCOLLISIONEVENT>& coEvents);

	// Find the first collision event in coEvents
	void Filter(
		LPPHYSICALOBJECT objSrc,
		vector<LPCOLLISIONEVENT>& coEvents,
		LPCOLLISIONEVENT& colX,
		LPCOLLISIONEVENT& colY,
		int filterBlock = 1,	// 1: filter block collisions, 0: filter all collisions 
		int filterX = 1,		// 1: process events on X, 0: skip events on X 
		int filterY = 1			// 1: process events on Y, 0: skip events on Y
	);
public:
	static CCollision* GetInstance();
	static void SweptAABB(
		RECT* movingObj,
		float distanceX, float distanceY,		// relative movement distance in one frame
		RECT* staticObj,
		float& time, DirectionXAxisType& normalX, DirectionYAxisType& normalY
	);
	static void SweptAABB(float movingLeft, float movingTop, float movingRight, float movingBot,
		float distanceX, float distanceY,
		float staticLeft, float staticTop, float staticRight, float staticBot,
		float& time, DirectionXAxisType& normalX, DirectionYAxisType& normalY);

	// interactive object will react to the first collision event in coEvents
	void Process(LPINTERACTIVEOBJECT objSrc, DWORD dt, vector<LPPHYSICALOBJECT>* coObjs); 
	void ProcessCollisionY(LPINTERACTIVEOBJECT objSrc, float& positionX, float& positionY, float distanceY, 
		LPCOLLISIONEVENT colY, bool setPosFlag = false);
	void ProcessCollisionX(LPINTERACTIVEOBJECT objSrc, float& positionX, float& positionY, float distanceX,
		LPCOLLISIONEVENT colX, bool setPosFlag = false);
};