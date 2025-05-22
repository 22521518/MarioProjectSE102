#include "OneUpMushroom.h"
#include "Animations.h"
#include "Collision.h"
#include "ItemConfig.h"
#include "ItemAniIDs.h"
#include "Mario.h"

void COneUpMushroom::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_ONE_UP_MUSHROOM_ITEM)->Render(x, y);
}

void COneUpMushroom::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	mario->OnCollisionWithOneUpMushroom(this, e);
	CMushroom::OnMarioCollide(mario, e);
}
