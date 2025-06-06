#include "BrickItem.h"
#include "Mushroom.h"

void CBrickItem::Render()
{
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->IsDeleted()) continue;
		items[i]->Render();
	}
}

void CBrickItem::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	this->vy += this->ay * dt;
	this->vx += this->ax * dt;
	this->x += this->vx * dt;
	this->y += this->vy * dt;

	if (this->y >= this->startY)
	{
		this->y = this->startY;
		this->vy = this->ay = 0;
		for (int i = 0; i < items.size(); i++) {
			LPMUSHROOM mushroom = dynamic_cast<LPMUSHROOM>(items[i]);
			if (mushroom && !mushroom->GetActive())
			{
				mushroom->Activate();
			}
		}
	}

	for (int i = 0; i < items.size(); i++) {
		if (items[i]->IsDeleted()) continue;
		items[i]->Update(dt, coObjects);
	}
}

void CBrickItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_BBOX_WIDTH / 2.0f;
	top = y - BRICK_BBOX_HEIGHT / 2.0f;

	right = left + BRICK_BBOX_WIDTH;
	bottom = top + BRICK_BBOX_HEIGHT;
}

void CBrickItem::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	if (!this->IsActive()) return;
	if (numberOfCollision <= 1) 
	{
		this->SetState(BRICK_STATE_INACTIVE);
		return;
	}
	this->numberOfCollision--;
}

void CBrickItem::OnDestroy(LPCOLLISIONEVENT e)
{
	if (!this->IsActive()) return;
	this->SetState(BRICK_STATE_INACTIVE);
}


void CBrickItem::PurgeDeletedItems() {
	vector<LPITEM>::iterator it;
	for (it = this->items.begin(); it != this->items.end(); it++) {
		LPITEM currentObj = *it;
		if (currentObj->IsDeleted()) {
			delete currentObj;
			*it = nullptr;
		}
	}

	this->items.erase(remove_if(
		this->items.begin(), this->items.end(), CBrickItem::IsItemsDeleted),
		this->items.end());
}