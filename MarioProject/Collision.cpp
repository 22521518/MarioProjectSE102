
#include "Collision.h"
#include "InteractiveObject.h"
#include "Character.h"
#include "Mario.h"
#include "Enemy.h"
#include "CheckingEdgeObject.h"

constexpr float MIN_FLOAT = -99999999999.0f;
constexpr float MAX_FLOAT = 99999999999.0f;

bool CCollision::IsOverlap(float l1, float t1, float r1, float b1, float l2, float t2, float r2, float b2) {
	return l1 < r2 && r1 > l2 && t1 < b2 && b1 > t2;
}

bool CCollision::IsOverlap(const RECT* obj1, const RECT* obj2) {
	return IsOverlap(
		static_cast<float>(obj1->left), static_cast<float>(obj1->top),
		static_cast<float>(obj1->right), static_cast<float>(obj1->bottom),
		static_cast<float>(obj2->left), static_cast<float>(obj2->top),
		static_cast<float>(obj2->right), static_cast<float>(obj2->bottom)
	);
}

void CCollision::SweptAABB(
	float movingLeft, float movingTop, float movingRight, float movingBot,
	float distanceX, float distanceY,
	float staticLeft, float staticTop, float staticRight, float staticBot, 
	float& time, DirectionXAxisType& normalX, DirectionYAxisType& normalY
) {
	//default no collision
	time = -1.0f;
	normalX = DirectionXAxisType::None;
	normalY = DirectionYAxisType::None;

	// moving object is not moving
	if (distanceX == 0 && distanceY == 0) return;

	float distanceX_entry, distanceX_exit, timeX_entry, timeX_exit;
	float distanceY_entry, distanceY_exit, timeY_entry, timeY_exit;

	// Broad-phase test: calc expanded bbox of moving object
	// Create a bbox that is expanded by the distance of the moving object
	float exBBoxLeft = distanceX > 0 ? movingLeft : movingLeft + distanceX;
	float exBBoxRight = distanceX > 0 ? movingRight + distanceX : movingRight;
	float exBBoxTop = distanceY > 0 ? movingTop : movingTop + distanceY;
	float exBBoxBot = distanceY > 0 ? movingBot + distanceY : movingBot;

	// if static object is outside of the scope of the moving object, return
	if (exBBoxRight < staticLeft || exBBoxLeft > staticRight || exBBoxBot < staticTop || exBBoxTop > staticBot) return;

	// moving right (dis right - left, otherwise left to right)
	// entry value: the distance to met
	// exit value = entry_distance + size of both objects
	distanceX_entry = distanceX > 0 ? staticLeft - movingRight : staticRight - movingLeft; 
	distanceY_entry = distanceY > 0 ? staticTop - movingBot : staticBot - movingTop;
	distanceX_exit = distanceX > 0 ? staticRight - movingLeft : staticLeft - movingRight; 
	distanceY_exit = distanceY > 0 ? staticBot - movingTop : staticTop - movingBot;

	// special case: moving object is not moving on X or Y
	timeX_entry = distanceX == 0 ? MIN_FLOAT : distanceX_entry / distanceX;
	timeX_exit = distanceX == 0 ? MAX_FLOAT : distanceX_exit / distanceX;
	timeY_entry = distanceY == 0 ? MIN_FLOAT : distanceY_entry / distanceY;
	timeY_exit = distanceY == 0 ? MAX_FLOAT : distanceY_exit / distanceY;

	// condition for collision: entry time is between 0 and 1 
	if ((timeX_entry < 0.0f && timeY_entry < 0.0f) || timeX_entry > 1.0f || timeY_entry > 1.0f) return;

	float t_entry = max(timeX_entry, timeY_entry);
	float t_exit = min(timeX_exit, timeY_exit);


	if (t_entry > t_exit) return;
	time = t_entry;

	if (timeX_entry > timeY_entry) {
		normalY = DirectionYAxisType::None;
		normalX = distanceX > 0 ? DirectionXAxisType::Left : DirectionXAxisType::Right;
	}
	else {
		normalX = DirectionXAxisType::None;
		normalY = distanceY > 0 ? DirectionYAxisType::Top : DirectionYAxisType::Bottom;
	}
}

