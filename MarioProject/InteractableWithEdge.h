#pragma once
#include <windows.h>

// interface for object that interact on the edge
class CInteractableWithEdge {
public:
	virtual void OnEdgeBehavior(DWORD dt) = 0;
	virtual void GetObjectBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual DirectionXAxisType GetObjectCurrentDirectionX() = 0;
};

typedef CInteractableWithEdge* LPINTERACTABLEWITHEDGE;
