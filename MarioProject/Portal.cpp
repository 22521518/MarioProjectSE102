#include "Portal.h"
#include "PortSpriteIDs.h"
#include "PortConfig.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id, int isPipe, bool isReturnToExist, int px, int py)
	: isPipePort(isPipe), isReturnToExisting(isReturnToExist), px(px), py(py)
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

bool CPortal::TimeToMove() const
{
	ULONGLONG now = GetTickCount64();
	return time_start > 0 && (!isPipePort || (now - time_start) > PORT_MOVE_TIME);
}

#pragma region COLLIDABLE_MARIO_METHOD
void CPortal::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	if (time_start == 0) 
	{
		time_start = GetTickCount64();
		mario->StartPipeMove();
	};

	int level = mario->GetLevel();
	if (level == MARIO_LEVEL_SMALL) animation_id = ID_SPRITE_SMALL_MARIO_MOVEMENT;
	else if (level == MARIO_LEVEL_BIG) animation_id = ID_SPRITE_BIG_MARIO_MOVEMENT;
	else if (level == MARIO_LEVEL_FLY) animation_id = ID_SPRITE_FLY_MARIO_MOVEMENT;
	//mario->OnCollisionWithPortal(this, e);
	float f, t, r, b;
	mario->GetBoundingBox(f, t, r, b);
	animation_height = b - t, animation_width = r - f;
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

void CPortal::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	if (TimeToMove() && scene_id != PORT_NULL_SCENE_ID)
	{
		if (isReturnToExisting) CGame::GetInstance()->InitiateSwitchSceneFromBonus(scene_id, px, py, isPipePort);
		else CGame::GetInstance()->InitiateSwitchScene(scene_id, isPipePort);
		time_start = 0;
	}
}

void CPortal::Render()
{
	if (isPipePort && !TimeToMove() && time_start > 0) 
	{
		ULONGLONG elapsed = GetTickCount64() - time_start;
		int currentIndex = (int)((elapsed * PORT_FRAME_NUMS) / PORT_MOVE_TIME);
		if (currentIndex >= PORT_FRAME_NUMS) currentIndex = PORT_FRAME_NUMS - 1; 

		float xx = x;
		float yy = y;

		float offset = isPipePort * (currentIndex * animation_height / (float)PORT_FRAME_NUMS - animation_height / 2.0f);
		yy += offset;

		CSprites::GetInstance()->Get(animation_id)->Draw(xx, yy);

	}
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}
#pragma endregion