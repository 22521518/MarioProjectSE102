#include "PhysicalObject.h"

void CPhysicalObject::GetBoundingBox(RECT& rect)
{
	float left, top, right, bottom;
	this->GetBoundingBox(left, top, right, bottom);
	rect.left = (LONG)left;
	rect.top = (LONG)top;
	rect.right = (LONG)right;
	rect.bottom = (LONG)bottom;
}

void CPhysicalObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	CGame::GetInstance()->Draw(x - camX, y - camY, bbox, &rect, BBOX_ALPHA);
	
}
