#pragma once
#include "GameObject.h"

class CHUDObject : public CGameObject {
protected:
	float offsetX = 0;
	float offsetY = 0;
public:
	CHUDObject() {}
	void GetOffSet(float& offX, float& offY) const { offX = this->offsetX; offY = this->offsetY; }
};

typedef CHUDObject* LPHUDOBJECT;