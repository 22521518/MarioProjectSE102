#include "Character.h"
#include "Collision.h"

void CCharacter::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	//return;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCharacter::OnNoCollision(DWORD dt)
{
	float x, y;
	this->GetPosition(x, y);
	this->SetPosition(x + vx * dt, y + vy * dt);
}