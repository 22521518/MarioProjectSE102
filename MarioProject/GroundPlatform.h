#pragma once
#include "Platform.h"
class CGroundPlatform :
    public CPlatform
{

    int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) { return 1; };
};

