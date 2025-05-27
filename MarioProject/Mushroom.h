#pragma once
#include "Item.h"
#include "ItemConfig.h"
#include "ItemStateIDs.h"

class CMushroom :
    public CItem
{
    bool isGrowing = false;
    ULONGLONG startTime = 0;
    float startY;
public:
    CMushroom(float x = 0, float y = 0, float vx = 0, float vy = 0, float ax = 0, float ay = MUSHROOM_GRAVITY, DirectionXAxisType nx = DirectionXAxisType::Left, int state = MUSHROOM_STATE_IDLE) : CItem(x, y, vx, vy, ax, ay, nx, state), startY(y) {
     		this->SetState(state);
            this->SetActive(false);
    }

    // game object method
    virtual void Render() = 0;
    virtual void Activate() { this->SetActive(true); isGrowing = true; }

    // physical object method
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
    virtual void Update(DWORD dt, vector<LPPHYSICALOBJECT>* coObjects) override;

    // interactive object method
    virtual void OnNoCollision(DWORD dt) override;
    virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;
    virtual void SetState(int state) override;
    virtual int IsCollidable() override { return 1; }

    // collidable with mario interface
    virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;

};

typedef CMushroom* LPMUSHROOM;