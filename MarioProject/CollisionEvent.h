#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

#include "DirectionType.h"
#include "InteractiveObject.h"

using namespace std;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

struct CCollisionEvent
{
	LPPHYSICALOBJECT src_obj;		// source object : the object from which to calculate collision
	LPPHYSICALOBJECT obj;			// the target object

	float time;
	DirectionXAxisType normalX; // duong phap cua vector phap tuyen
	DirectionYAxisType normalY; // duong phap cua vector phap tuyen

	float distanceX, distanceY;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;

	CCollisionEvent(float t, DirectionXAxisType nx = DirectionXAxisType::None, DirectionYAxisType ny = DirectionYAxisType::None,
		float dx = 0, float dy = 0,
		LPPHYSICALOBJECT obj = NULL, LPPHYSICALOBJECT src_obj = NULL);
	int WasCollided();
	static bool compare(CCollisionEvent*& a, CCollisionEvent*& b);
	void printInfo();
};