#include "HUDObject.h"
#include "HUDWorld.h"
#include "HUDLives.h"
#include "HUDScore.h"
#include "HUDTime.h"
#include "HUDCoin.h"
#include "HUDPowerP.h"
#include "HUDItems.h"
#include "HUDScoreboard.h"

CHUDObject* CHUDObject::CreateHUDWorld(UINT* pWorld, float offX, float offY)
{
    return new CHUDWorld(pWorld, offX, offY);
}

CHUDObject* CHUDObject::CreateHUDLives(UINT* pLives, float offX, float offY)
{
    return new CHUDLives(pLives, offX, offY);
}

CHUDObject* CHUDObject::CreateHUDScores(ULONG* pScores, float offX, float offY)
{
    return new CHUDScore(pScores, offX, offY);
}

CHUDObject* CHUDObject::CreateHUDTimes(UINT* pTimes, float offX, float offY)
{
    return new CHUDTime(pTimes, offX, offY);
}

CHUDObject* CHUDObject::CreateHUDCoins(UINT* pCoins, float offX, float offY)
{
    return new CHUDCoin(pCoins, offX, offY);;
}

CHUDObject* CHUDObject::CreateHUDPowerP(float offX, float offY)
{
    return new HUDPowerP(offX, offY);;
}

CHUDObject* CHUDObject::CreateHUDItems(float offX, float offY)
{
    return new CHUDItems(offX, offY);;
}

CHUDObject* CHUDObject::CreateHUDScoreboard(UINT* time, ULONG* score, UINT* life, UINT* coin, UINT* world, float offX, float offY)
{
    return new  CHUDScoreboard(time, score, life, coin, world);
}



