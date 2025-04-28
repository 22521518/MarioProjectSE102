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

	if (this->timeDestroy - GetTickCount64() > 5000) {
		this->timeDestroy = -1;
		for (int i = 0; i < pieces.size(); i++)
		{
			this->pieces[i]->Delete();
		}
		this->Delete();
		return;
	}

	for (int i = 0; i < pieces.size(); i++)
	{
		this->pieces[i]->Render();
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

void CDestroyableBrick::OnDestroy()
{

	float left, top, right, bottom;
	this->GetBoundingBox(left, top, right, bottom);
	float speedX = 0.1f;
	float speedY = -0.2f;
	float accelerationX = 0.005f;
	float accelerationY = 0.00075f;

	this->pieces.push_back(new CBreakBrickEffect(left, top, -speedX, speedY, accelerationX, accelerationY));
	this->pieces.push_back(new CBreakBrickEffect(right, top, speedX, speedY, accelerationX, accelerationY));
	this->pieces.push_back(new CBreakBrickEffect(left, bottom, -speedX, speedY, accelerationX, accelerationY));
	this->pieces.push_back(new CBreakBrickEffect(right, bottom, speedX, speedY, accelerationX, accelerationY));


	this->isDestroy = true;
	this->timeDestroy = GetTickCount64();
}