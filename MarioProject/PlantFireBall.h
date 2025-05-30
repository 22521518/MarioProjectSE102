#pragma once
#include "InteractiveObject.h"
#include "CollidableWithMario.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "PlantEnemyConfig.h"

class CPlantFireBall : public CInteractiveObject, public CCollidableWithMario {
protected:
	LPGAMEOBJECT mario;
public:
	CPlantFireBall(LPGAMEOBJECT mario, float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = 0,
		DirectionXAxisType nx = DirectionXAxisType::Left)
		: CInteractiveObject(x, y, vx, vy, ax, ay, nx) {
		this->mario = mario;
	}
	// game object method
	virtual void Render() override {
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_PLANT_FIREBALL)->Render(x, y);
	};
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
	{
		if (mario->IsUntouchable() == 0 ) // hit FIRE BALL!
		{
			if (mario->GetLevel() > MARIO_LEVEL_SMALL)
			{
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				mario->SetState(MARIO_STATE_DIE);
			}
		}
	};
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override
	{
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = x - PLANT_FIREBALL_WIDTH / 2;
		t = y - PLANT_FIREBALL_HEIGHT / 2;
		r = l + PLANT_FIREBALL_WIDTH;
		b = t + PLANT_FIREBALL_HEIGHT;
	};

	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsBlocking() override { return 0; };
	virtual int IsCollidable() override { return 1; };

	// interactive object method
	virtual void OnNoCollision(DWORD dt) override
	{
		this->vy += this->ay * dt;
		this->vx += this->ax * dt;
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<LPINTERACTIVEOBJECT>(e->obj)) return;
		if (e->normalY != DirectionYAxisType::Bottom)
		{
			vy = 0;
		}
		else
		{
			vy = 0;
		}
	};
	virtual void SetState(int state)
	{
		CInteractiveObject::SetState(state);
	};
	void WhereToShoot(LPPLANTENEMY plant) {
		float Mx, My, Px, Py;
		plant->GetPosition(Px, Py);
		mario->GetPosition(Mx, My);
		float GOx = Mx - Px, GOy = Py - My;
		float rate = GOx / GOy;
		float BY = sqrt(powf(FIREBALL_SPEED, (float)2) / (powf(rate, (float)2) + 1));
		float BX = BY * rate;
		if (Py <= My)this->SetSpeed(-BX, BY);
		else if (Py > My)this->SetSpeed(BX, -BY);
	};
	float Distant(LPPLANTENEMY plant) {
		float Px, Py;
		plant->GetPosition(Px, Py);
		return sqrt(powf((x - Px), (float)2) + powf((Py - y), (float)2));
	};
};
typedef CPlantFireBall* LPPLANTFIREBALL;