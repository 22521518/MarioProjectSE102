#pragma once
#include "Mario.h"

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

// interface for object that interact with mario
// instead of if else dynamic cast like in the origin source
class CCollidableWithMario {
public:
    virtual void OnMarioCollide(LPMARIO mario, LPCOLLISIONEVENT e) = 0;
};

typedef CCollidableWithMario* LPCOLLIDABLEWITHMARIO;