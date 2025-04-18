#include "Mario.h"
#include "MarioState.h"
#include "BigMarioState.h"
#include "SmallMarioState.h"
#include "CollisionEvent.h"
#include "PhysicalObject.h"
#include "MarioAniIDs.h"
#include "Collision.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "CollidableWithMario.h"

CMario::CMario(float x, float y, float vx, float vy, float ax, float ay, DirectionXAxisType nx, int state) : CCharacter(x, y, vx, vy, ax, ay, nx, state)
{
	this->maxVx = 0.0f;
	this->isSitting = false;
	this->isOnPlatform = false;

	this->level = MARIO_LEVEL_SMALL;
	this->untouchable = 0;
	this->untouchable_start = -1;

	this->coin = 0;
	this->stateHandler = new CSmallMarioState();
};

void CMario::SetLevel(int level)
{
	if (level == MARIO_LEVEL_SMALL)
	{
		this->stateHandler = new CSmallMarioState();
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else
	{
		this->stateHandler = new CBigMarioState();
	}
	this->level = level;
}

void CMario::StartUntouchable() {
	this->untouchable = 1;
	this->untouchable_start = GetTickCount64();
}

#pragma region COLLIDABLE_MARIO_METHOD
void CMario::OnCollisionWithGoomba(LPGOOMBA goomba, LPCOLLISIONEVENT e)
{
	// jump on top >> kill Goomba and deflect a bit 
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!goomba->IsDeadState())
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (untouchable == 0 && !goomba->IsDeadState()) // hit by Goomba
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_SMALL);
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOIN coin, LPCOLLISIONEVENT e) { coin++; }

void CMario::OnCollisionWithKoopa(LPKOOPA koopa, LPCOLLISIONEVENT e)
{
	
	if (e->normalY == DirectionYAxisType::Top)
	{
		if (!koopa->IsShellState() || koopa->IsParatroopaState())
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (untouchable == 0 && !koopa->IsDeadState())
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_SMALL);
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			//SetState(MARIO_STATE_DIE);
		}
	}
}

#pragma endregion

#pragma region INTERACTIVE_OBJECT_METHOD
void CMario::SetState(int state)
{
	if (this->IsDeadState()) return;
	this->stateHandler->HandleStateChange(this, state);
	this->state = state;
	CInteractiveObject::SetState(state);
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

	}
	else if (e->normalX != DirectionXAxisType::None && e->obj->IsBlocking())
	{
		vx = 0;
	}

	// replace the if else statement
	LPCOLLIDABLEWITHMARIO obj = dynamic_cast<LPCOLLIDABLEWITHMARIO>(e->obj);
	if (obj) {
		obj->OnMarioCollide(this, e);
	}
}
#pragma endregion

#pragma region PHYSICAL_OBJECT_METHOD
void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float bboxWidth = 0;
	float bboxHeight = 0;
	if (this->level == MARIO_LEVEL_BIG) 
	{
		if (this->isSitting) 
		{
			bboxHeight = MARIO_BIG_SITTING_BBOX_HEIGHT;
			bboxWidth = MARIO_BIG_SITTING_BBOX_WIDTH;
		}
		else 
		{
			bboxHeight = MARIO_BIG_BBOX_HEIGHT;
			bboxWidth = MARIO_BIG_BBOX_WIDTH;
		}
	}
	else if (MARIO_LEVEL_SMALL)
	{
		bboxHeight = MARIO_SMALL_BBOX_HEIGHT;
		bboxWidth = MARIO_SMALL_BBOX_WIDTH;
	}

	left = x - bboxWidth / 2;
	top = y - bboxHeight / 2;
	right = left + bboxWidth;
	bottom = top + bboxHeight;
}

void CMario::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	//vy += ay * dt;
	//vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	CCharacter::Update(dt, coObjects);
}
#pragma endregion

#pragma region GAME_OBJECT_METHOD
void CMario::Render()
{
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

	RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}
#pragma endregion
