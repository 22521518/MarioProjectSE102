#include "Mushroom.h"
#include "Collision.h"
#include "ItemConfig.h"
#include "Enemy.h"

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2.0f;
	top = y - MUSHROOM_BBOX_HEIGHT / 2.0f;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	if (this->state == MUSHROOM_STATE_IDLE) {
		if (this->isGrowing) {
			this->y -= MUSHROOM_GROW_SPEED * dt; // rising

			if (this->startY - this->y >= MUSHROOM_RISE_DISTANCE) {
				this->y = this->startY - MUSHROOM_RISE_DISTANCE;
				this->isGrowing = false;
				this->startTime = GetTickCount64();
			}
		}
		if (isGrowing || !this->GetActive()) return;
		if  ((GetTickCount64() - startTime > MUSHROOM_GROW_WAIT_TIME)) {

			this->SetState(MUSHROOM_STATE_MOVE);
		}
	}
	else if (this->state == MUSHROOM_STATE_MOVE) {
		this->vy += this->ay * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{
	if (this->state == MUSHROOM_STATE_MOVE) 
	{
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	}
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOutObjectClassName(e->obj);
	LPMARIO mario = dynamic_cast<LPMARIO>(e->obj);
	if (mario || CPlayScene::GetPlayer() == e->obj)
	{
		this->Delete();
		this->OnMarioCollide(mario, e);
		return;
	}

	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<LPENEMY>(e->obj)) return;
	if (this->state == MUSHROOM_STATE_IDLE) return;

	if (e->normalY != DirectionYAxisType::None)
	{	
		vy = 0; 
	}
	if (e->normalX != DirectionXAxisType::None)
	{
		int direction = static_cast<int>(nx);
		this->nx = static_cast<DirectionXAxisType>(-direction);
		vx = -vx;
	}
}

void CMushroom::SetState(int state)
{
	if (state == MUSHROOM_STATE_MOVE) 
	{
		int direction = static_cast<int>(nx);
		this->vx = MUSHROOM_SPPED * direction;
		this->state = state;
	}
}

void CMushroom::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	this->Delete();
}
