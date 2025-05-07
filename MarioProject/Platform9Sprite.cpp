#include "Platform9Sprite.h"

CPlatform9Sprite::CPlatform9Sprite(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end, int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end, int sprite_id_bot_begin, int sprite_id_bot_middle, int sprite_id_bot_end)
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

unordered_map<string, float> CPlatform9Sprite::GetAdditionalFieldInfo(vector<string> tokens)
{
	unordered_map<string, float> fieldInfo;
	fieldInfo["cell_width"] = (float)atof(tokens[3].c_str());
	fieldInfo["cell_height"] = (float)atof(tokens[4].c_str());

	fieldInfo["length"] = atoi(tokens[5].c_str());
	fieldInfo["height"] = atoi(tokens[6].c_str());

	fieldInfo["sprite_top_begin"] = atoi(tokens[7].c_str());
	fieldInfo["sprite_top_middle"] = atoi(tokens[8].c_str());
	fieldInfo["sprite_top_end"] = atoi(tokens[9].c_str());

	fieldInfo["sprite_mid_begin"] = atoi(tokens[10].c_str());
	fieldInfo["sprite_mid_middle"] = atoi(tokens[11].c_str());
	fieldInfo["sprite_mid_end"] = atoi(tokens[12].c_str());

	fieldInfo["sprite_bot_begin"] = atoi(tokens[13].c_str());
	fieldInfo["sprite_bot_middle"] = atoi(tokens[14].c_str());
	fieldInfo["sprite_bot_end"] = atoi(tokens[15].c_str());

	return fieldInfo;
}

void CPlatform9Sprite::Render()
{
	if (this->length <= 0 || this->height <= 0) return;
	//layer top
	float xx = x;
	float yy = y;
	this->RenderByLayer(xx, yy, this->spriteIdTopBegin, this->spriteIdTopMiddle, this->spriteIdTopEnd);

	//layer bottom
	if (this->height < 2) return;
	
	//layer mid
	yy = y + this->cellHeight;
	for (int i = 1; i < this->height - 1; i++)
	{
		xx = x;
		this->RenderByLayer(xx, yy, this->spriteIdMidBegin, this->spriteIdMidMiddle, this->spriteIdMidEnd);
		yy += this->cellHeight;
	}
	xx = x;
	this->RenderByLayer(xx, yy, this->spriteIdBotBegin, this->spriteIdBotMiddle, this->spriteIdBotEnd);
}

void CPlatform9Sprite::RenderByLayer(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd)
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

	//RenderBoundingBox();
}

void CPlatform9Sprite::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->length * this->cellWidth;
	b = t + this->height * this->cellHeight;
}


void CPlatform9Sprite::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = l;
	rect.top = r;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y - this->cellHeight / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}