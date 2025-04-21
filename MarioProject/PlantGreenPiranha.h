#pragma once
#include "PlantEnemy.h"
#include "CollidableWithMario.h"
#include "PlantEnemyConfig.h"
#include "GameObject.h"

class CPlantGreenPiranha :
	public CPlantEnemy, public CCollidableWithMario
{
public:
	CPlantGreenPiranha(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CPlantEnemy(mario, x, y, vx, vy, ax, ay, nx, state) {};

	// game object method
	virtual void Render() {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_PLANT_GP)->Render(x, y);
		//RenderBoundingBox()
	};
}

typedef CPlantGreenPiranha* LPPlantGP;