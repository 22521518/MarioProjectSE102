#include "GameBackground9Sprite.h"
#include "Sprites.h"

CGameBackground9Sprite::CGameBackground9Sprite(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end, int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end, int sprite_id_bot_begin, int sprite_id_bot_middle, int sprite_id_bot_end)
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

unordered_map<string, float> CGameBackground9Sprite::GetAdditionalFieldInfo(vector<string> tokens)
{
	unordered_map<string, float> fieldInfo;
	fieldInfo["cell_width"] = static_cast<float>(atof(tokens[3].c_str()));
	fieldInfo["cell_height"] = static_cast<float>(atof(tokens[4].c_str()));

	fieldInfo["length"] = static_cast<float>(atof(tokens[5].c_str()));
	fieldInfo["height"] = static_cast<float>(atof(tokens[6].c_str()));

	fieldInfo["sprite_top_begin"] = static_cast<float>(atof(tokens[7].c_str()));
	fieldInfo["sprite_top_middle"] = static_cast<float>(atof(tokens[8].c_str()));
	fieldInfo["sprite_top_end"] = static_cast<float>(atof(tokens[9].c_str()));

	fieldInfo["sprite_mid_begin"] = static_cast<float>(atof(tokens[10].c_str()));
	fieldInfo["sprite_mid_middle"] = static_cast<float>(atof(tokens[11].c_str()));
	fieldInfo["sprite_mid_end"] = static_cast<float>(atof(tokens[12].c_str()));

	fieldInfo["sprite_bot_begin"] = static_cast<float>(atof(tokens[13].c_str()));
	fieldInfo["sprite_bot_middle"] = static_cast<float>(atof(tokens[14].c_str()));
	fieldInfo["sprite_bot_end"] = static_cast<float>(atof(tokens[15].c_str()));

	return fieldInfo;
}


void CGameBackground9Sprite::Render()
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

void CGameBackground9Sprite::RenderByRow(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) const
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
