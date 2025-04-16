#pragma once
#include "Character.h"
#include "PlantEnemyConfig.h"
#include "CollidableWithMario.h"

class CPlantEnemy :
	public CCharacter, public CCollidableWithMario
{

public:
	CPlantEnemy(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0, DirectionXAxisType nx = DirectionXAxisType::Left, int state = PLANT_STATE_HIDE)
		: CCharacter(x, y, vx, vy, ax, ay, nx, state)
	{
		SetState(PLANT_STATE_HIDE);
	};

	// game object method
	/*virtual void Render()
	//{
		//int aniId = ;
		//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		//RenderBoundingBox();
	//};*/

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override
	{
		float boxHeight;
		switch (state)
		{
		case PLANT_STATE_HIDE:
			boxHeight = 0;
			break;
		case PLANT_STATE_UP:
			boxHeight = PLANT_BBOX_HEIGHT;
			break;
		default:
			boxHeight = PLANT_BBOX_HEIGHT / 2; //Tạm thời để vậy
		}
		float boxWidth = PLANT_BBOX_WIDTH;
		left = x - boxWidth / 2;
		top = y - boxHeight / 2;
		right = left + boxWidth;
		bottom = top + boxHeight;
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	virtual void SetState(int state) override
	{
		/*switch (state)
		{
			//
		}*/
		CInteractiveObject::SetState(state);
	};
	//virtual void OnNoCollision(DWORD dt) override;
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;

	// collidable with mario interface
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override
	{
		// die?
	};

};

typedef CPlantEnemy* LPPlantEnemy;