void CCollision::SweptAABB(RECT* movingObj, float distanceX, float distanceY, RECT* staticObj, 
	float& time, DirectionXAxisType& normalX, DirectionYAxisType& normalY)
{
	if (IsOverlap(movingObj, staticObj))
	{
		time = 0.0f;
		normalY = DirectionYAxisType::None;
		normalX = DirectionXAxisType::None;
	}
	else
	{
		SweptAABB(
			movingObj->left, movingObj->top, movingObj->right, movingObj->bottom, distanceX, distanceY,
			staticObj->left, staticObj->top, staticObj->right, staticObj->bottom, time, normalX, normalY
		);
	}
}

LPCOLLISIONEVENT CCollision::SweptAABB(LPPHYSICALOBJECT objSrc, DWORD dt, LPPHYSICALOBJECT objDest)
{
	float movingLeft, movingTop, movingRight, movingBot;
	float staticLeft, staticTop, staticRight, staticBot;

	float time;
	DirectionXAxisType normalX;
	DirectionYAxisType normalY;

	float movingVX, movingVY;
	objSrc->GetSpeed(movingVX, movingVY);
	float movingDX = movingVX * dt,
		movingDY = movingVY * dt;

	float staticVX, staticVY;
	objDest->GetSpeed(staticVX, staticVY);
	float staticDX = staticVX * dt,
		staticDY = staticVY * dt;

	float distanceX = movingDX - staticDX,
		distanceY = movingDY - staticDY;

	objSrc->GetBoundingBox(movingLeft, movingTop, movingRight, movingBot);
	objDest->GetBoundingBox(staticLeft, staticTop, staticRight, staticBot);

	// Check overlapped collision
	if (IsOverlap(movingLeft, movingTop, movingRight, movingBot, staticLeft, staticTop, staticRight, staticBot))
	{
		time = 0.0f;
		normalY = DirectionYAxisType::None;
		normalX = DirectionXAxisType::None;
	} 
	else
	{
		CCollision::SweptAABB(
			movingLeft, movingTop, movingRight, movingBot,
			distanceX, distanceY,
			staticLeft, staticTop, staticRight, staticBot,
			time, normalX, normalY
		);
	}

	return new CCollisionEvent(time, normalX, normalY, distanceX, distanceY, 
		objDest, objSrc);
}

void CCollision::Scan(LPPHYSICALOBJECT objSrc, DWORD dt, 
	vector<LPPHYSICALOBJECT>* objDests, vector<LPCOLLISIONEVENT>& coEvents)
{
	coEvents.reserve(objDests->size()); // optimize by reserving memory for the number of objects to be checked

	for (UINT i = 0; i < objDests->size(); i++)
	{
		if (objSrc == objDests->at(i) || 
			(dynamic_cast<LPMARIO>(objDests->at(i)) && dynamic_cast<LPENEMY>(objSrc))) continue;
		LPCOLLISIONEVENT e = SweptAABB(objSrc, dt, objDests->at(i));
		if (e->WasCollided() == 1) 
		{
			coEvents.push_back(e);
		}
		else 
		{
			delete e; // remember to delete the event if it is not a collision
		}
	}
	sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CCollision::Filter(LPPHYSICALOBJECT objSrc, vector<LPCOLLISIONEVENT>& coEvents, LPCOLLISIONEVENT& colX, LPCOLLISIONEVENT& colY, int filterBlock, int filterX, int filterY)
{
	float min_tx = 1.0f, min_ty = 1.0f;
	int min_ix = -1, min_iy = -1;
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (c->isDeleted || c->obj->IsDeleted()) // skip deleted events
		{
			continue;
		}
		if (filterBlock == 1 && !c->obj->IsBlocking()) // ignore non-blocking objects
		{
			continue;
		}
		// near collision on X
		if (c->time < min_tx && c->normalX != DirectionXAxisType::None && filterX == 1) {
			min_tx = c->time; 
			min_ix = i;
		}

		// near collision on Y
		if (c->time < min_ty && c->normalY != DirectionYAxisType::None && filterY == 1) {
			min_ty = c->time; 
			min_iy = i;
		}
	}
	if (min_ix >= 0) colX = coEvents[min_ix];
	if (min_iy >= 0) colY = coEvents[min_iy];
}

