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

	this->level = MARIO_LEVEL_SMALL;
	this->untouchable = 0;
	this->untouchable_start = -1;
	this->flap_start = -1;
	this->kick_start = -1;

	this->coin = 0;
	this->stateHandler = new CSmallMarioState();
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
		this->stateHandler = new CSmallMarioState(); 
		break;
	}
	case MARIO_LEVEL_BIG:
	{
		delete this->stateHandler;
		this->stateHandler = new CBigMarioState();
		break;
	}
	case MARIO_LEVEL_FLY: 
	{
		delete this->stateHandler;
		this->stateHandler = new CFlyMarioState();
		break;
	}
	default:
		break;
	}

	float currentHeight, currentWidth;
	this->stateHandler->GetBoundingBox(this, currentWidth, currentHeight);
	this->y = bottom - currentHeight / 2;
	this->level = level;
}

void CMario::StartUntouchable() {
	this->untouchable = 1;
	this->untouchable_start = GetTickCount64();
}

void CMario::ReleaseHoldingItem()
{
	if (!this->holdingItem) return;
	this->OnKick();
	this->holdingItem->OnMarioRelease(this);
	this->holdingItem = nullptr;
}

void CMario::StartFlap()
{
	if (this->level != MARIO_LEVEL_FLY) return;
	flap_start = GetTickCount64();
	this->SetState(MARIO_FLY_FLAPPING);
}

#pragma region COLLIDABLE_MARIO_METHOD
void CMario::OnCollisionWithGoomba(LPGOOMBA goomba, LPCOLLISIONEVENT e)
{
	// jump on top >> kill Goomba and deflect a bit 
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!goomba->IsDeadState() || goomba->IsParaGoombaState())
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
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
			vy = -MARIO_JUMP_DEFLECT_SPEED;
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
			vy = -MARIO_JUMP_DEFLECT_SPEED;
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
	this->stateHandler->HandleStateChange(this, state);
}

void CMario::OnNoCollision(DWORD dt)
{
	CCharacter::OnNoCollision(dt);
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	LPDESTROYABLEOBJECT destroyableObj = dynamic_cast<LPDESTROYABLEOBJECT>(e->obj);
	if (destroyableObj && e->normalY == DirectionYAxisType::Bottom && this->GetLevel() > MARIO_LEVEL_SMALL && dynamic_cast<LPBRICK>(destroyableObj))
	{
		destroyableObj->OnDestroy(e);
	}

	if (e->normalY != DirectionYAxisType::None && e->obj->IsBlocking())
	{
		vy = 0;
		isOnPlatform = (e->normalY == DirectionYAxisType::Top) ? true : isOnPlatform;
		this->flap_start = -1;
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
		obj->OnMarioCollide(this, e);
	}
}
#pragma endregion

#pragma region PHYSICAL_OBJECT_METHOD
void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxWidth = 0;
	float bboxHeight = 0;
	this->stateHandler->GetBoundingBox(this, bboxWidth, bboxHeight);

	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CMario::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	this->ax = vy > 0 ? MARIO_FALL_GRAVITY : MARIO_GRAVITY;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
	CCharacter::Update(dt, coObjects);

	if (this->holdingItem)
	{
		float bboxWidth = 0;
		float bboxHeight = 0;
		this->stateHandler->GetBoundingBox(this, bboxWidth, bboxHeight);

		int dir = static_cast<int>(this->nx);
		this->holdingItem->SetObjectPosision(this->x + (bboxWidth - 2.0f) * dir, this->y);
		if (!this->holdingItem->IsHoldableState())
		{
			this->ReleaseHoldingItem();
		}
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
		aniId = this->stateHandler->GetAniId(this);
	}

	animations->Get(aniId)->Render(x, y);

	DebugOutTitle(L"Coins: %d", coin);
}
#pragma endregion
