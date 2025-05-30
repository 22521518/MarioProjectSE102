#include "Portal.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r - l;
	height = b - t;
}

// for parsing txt file
unordered_map<string, float> CPortal::GetAdditionalFieldInfo(vector<string> tokens)
{
	unordered_map<string, float> fieldInfo;
	fieldInfo["r"] = static_cast<float>(atof(tokens[3].c_str()));
	fieldInfo["b"] = static_cast<float>(atof(tokens[4].c_str()));
	fieldInfo["scene_id"] = static_cast<float>(atof(tokens[5].c_str()));

	return fieldInfo;
}

#pragma region COLLIDABLE_MARIO_METHOD
void CPortal::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	CGame::GetInstance()->InitiateSwitchScene(this->GetSceneId());
	//mario->OnCollisionWithPortal(this, e);
}
#pragma endregion

#pragma region PHYSICAL_OBJECT_METHOD
void CPortal::RenderBoundingBox()
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

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}
#pragma endregion