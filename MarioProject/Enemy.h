#pragma once
#include "Character.h"

class CEnemy : public CCharacter {
public:
	CEnemy(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1)
		: CCharacter(x, y, vx, vy, ax, ay, nx, state) {}

	int IsCollidable() override { return !this->IsDeleted(); };
};

typedef CEnemy* LPENEMY;