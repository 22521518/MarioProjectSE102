#include "Platform.h"

CPlatform::CPlatform(float x, float y, float cell_width, float cell_height, int length, int sprite_id_begin, int sprite_id_middle, int sprite_id_end)
	: CStaticObject(x, y)
{
	this->length = length;
	this->cellWidth = cell_width;
	this->cellHeight = cell_height;
	this->spriteIdBegin = sprite_id_begin;
	this->spriteIdMiddle = sprite_id_middle;
	this->spriteIdEnd = sprite_id_end;
}

// for parsing txt file
unordered_map<string, float> CPlatform::GetAdditionalFieldInfo(vector<string> tokens)
{
	unordered_map<string, float> fieldInfo;
	fieldInfo["cell_width"] = static_cast<float>(atof(tokens[3].c_str()));
	fieldInfo["cell_height"] = static_cast<float>(atof(tokens[4].c_str()));
	fieldInfo["length"] = static_cast<float>(atof(tokens[5].c_str()));
	fieldInfo["sprite_begin"] = static_cast<float>(atof(tokens[6].c_str()));
	fieldInfo["sprite_middle"] = static_cast<float>(atof(tokens[7].c_str()));
	fieldInfo["sprite_end"] = static_cast<float>(atof(tokens[8].c_str()));
	
	return fieldInfo;
}

void CPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect{};

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2.0f + rect.right / 2.0f;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPlatform::Render()
{
	if (this->length <= 0) return;
	float xx = x;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(xx, y);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(xx, y);
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdEnd)->Draw(xx, y);

}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight;
}

int CPlatform::IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny)
{
	return nx == DirectionXAxisType::None && ny == DirectionYAxisType::Top;
}