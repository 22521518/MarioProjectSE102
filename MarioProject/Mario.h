#pragma once
#include "Character.h"
#include "MarioConfig.h"
#include "MarioStateIDs.h"

class CPortal; typedef CPortal* LPPORTAL;
class CCoin; typedef CCoin* LPCOIN;
class CGoomba; typedef CGoomba* LPGOOMBA;
class CKoopa; typedef CKoopa* LPKOOPA;
class CMarioState; typedef CMarioState* LPMARIOSTATE;
class CPhysicalObject; typedef CPhysicalObject* LPPHYSICALOBJECT;
class CBlockQ; typedef CBlockQ* LPBlockQ;

struct CCollisionEvent; typedef CCollisionEvent* LPCOLLISIONEVENT;

class CMario : public CCharacter
{
	// physical state
	float maxVx;

	// mario state
	BOOLEAN isSitting;
	BOOLEAN isOnPlatform;
	int level;
	int untouchable;
	ULONGLONG untouchable_start;

	// score
	int coin = 0;
	LPMARIOSTATE stateHandler;


public:
	CMario(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = MARIO_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = -1);

	// game object method
	virtual void Render();

	// physical object method
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;
	virtual int IsBlocking() override { return (this->state != MARIO_STATE_DIE && untouchable == 0); };
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override { return 1; };
	virtual int IsCollidable() override { return (this->state != MARIO_STATE_DIE); };

	// interactive object method
	virtual void SetState(int state) override;
	virtual void OnNoCollision(DWORD dt) override;
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;

	// character object mehtod
	virtual bool IsDeadState() override { return this->state == MARIO_STATE_DIE; }

	// mario method
	void SetLevel(int level);
	int GetLevel() const { return level; };
	void StartUntouchable();
	bool IsUntouchable() const { return this->untouchable != 0; }

	// mario with collidable mario obj
	void OnCollisionWithGoomba(LPGOOMBA goomba, LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOIN coin, LPCOLLISIONEVENT e);
	//void OnCollisionWithBlockQ (LPBlockQ coin, LPCOLLISIONEVENT e) {};
	//void OnCollisionWithPortal(LPPORTAL portal, LPCOLLISIONEVENT e) {};
	void OnCollisionWithKoopa(LPKOOPA koopa, LPCOLLISIONEVENT e);

	friend class CMarioState;
	friend class CSmallMarioState;
	friend class CBigMarioState;

	friend class CCollidableWithMario;
};

typedef CMario* LPMARIO;