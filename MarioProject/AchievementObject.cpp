#include "AchievementObject.h"
#include "AchievementConfig.h"
#include "Collision.h"

CAchievementObject::CAchievementObject(float x, float y) : CInteractiveObject(x, y) {
}

void CAchievementObject::Render()
{
	if (mario_touch_start > 0 && GetTickCount64() - mario_touch_start > ACHIVEMENT_TIME) return;
	CAnimations::GetInstance()->Get(ID_ANI_ACHIVEMENT_BOX_ITEM)->Render(x, y);
}

void CAchievementObject::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	if (mario_touch_start != 0) return;
	mario_touch_start = GetTickCount64();
	CMario::stageItem.push_back(4000201);
	vy = -ACHIVEMENT_VY;
}

void CAchievementObject::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	if (mario_touch_start > 0 && GetTickCount64() - mario_touch_start > ACHIVEMENT_TIME) return;
	x += vx * dt;
	y += vy * dt;
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CAchievementObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	LPMARIO mario = dynamic_cast<LPMARIO>(e->obj);
	if (mario || CPlayScene::GetPlayer() == e->obj)
	{
		this->OnMarioCollide(mario, e);
		return;
	}
}

void CAchievementObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ACHIEVEMENT_WIDTH / 2;
	t = y - ACHIEVEMENT_HEIGHT / 2;
	r = l + ACHIEVEMENT_WIDTH;
	b = t + ACHIEVEMENT_HEIGHT;
}
