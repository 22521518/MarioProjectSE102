#include "Mario.h"
#include "MarioState.h"
#include "FlyMarioState.h"
#include "BigMarioState.h"
#include "SmallMarioState.h"
#include "CollisionEvent.h"
#include "PhysicalObject.h"
#include "MarioAniIDs.h"
#include "Collision.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "Brick.h"
#include "CollidableWithMario.h"
#include "DestroyableObject.h"
#include "BrickSuperItem.h"
#include"SuperMushroom.h"
#include"OneUpMushroom.h"

#include "PlantEnemy.h"
#include "PlantFireBall.h"
#include "Block1Up.h"

UINT CMario::coins = 0;
ULONG CMario::scores = 0;
UINT CMario::lives = 1;

void CMario::AddCoin(int c)
{
	int remainsLives = ((CMario::coins + c) / 100) - (CMario::coins / 100);
	CMario::lives += remainsLives > 0 ? 1 : 0;
	int remainsScore = ((CMario::coins + c) / 50) - (CMario::coins / 50);
	CMario::AddScore(remainsScore * 50);

	CMario::coins += c;
}

void CMario::AddScore(int c)
{
	CMario::scores += c;
}

CMario::CMario(float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state) : CCharacter(x, y, vx, vy, ax, ay, nx, state)
{
	this->maxVx = 0.0f;
	this->isSitting = false;
	this->isOnPlatform = false;

	this->untouchable = 0;
	this->die_start = 0;
	this->untouchable_start = 0;
	this->running_start = 0;
	this->flap_start = 0;
	this->kick_start = 0;
	this->attack_start = 0;
	this->power_p_start = 0;

	this->level = MARIO_LEVEL_SMALL;
	this->stateHandler = new CSmallMarioState(this);
	this->holdingItem = nullptr;

	DebugOut(L"[DUMB-SS]Mario reborn, state_handler: ");
	DebugOutObjectClassName(stateHandler);
}
void CMario::Init(float x, float y)
{
	this->x = x, this->y = y;
	this->stateHandler = new CSmallMarioState(this);
	this->holdingItem = nullptr;
}

void CMario::OnGameReset()
{
	CMario::coins = 0;
	CMario::scores = 0;
	CMario::lives = 1;
}

boolean CMario::IsMarioDieAndReload()
{
	ULONGLONG time_now = GetTickCount64();
	return state == MARIO_STATE_DIE && die_start > 0 && time_now - die_start >= MARIO_DIE_TIME_DELAY;
}

void CMario::SetLevel(int level)	
{
	StartUntouchable();
	//if (this->level > MARIO_LEVEL_BIG) return;
	float left, top, right, bottom;
	this->GetBoundingBox(left, top, right, bottom);
	switch (level) {
	case MARIO_LEVEL_SMALL:
	{
		delete this->stateHandler;
		this->stateHandler = new CSmallMarioState(this); 
		break;
	}
	case MARIO_LEVEL_BIG:
	{
		delete this->stateHandler;
		this->stateHandler = new CBigMarioState(this);
		break;
	}
	case MARIO_LEVEL_FLY: 
	{
		delete this->stateHandler;
		this->stateHandler = new CFlyMarioState(this);
		break;
	}
	default:
		break;
	}

	float currentHeight, currentWidth;
	this->stateHandler->GetBoundingBox(currentWidth, currentHeight);
	this->y = bottom - currentHeight / 2;
	this->level = level;
}

void CMario::StartUntouchable() {
	this->untouchable = 1;
	this->untouchable_start = GetTickCount64();
}

float CMario::GetPowerP() const
{
	ULONGLONG now = GetTickCount64();

	if (power_p_start > 0 &&
		now - power_p_start < MARIO_DURATION_POWER_P)
	{
		return 7;
	}

	return powerPBar;
}

void CMario::ReleaseHoldingItem()
{
	if (!this->holdingItem) return;
	this->OnKick();
	this->holdingItem->OnMarioRelease(this);
	this->holdingItem = nullptr;
}

