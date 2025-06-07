#include "SemisolidFlimsyLiftPlatform.h"
#include "Collision.h"

CSemisolidFlimsyLiftPlatform::CSemisolidFlimsyLiftPlatform(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end, int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end, int sprite_id_bot_begin, int sprite_id_bot_middle, int sprite_id_bot_end): CInteractiveObject(x, y, LIFT_PLATFORM_HORIZONTIAL_SPEED)
{
	this->length = length;
	this->height = height;

	this->cellWidth = cell_width;
	this->cellHeight = cell_height;

	this->spriteIdTopBegin = sprite_id_top_begin;
	this->spriteIdTopMiddle = sprite_id_top_middle;
	this->spriteIdTopEnd = sprite_id_top_end;

	this->spriteIdMidBegin = sprite_id_mid_begin;
	this->spriteIdMidMiddle = sprite_id_mid_middle;
	this->spriteIdMidEnd = sprite_id_mid_end;

	this->spriteIdBotBegin = sprite_id_bot_begin;
	this->spriteIdBotMiddle = sprite_id_bot_middle;
	this->spriteIdBotEnd = sprite_id_bot_end;
}

void CSemisolidFlimsyLiftPlatform::Render()
{
	if (this->length <= 0 || this->height <= 0) return;
	//layer top
	float xx = x;
	float yy = y;
	this->RenderByRow(xx, yy, this->spriteIdTopBegin, this->spriteIdTopMiddle, this->spriteIdTopEnd);

	//layer bottom
	if (this->height < 2) return;

	//layer mid
	yy = y + this->cellHeight;
	for (int i = 1; i < this->height - 1; i++)
	{
		xx = x;
		this->RenderByRow(xx, yy, this->spriteIdMidBegin, this->spriteIdMidMiddle, this->spriteIdMidEnd);
		yy += this->cellHeight;
	}
	xx = x;
	this->RenderByRow(xx, yy, this->spriteIdBotBegin, this->spriteIdBotMiddle, this->spriteIdBotEnd);
}

void CSemisolidFlimsyLiftPlatform::RenderByRow(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) const
{
	CSprites::GetInstance()->Get(spriteIdBegin)->Draw(xx, yy);
	if (length > 1)
	{
		CSprites::GetInstance()->Get(spriteIdBegin)->Draw(xx, yy);
		xx += cellWidth;
		for (int i = 1; i < length - 1; i++) {
			CSprites::GetInstance()->Get(spriteIdMiddle)->Draw(xx, yy);
			xx += cellWidth;
		}
		CSprites::GetInstance()->Get(spriteIdEnd)->Draw(xx, yy);
	}
}


void CSemisolidFlimsyLiftPlatform::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	mario_step_on_start = GetTickCount64();
}

void CSemisolidFlimsyLiftPlatform::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (x <= originX - LIFT_PLATFORM_RANGE_HORIZONTIAL_MOVEMENT || 
		x >= originX + LIFT_PLATFORM_RANGE_HORIZONTIAL_MOVEMENT) 
	{
		vx *= -1;
	}
	else {
		vx = LIFT_PLATFORM_HORIZONTIAL_SPEED;
	}

	if (mario_step_on_start > 0) {
		vy = LIFT_PLATFORM_VERTICAL_SPEED;
	}


	x += vx * dt;
	y += vy * dt;
}

void CSemisolidFlimsyLiftPlatform::OnCollisionWith(LPCOLLISIONEVENT e)
{
	LPMARIO mario = dynamic_cast<LPMARIO>(e->obj);
	if (mario || CPlayScene::GetPlayer() == e->obj)
	{
		this->OnMarioCollide(mario, e);
		return;
	}
}

void CSemisolidFlimsyLiftPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->length * this->cellWidth;
	b = t + this->height * this->cellHeight;
}