void CCollision::ProcessCollisionX(LPINTERACTIVEOBJECT objSrc, float& positionX, float& positionY, float distanceX, LPCOLLISIONEVENT colX, bool setPosFlag) {
	if (colX == NULL) {
		positionX += distanceX;
		return;
	}

	int normalXValue = static_cast<int>(colX->normalX);
	positionX += colX->time * distanceX + normalXValue * BLOCK_PUSH_FACTOR;

	if (setPosFlag) {
		objSrc->SetPosition(positionX, positionY);
	}
	objSrc->OnCollisionWith(colX);
}

void CCollision::ProcessCollisionY(LPINTERACTIVEOBJECT objSrc, float& positionX, float& positionY, float distanceY, LPCOLLISIONEVENT colY, bool setPosFlag) {

	if (colY == NULL) {
		positionY += distanceY;
		return;
	}

	int normalYValue = static_cast<int>(colY->normalY);
	positionY += colY->time * distanceY + normalYValue * BLOCK_PUSH_FACTOR;

	if (setPosFlag) {
		objSrc->SetPosition(positionX, positionY);
	}
	objSrc->OnCollisionWith(colY);
}

void CCollision::Process(LPINTERACTIVEOBJECT objSrc, DWORD dt, vector<LPPHYSICALOBJECT>* coObjs)
{
	if (!objSrc) return;
	vector<LPCOLLISIONEVENT> coEvents;
	LPCOLLISIONEVENT colX = NULL;
	LPCOLLISIONEVENT colY = NULL;
	coEvents.clear();
	if (objSrc->IsCollidable())
	{
		Scan(objSrc, dt, coObjs, coEvents);
	}
	else
	{
		//DebugOutObjectClassName(objSrc);
	}

	if (coEvents.size() == 0)
	{
		objSrc->OnNoCollision(dt);
	}
	else
	{
		Filter(objSrc, coEvents, colX, colY);
		float x, y, vx, vy, distanceX, distanceY;
		objSrc->GetPosition(x, y);
		objSrc->GetSpeed(vx, vy);
		distanceX = vx * dt;
		distanceY = vy * dt;

		

		if (colX != NULL && colY != NULL)
		{
			if (colY->time < colX->time)
			{
				ProcessCollisionY(objSrc, x, y, distanceY, colY, true);
				
				// Check if there is still a collision on X after Y correction
				LPCOLLISIONEVENT colX_other = NULL;
				colX->isDeleted = true;	// remove current collision event on X
				coEvents.push_back(SweptAABB(objSrc, dt, colX->obj)); // replace with a new collision event using corrected location 
				Filter(objSrc, coEvents, colX_other, colY, 1, 1, 0); // re-filter on X only


				ProcessCollisionX(objSrc, x, y, distanceX, colX_other);
			}
			else
			{
				ProcessCollisionX(objSrc, x, y, distanceX, colX, true);

				// see if after correction on X, is there still a collision on Y ? 
				LPCOLLISIONEVENT colY_other = NULL;
				colY->isDeleted = true;	// remove current collision event on Y
				coEvents.push_back(SweptAABB(objSrc, dt, colY->obj)); // replace with a new collision event using corrected location 
				Filter(objSrc, coEvents, colX, colY_other, 1, 0, 1); // re-filter on Y only

				ProcessCollisionY(objSrc, x, y, distanceY, colY_other);
			}
		}
		else
		{
			// only collision on 1 or 0 axis
			ProcessCollisionX(objSrc, x, y, distanceX, colX);
			ProcessCollisionY(objSrc, x, y, distanceY, colY);
		}
		objSrc->SetPosition(x, y);
	}

	//
	// Scan all non-blocking collisions for further collision logic
	//
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (e->isDeleted || e->obj->IsBlocking()) continue;  // blocking collisions were handled already, skip them
		//e->printInfo();
		objSrc->OnCollisionWith(e);
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

CCollision* CCollision::__instance = NULL;

CCollision* CCollision::GetInstance()
{
	if (__instance == NULL) __instance = new CCollision();
	return __instance;
}