bool CMario::IsFlapping() const
{
	return flap_start > 1 && (GetTickCount64() - flap_start) < MARIO_FLAPPING_TIME;
}

void CMario::StartFlap()
{
	if (this->level != MARIO_LEVEL_FLY) return;
	if (CanFly() || vy > 0)
	flap_start = GetTickCount64();
	//this->SetState(MARIO_FLY_FLAPPING); handle by the property, not the state
}

void CMario::StartAttack() {
	if (this->level < MARIO_LEVEL_FLY) return;
	attack_start = GetTickCount64();
}

bool CMario::CanFly() const
{
	ULONGLONG now = GetTickCount64();
	return (power_p_start > 0 && now - power_p_start < MARIO_DURATION_POWER_P);
}

bool CMario::IsAttacking() const
{
	return attack_start > 1 && (GetTickCount64() - attack_start) < MARIO_ATTACK_FRAME_TIME + MARIO_ATTACK_CD_TIME;
}
	
#pragma region COLLIDABLE_MARIO_METHOD
void CMario::OnCollisionWithGoomba(LPGOOMBA goomba, LPCOLLISIONEVENT e)
{
	// jump on top >> kill Goomba and deflect a bit 
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!goomba->IsDeadState() || goomba->IsParaGoombaState())
		{
			vy = vy > 0 ? -MARIO_JUMP_DEFLECT_SPEED : vy - MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (untouchable == 0 && !goomba->IsDeadState()) // hit by Goomba
	{
		if (level > MARIO_LEVEL_BIG)
		{
			this->SetLevel(MARIO_LEVEL_BIG);
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_SMALL);
		}
		else
		{
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithEnemy(LPENEMY goomba, LPCOLLISIONEVENT e)
{
	// jump on top >> kill ___ and deflect a bit 
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!goomba->IsDeadState())
		{
			vy = vy > 0 ? -MARIO_JUMP_DEFLECT_SPEED : -MARIO_JUMP_DEFLECT_SPEED * 1.5f;
		}
	}
	else if (untouchable == 0 && !goomba->IsDeadState()) // hit by ???
	{
		if (level > MARIO_LEVEL_BIG)
		{
			this->SetLevel(MARIO_LEVEL_BIG);
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_SMALL);
		}
		else
		{
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::CollideBullet(LPINTERACTIVEOBJECT fire)
{
	if (this->IsOverLapping(static_cast<LPINTERACTIVEOBJECT>(fire)) && untouchable == 0) {
		if (level > MARIO_LEVEL_BIG)
		{
			this->SetLevel(MARIO_LEVEL_BIG);
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_SMALL);
		}
		else
		{
			SetState(MARIO_STATE_DIE);
		}
	}
};

void CMario::Collide1UP(LPBLOCK1UP fire)
{
	if (this->IsOverLapping(static_cast<LPINTERACTIVEOBJECT>(fire))) {
		if (this->GetLevel() == MARIO_LEVEL_SMALL && fire->GetState() == BRICK_STATE_EMPTYING && fire->out)
		{
			this->y = this->y - MARIO_SMALL_BBOX_HEIGHT;
			this->SetLevel(MARIO_LEVEL_BIG);
			this->StartUntouchable();
			fire->SetState(BRICK_STATE_EMPTY);
		}
	}
};
bool CMario::IsOverLapping(LPINTERACTIVEOBJECT a) {
	float l, t, r, b, Fl, Ft, Fr, Fb;
	this->GetBoundingBox(l, t, r, b);
	a->GetBoundingBox(Fl, Ft, Fr, Fb);
	if (l < Fr && r > Fl && t < Fb && b > Ft) return true;
	else return false;
}

void CMario::OnCollisionWithCoin(LPCOIN coin, LPCOLLISIONEVENT e) {
	CMario::AddCoin(1);
}

void CMario::OnCollisionWithSuperLeaf(LPSUPERLEAF leaf, LPCOLLISIONEVENT e)
{
	this->SetLevel(MARIO_LEVEL_FLY);
}

void CMario::OnCollisionWithSuperMushroom(LPSUPERMUSHROOM mushroom, LPCOLLISIONEVENT e)
{
	this->SetLevel(MARIO_LEVEL_BIG);
}

void CMario::OnCollisionWithOneUpMushroom(LPONEUPMUSHROOM mushroom, LPCOLLISIONEVENT e)
{
	CMario::lives++;
	CMario::AddScore(mushroom->GetScore());
}

void CMario::OnCollisionWithSuperItemBrick(LPBRICKSUPERITEM brick, LPCOLLISIONEVENT e)
{
	if (this->level > MARIO_LEVEL_SMALL)
	{
		brick->CreateSuperLeaf(e);
		return;
	}
	brick->CreateSuperMushroom(e);
}

void CMario::OnCollisionWithKoopa(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!koopa->IsShellIdle() || koopa->IsParatroopaState())
		{
			vy = vy > 0 ? -MARIO_JUMP_DEFLECT_SPEED : vy - MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (untouchable == 0 && !koopa->IsDeadState())
	{
		if (level > MARIO_LEVEL_BIG)
		{
			this->SetLevel(MARIO_LEVEL_BIG);
		}
		else if (level > MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_SMALL);
		}
		else
		{
			SetState(MARIO_STATE_DIE);
		}
	}
}

