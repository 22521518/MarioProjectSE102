#include "Character.h"
#include "Collision.h"

void CCharacter::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	//return;
	vy += ay * dt;
	vx += ax * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCharacter::OnNoCollision(DWORD dt)
{
	this->x += this->vx * dt;
	this->y += this->vy * dt;
}