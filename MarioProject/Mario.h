#pragma once
#include "Character.h"
#include "MarioConfig.h"
#include "MarioStateIDs.h"
#include "HoldableWithMario.h"

// object class
class CPortal; typedef CPortal* LPPORTAL;
class CCoin; typedef CCoin* LPCOIN;
class CGoomba; typedef CGoomba* LPGOOMBA;
class CKoopa; typedef CKoopa* LPKOOPA;
class CMarioState; typedef CMarioState* LPMARIOSTATE;
class CPhysicalObject; typedef CPhysicalObject* LPPHYSICALOBJECT;
class CBlockQ; typedef CBlockQ* LPBLOCKQ;
class CPlantEnemy; typedef CPlantEnemy* LPPLANTENEMY;
class CPlantFireBall; typedef CPlantFireBall* LPPLANTFIREBALL;
class CBlock1Up; typedef CBlock1Up* LPBLOCK1UP;
class CSuperMushroom; typedef CSuperMushroom* LPSUPERMUSHROOM;
class COneUpMushroom; typedef COneUpMushroom* LPONEUPMUSHROOM;
class CSuperLeaf; typedef CSuperLeaf* LPSUPERLEAF;
class CBrickSuperItem; typedef CBrickSuperItem* LPBRICKSUPERITEM;

struct CCollisionEvent; typedef CCollisionEvent* LPCOLLISIONEVENT;

class CMario : public CCharacter
{
	LPHOLDABLEWITHMARIO holdingItem = nullptr;
	bool isRunning = false;
	// physical state
	float maxVx;

	// mario state
	BOOLEAN isSitting;
	BOOLEAN isOnPlatform;
	int level;
	int untouchable;
	ULONGLONG flap_start;
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;

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
	bool IsRunning() const { return this->isRunning; }
	void SetRunning(bool run) { this->isRunning = run; }
	void SetLevel(int level);
	int GetLevel() const { return level; };
	void StartUntouchable();
	bool IsUntouchable() const { return this->untouchable != 0; }
	
	// release item with LPHOLDABLEWITHMARIO
	void ReleaseHoldingItem();
	virtual void OnKick() { this->kick_start = GetTickCount64(); };

	// fly mario method
	bool IsFlapping() const {
		return flap_start > 0 && (GetTickCount64() - flap_start) < MARIO_FLAPPING_TIME;
	}
	void StartFlap();

	// mario with collidable mario obj
	void OnCollisionWithGoomba(LPGOOMBA goomba, LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOIN coin, LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPSUPERLEAF leaf, LPCOLLISIONEVENT e);
	void OnCollisionWithSuperMushroom(LPSUPERMUSHROOM mushroom, LPCOLLISIONEVENT e);
	void OnCollisionWithOneUpMushroom(LPONEUPMUSHROOM mushroom, LPCOLLISIONEVENT e);
	void OnCollisionWithSuperItemBrick(LPBRICKSUPERITEM brick, LPCOLLISIONEVENT e);

	//void OnCollisionWithBlockQ (LPBlockQ coin, LPCOLLISIONEVENT e) {};
	//void OnCollisionWithPortal(LPPORTAL portal, LPCOLLISIONEVENT e) {};
	void OnCollisionWithPlant(LPPLANTENEMY plant, LPCOLLISIONEVENT e);
	void CollideFireBall(LPPLANTFIREBALL fire);
	void Collide1UP(LPBLOCK1UP fire);
	void OnCollisionWithKoopa(LPKOOPA koopa, LPCOLLISIONEVENT e);
	bool IsOverLapping(LPINTERACTIVEOBJECT a);

	friend class CMarioState;
	friend class CSmallMarioState;
	friend class CBigMarioState;
	friend class CFlyMarioState;

	friend class CCollidableWithMario;
};

typedef CMario* LPMARIO;