#pragma endregion

#pragma region INTERACTIVE_OBJECT_METHOD
void CMario::SetState(int state)
{
	this->stateHandler->HandleStateChange(state);
}

void CMario::OnNoCollision(DWORD dt)
{
	CCharacter::OnNoCollision(dt);
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->normalY != DirectionYAxisType::None && e->obj->IsBlocking())
	{
		vy = 0;
		isOnPlatform = (e->normalY == DirectionYAxisType::Top) ? true : isOnPlatform;
		this->flap_start = 0;
		this->power_p_start = 0;
	}

	if (e->normalX != DirectionXAxisType::None && e->obj->IsBlocking())
	{
		vx = 0;
	}

	LPDESTROYABLEOBJECT destroyableObj = dynamic_cast<LPDESTROYABLEOBJECT>(e->obj);
	if (destroyableObj && (
		(e->normalY == DirectionYAxisType::Bottom && this->GetLevel() > MARIO_LEVEL_SMALL && dynamic_cast<LPBRICK>(destroyableObj))
		|| this->IsAttacking()))
	{
		destroyableObj->OnDestroy(e);
	}

	LPCOLLIDABLEWITHMARIO obj = dynamic_cast<LPCOLLIDABLEWITHMARIO>(e->obj);
	if (obj) {
		LPHOLDABLEWITHMARIO holdableObj = dynamic_cast<LPHOLDABLEWITHMARIO>(obj);
		if (holdableObj && holdableObj->IsHoldableState() && this->IsRunning())
		{
			holdableObj->OnMarioHold(this, e);
			this->holdingItem = holdableObj;
			return;
		}

		LPDESTROYABLEOBJECT desObj = dynamic_cast<LPDESTROYABLEOBJECT>(obj);
		if (this->IsAttacking() && desObj != nullptr) {
			desObj->OnDestroy(e);
		}
		else
		{
			if (!untouchable)
				obj->OnMarioCollide(this, e);
		}
	}
}
#pragma endregion

