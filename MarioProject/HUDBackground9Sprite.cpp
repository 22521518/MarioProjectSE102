#include "HUDBackground9Sprite.h"
#include "Sprites.h"

CHUDBackground9Sprite* CHUDBackground9Sprite::FromSingleSprite(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id, float offX, float offY)
{
	return new CHUDBackground9Sprite(x, y, length, height, cell_width, cell_height,
		sprite_id, sprite_id, sprite_id, sprite_id, sprite_id, sprite_id, sprite_id, sprite_id, sprite_id, offX, offY);
}

CHUDBackground9Sprite::CHUDBackground9Sprite(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end, int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end, int sprite_id_bot_begin, int sprite_id_bot_middle, int sprite_id_bot_end, float offX, float offY) : CHUDObject(offX, offY)
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

void CHUDBackground9Sprite::Render()
{
	if (this->length <= 0 || this->height <= 0) return;

	//row top
	float xx = x;
	float yy = y;
	this->RenderByRow(xx + +offsetY + cellWidth / 2, yy + offsetY, this->spriteIdTopBegin, this->spriteIdTopMiddle, this->spriteIdTopEnd);

	//row bottom
	if (this->height < 2) return;

	//row mid
	yy = y + this->cellHeight;
	for (int i = 1; i < this->height - 1; i++)
	{
		xx = x;
		this->RenderByRow(xx + offsetY + cellWidth / 2, yy + offsetY, this->spriteIdMidBegin, this->spriteIdMidMiddle, this->spriteIdMidEnd);
		yy += this->cellHeight;
	}
	xx = x;
	this->RenderByRow(xx + offsetY + cellWidth / 2, yy + offsetY, this->spriteIdBotBegin, this->spriteIdBotMiddle, this->spriteIdBotEnd);
}

void CHUDBackground9Sprite::RenderByRow(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) const
{
	if (length <= 0) return;

	CSprites::GetInstance()->Get(spriteIdBegin)->Draw(xx, yy);
	xx += cellWidth;

	for (int i = 1; i < length - 1; i++) {
		CSprites::GetInstance()->Get(spriteIdMiddle)->Draw(xx, yy);
		xx += cellWidth;
	}

	if (length > 1)
		CSprites::GetInstance()->Get(spriteIdEnd)->Draw(xx, yy);
}

