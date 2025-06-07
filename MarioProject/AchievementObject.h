#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"

class CAchievementObject :
	public CInteractiveObject, public CCollidableWithMario {
public:
	CAchievementObject(float x = 0, float y = 0);
};