#pragma once
#include "GameObject.h"
class CGameDecor :
    public CGameObject
{
public:
    CGameDecor(float x = 0, float y = 0) : CGameObject(x, y) {};
};

typedef CGameDecor* LPGAMEDECOR;