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

#include "PlantEnemy.h"
#include "PlantFireBall.h"
#include "Block1Up.h"

CMario::CMario(float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state) : CCharacter(x, y, vx, vy, ax, ay, nx, state)
{
	this->maxVx = 0.0f;
	this->isSitting = false;
	this->isOnPlatform = false;

	this->untouchable = 0;
	this->running_start = 0;
	this->untouchable_start = 0;
	this->flap_start = 0;
	this->kick_start = 0;
	this->attack_start = 0;

	this->coin = 0;
	this->level = MARIO_LEVEL_SMALL;
	this->stateHandler = new CSmallMarioState(this);
};

void CMario::SetLevel(int level)	
{
	StartUntouchable();
	if (this->level > MARIO_LEVEL_BIG) return;
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
	return 0.0f;
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
	flap_start = GetTickCount64();
	//this->SetState(MARIO_FLY_FLAPPING); handle by the property, not the state
}

void CMario::StartAttack() {
	if (this->level < MARIO_LEVEL_FLY) return;
	attack_start = GetTickCount64();
}

bool CMario::CanFly() const
{
	//return vx >= MARIO_SPRINTNIG_SPEED || (running_start > 0 && GetTickCount64() - running_start > MARIO_TIME_POWER_P + MARIO_DURATION_POWER_P);
	return (power_p_start > 0 && GetTickCount64() - power_p_start < MARIO_DURATION_POWER_P);
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
void CMario::OnCollisionWithPlant(LPPLANTENEMY plant, LPCOLLISIONEVENT e)
{
	// jump on top >> kill ___ and deflect a bit 
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!plant->IsDeadState())
		{
			vy = vy > 0 ? -MARIO_JUMP_DEFLECT_SPEED : vy - MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (untouchable == 0 && !plant->IsDeadState()) // hit by ___
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
void CMario::CollideFireBall(LPPLANTFIREBALL fire)
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
	coin++;
	//DebugOut(L"I GOT MORE COIN! \n");
	if (this->coin >= 100)
		return;
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
	this->SetLevel(MARIO_LEVEL_FLY);
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
	LPDESTROYABLEOBJECT destroyableObj = dynamic_cast<LPDESTROYABLEOBJECT>(e->obj);
	if (destroyableObj && (
		(e->normalY == DirectionYAxisType::Bottom && this->GetLevel() > MARIO_LEVEL_SMALL && dynamic_cast<LPBRICK>(destroyableObj)) 
			|| this->IsAttacking()))
	{
		destroyableObj->OnDestroy(e);
	}

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

	DebugOutTitle(L"speed: %f, max: %f, acc: %f, dir: %d, times %llu\n", vy, maxVx, ay, IsFlapping(), running_start);
	vy += ay * dt;
	vx += ax * dt;

	
	if (maxVx != 0 && (vx >= maxVx && static_cast<int>(nx) > 0) || (vx <= maxVx && static_cast<int>(nx) < 0)) {
		vx = maxVx;
	}

	if (abs(vx) >= MARIO_RUNNING_SPEED) {
		running_start = running_start == 0 ? GetTickCount64() : running_start;
		if (GetTickCount64() - running_start > MARIO_TIME_POWER_P + MARIO_DURATION_POWER_P)
			running_start = 0;
	}
	else {
		running_start = 0;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
	//CCharacter::Update(dt, coObjects);

	if (this->holdingItem)
	{
		float bboxWidth = 0;
		float bboxHeight = 0;
		this->stateHandler->GetBoundingBox(bboxWidth, bboxHeight);

		int dir = static_cast<int>(this->nx);
		this->holdingItem->SetObjectPosision(this->x + (bboxWidth - 2.0f) * dir, this->y);
		if (!this->holdingItem->IsHoldableState())
		{
			this->ReleaseHoldingItem();
		}
	}

	if (flap_start > 1 && (GetTickCount64() - flap_start) >= MARIO_FLAPPING_TIME)
	{
		flap_start = 2;
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
