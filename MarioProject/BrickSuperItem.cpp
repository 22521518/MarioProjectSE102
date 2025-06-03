#include "BrickSuperItem.h"
#include "SuperLeaf.h"
#include "SuperMushroom.h"
#include "CollisionEvent.h"
#include "BrickConfig.h"

unordered_map<string, float> CBrickSuperItem::GetAdditionalFieldInfo(vector<string> tokens)
{
	unordered_map<string, float> fieldInfo;

	return fieldInfo;
}

void CBrickSuperItem::CreateSuperLeaf(LPCOLLISIONEVENT e)
{
	float targetX, targetY;
	e->obj->GetPosition(targetX, targetY);
	DirectionXAxisType directionX = targetX > this->x ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	items.push_back(new CSuperLeaf(this->x, this->y - BRICK_BBOX_HEIGHT, directionX));
}

void CBrickSuperItem::CreateSuperMushroom(LPCOLLISIONEVENT e)
{
	float targetX, targetY;
	e->obj->GetPosition(targetX, targetY);
	DirectionXAxisType directionX = targetX > this->x ?
		DirectionXAxisType::Left : DirectionXAxisType::Right;
	items.push_back(new CSuperMushroom(this->x, this->y, directionX));
}

void CBrickSuperItem::Render()
{
	if (!this->onBounce) CBrickItem::Render();
	int aniId = state == BRICK_STATE_ACTIVE ?
		aniIdActive : aniIdEmpty;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBrickSuperItem::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	this->onBounce = (this->y < this->startY);
	CBrickItem::Update(dt, coObjects);
}

void CBrickSuperItem::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	if (!this->IsActive()) return;
	if (e->normalY == DirectionYAxisType::Bottom)
	{
		this->Bouncing();
		mario->OnCollisionWithSuperItemBrick(this, e);
		CBrickItem::OnMarioCollide(mario, e);
	}
}
 
void CBrickSuperItem::OnDestroy(LPCOLLISIONEVENT e)
{
	if (!this->IsActive()) return;
	mario->OnCollisionWithSuperItemBrick(this, e);
	CBrickItem::OnMarioCollide(mario, e);
}

void CBrickSuperItem::Bouncing()
{
	if (!this->IsActive()) return;

	onBounce = true;
	this->vy = -BRICK_JUMP_JUMP_DEFLECT_SPEED;
	this->ay = BRICK_GRAVITY;
}
