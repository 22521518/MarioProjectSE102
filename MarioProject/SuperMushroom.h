#pragma once
#include "Mushroom.h"

class CSuperMushroom :
    public CMushroom
{
public:
    CSuperMushroom(float x = 0, float y = 0, DirectionXAxisType nx = DirectionXAxisType::Left, float vx = 0, float vy = 0, float ax = 0, float ay = MUSHROOM_GRAVITY) : CMushroom(x, y, vx, vy, ax, ay, nx) {}

    // game object method
    virtual void Render() override;;

    // collidable with mario interface
    virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) override;
};

typedef CSuperMushroom* LPSUPERMUSHROOM;
