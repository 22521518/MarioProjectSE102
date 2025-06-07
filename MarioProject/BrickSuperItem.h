#pragma once
#include "BrickItem.h"
#include "BrickAniIDs.h"

class CBrickSuperItem :
	public CBrickItem
{
protected:
	int aniIdActive;
	int aniIdEmpty;
	bool isOneUp;

	bool onBounce = false;
public:
	static unordered_map<string, float> GetAdditionalFieldInfo(vector<string> tokens);

	CBrickSuperItem(float x = 0, float y = 0, int ani_id_active = ID_ANI_ITEM_BRICK, int ani_id_empty = ID_ANI_EMPTY_ITEM_BRICK, bool isOneUp = false , float vx = 0, float vy = 0, float ax = 0, float ay = BRICK_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = BRICK_STATE_ACTIVE, int numberOfCollision = 1)
		: CBrickItem (x, y, vx, vy, ax, ay, nx, state, numberOfCollision), 
		aniIdActive(ani_id_active), aniIdEmpty(ani_id_empty), isOneUp(isOneUp) {
	}
	void CreateSuperLeaf(LPCOLLISIONEVENT e);
	void CreateSuperMushroom(LPCOLLISIONEVENT e);
	void CreateOneUpMushroom(LPCOLLISIONEVENT e);

	// game object method
	virtual void Render() override;
	virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

	// on mario collide
	virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
	virtual void OnDestroy (LPCOLLISIONEVENT e) override;

	virtual void Bouncing();
	bool IsOneUpBrick() const { return isOneUp; }
};

typedef CBrickSuperItem* LPBRICKSUPERITEM;