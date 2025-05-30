#include "Coin.h"
#include "CoinAniIDs.h"
#include "CoinStateIDs.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

#pragma region COLLIDABLE_MARIO_METHOD
void CCoin::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	this->Delete();
	mario->OnCollisionWithCoin(this, e);
}
#pragma region endregion