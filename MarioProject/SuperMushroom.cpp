#include "SuperMushroom.h"
#include "Animations.h"
#include "Collision.h"
#include "ItemConfig.h"
#include "ItemAniIDs.h"

void CSuperMushroom::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_SUPER_MUSHROOM_ITEM)->Render(x, y);
}

void CSuperMushroom::OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e)
{
	//mario->OnCollisionWith(e);
	mario->OnCollisionWithSuperMushroom(this, e);
	CMushroom::OnMarioCollide(mario, e);
}
