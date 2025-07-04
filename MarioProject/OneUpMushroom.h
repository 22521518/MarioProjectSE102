#pragma once
#include "Mushroom.h"

class COneUpMushroom :
    public CMushroom
{
public:
    COneUpMushroom(float x = 0, float y = 0, DirectionXAxisType nx = DirectionXAxisType::Left, float vx = 0, float vy = 0, float ax = 0, float ay = MUSHROOM_GRAVITY) : CMushroom(x, y, vx, vy, ax, ay, nx) { this->score = 1000; }

    // game object method
    virtual void Render() override;;

    // collidable with mario interface
    virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
};

typedef COneUpMushroom* LPONEUPMUSHROOM;