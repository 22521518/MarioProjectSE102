#include "DestroyableBrick.h"
#include "BrickIDs.h"
#include "BreakBrickEffect.h"

void CDestroyableBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!this->isDestroy) {
		animations->Get(ID_ANI_DESTROYABLE_BRICK)->Render(x, y);
		return;
	}

	if (GetTickCount64() - this->timeDestroy > 50000) {
		this->timeDestroy = -1;
		for (int i = 0; i < pieces.size(); i++)
		{
			this->pieces[i]->Delete();
		}
		this->pieces.clear();
		this->Delete();
		return;
	}

	for (int i = 0; i < pieces.size(); i++)
	{
		this->pieces[i]->Render();
	}

}

void CDestroyableBrick::Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		this->pieces[i]->Update(dt, coObjects);
	}
}

void CDestroyableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDestroy) {
		CBrick::GetBoundingBox(left, top, right, bottom);
		return;
	}

	left = top = right = bottom = 0;
}

void CDestroyableBrick::OnDestroy(LPCOLLISIONEVENT e)
{
	if (this->isDestroy) return;
	float left, top, right, bottom;
	this->GetBoundingBox(left, top, right, bottom);

	// Initial upward and sideways speed
	float speedX = 0.075f;
	float speedY = 0.35f;   // Positive speed upward

	// Gravity effect (pulls pieces downward)
	float accelerationX = speedX / 1000.0f;         // No horizontal acceleration
	float accelerationY = 0.001f;        // Gravity downward

	this->pieces.push_back(new CBreakBrickEffect(left, top, -speedX, -speedY, accelerationX, accelerationY));
	this->pieces.push_back(new CBreakBrickEffect(right, top, speedX, -speedY, accelerationX, accelerationY));
	this->pieces.push_back(new CBreakBrickEffect(left, bottom, -speedX, -speedY, accelerationX, accelerationY));
	this->pieces.push_back(new CBreakBrickEffect(right, bottom, speedX, -speedY, accelerationX, accelerationY));

	this->isDestroy = true;
	this->timeDestroy = GetTickCount64();
}