#pragma region PHYSICAL_OBJECT_METHOD
void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxWidth = 0;
	float bboxHeight = 0;
	this->stateHandler->GetBoundingBox(bboxWidth, bboxHeight);

	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CMario::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	ULONGLONG time_now = GetTickCount64();
	if (IsFlapping()) 
	{
		if (CanFly()) {
			//DebugOut(L"I can fly!!\n");
			vy = -MARIO_FLAP_BOOST * 4;
			ay = MARIO_GRAVITY * 0.375f;
			maxVx = MARIO_WALKING_SPEED * 1.05f * static_cast<int>(nx);
		}
		else if (vy > 0)
		{
			//DebugOut(L"I dropping!!\n");
			running_start = 0;
			ay = MARIO_FALL_GRAVITY * 0.4f;
		}
		else {
			this->ay = vy > 0 ? MARIO_FALL_GRAVITY : MARIO_GRAVITY;
		}
	}
	else 
	{
		this->ay = vy > 0 ? MARIO_FALL_GRAVITY : MARIO_GRAVITY;
	}

	//DebugOutTitle(L"speed: %f, max: %f, acc: %f, dir: %d, times %llu\n", vy, maxVx, ay, IsFlapping(), die_start);
	////(time_now - running_start) % static_cast<int>(MARIO_TIME_POWER_P / 7)
	//DebugOutTitle(L"coins: %u, lives: %u, scores: %lu, die_time: %llu, power_p: %f\n", CMario::coins, CMario::lives, CMario::scores, power_p_start, powerPBar);
	DebugOutTitle(L"running: %llu, power_p: %llu ", 
		running_start > 0 ? (time_now - running_start) / 1000 : 0,
		power_p_start > 0 ? (time_now - power_p_start) / 1000 : 0);

	vy += ay * dt;
	vx += ax * dt;

	
	if (maxVx != 0 && (vx >= maxVx && static_cast<int>(nx) > 0) || (vx <= maxVx && static_cast<int>(nx) < 0)) {
		vx = maxVx;
	}

	if (abs(vx) >= MARIO_RUNNING_SPEED) {
		running_start = running_start == 0 ? time_now : running_start;
		if (time_now - running_start > MARIO_TIME_POWER_P + MARIO_DURATION_POWER_P)
			running_start = 0;
	}
	else {
		running_start = 0;
	}

	// reset untouchable timer if untouchable time has passed
	if (time_now - untouchable_start > MARIO_UNTOUCHABLE_TIME && untouchable_start > 0)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (this->holdingItem != nullptr && this->stateHandler != nullptr)
	{
		float bboxWidth = 0;
		float bboxHeight = 0;
		this->stateHandler->GetBoundingBox(bboxWidth, bboxHeight);
			
		int dir = static_cast<int>(this->nx);
		this->holdingItem->SetObjectPosision(this->x + (bboxWidth - 2.0f) * dir, this->y);
		if (!this->holdingItem->IsHoldableState())
		{

			untouchable_start = MARIO_UNTOUCHABLE_TIME - 200;
			untouchable = 1;
			int dir = static_cast<int>(this->nx);
			this->holdingItem->SetObjectPosision(this->x + (bboxWidth + 20.0f) * dir, this->y);
			//this->holdingItem->SetObjectPosision(this->x + (bboxWidth + 12.0f) * dir, this->y);
			this->ReleaseHoldingItem();
		}
	}

	if (flap_start > 1 && (time_now - flap_start) >= MARIO_FLAPPING_TIME)
	{
		flap_start = 2;
	}
	constexpr int POWERP_INCREASE_INTERVAL = static_cast<int>(MARIO_TIME_POWER_P / 7);
	constexpr int POWERP_DECREASE_INTERVAL = static_cast<int>(POWERP_INCREASE_INTERVAL * 0.6);

	// 1800 / 7 ~~ 250
	
	if(running_start > 0 && time_now - lastIncreaseTime >= POWERP_INCREASE_INTERVAL && !IsFlapping()) {
		powerPBar = min(powerPBar + 1, 7);
		lastIncreaseTime = time_now;
	}
	else if ((running_start <= 0 || 
		(power_p_start > 0 && time_now - power_p_start > MARIO_DURATION_POWER_P + MARIO_COOLDOWN_POWER_P)) &&
		time_now - lastDecreaseTime >= POWERP_DECREASE_INTERVAL) {
		lastDecreaseTime = time_now;
		powerPBar = max(powerPBar - 1, 0);
	}

	if ((!CanFly() && IsFlapping() && !isOnPlatform))
	{
		running_start = 0;
	}
}	
#pragma endregion

#pragma region GAME_OBJECT_METHOD
void CMario::Render()
{
	if (this->holdingItem)
	{
		this->holdingItem->RenderObject();
	}

	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
	{
		aniId = ID_ANI_MARIO_DIE;
	}
	else {
		aniId = this->stateHandler->GetAniId();
	}

	animations->Get(aniId)->Render(x, y);
}
#pragma endregion
