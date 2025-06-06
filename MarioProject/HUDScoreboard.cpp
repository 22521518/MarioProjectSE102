#include "HUDScoreboard.h"
#include "HUDConfig.h"
#include "HUDWorld.h"
#include "Sprites.h"

CHUDScoreboard::CHUDScoreboard(UINT* time, ULONG* score, UINT* life, UINT* coin, UINT* world, float offX, float offY) : CHUDObject(offX, offY)
{
	items.push_back(CHUDObject::CreateHUDWorld(world));
	items.push_back(CHUDObject::CreateHUDLives(life));
	items.push_back(CHUDObject::CreateHUDScores(score));
	items.push_back(CHUDObject::CreateHUDTimes(time));
	items.push_back(CHUDObject::CreateHUDCoins(coin));
	items.push_back(CHUDObject::CreateHUDPowerP());
}

void CHUDScoreboard::Render()
{
	CSprites::GetInstance()->Get(backgroundId)->Draw(x + offsetX + HUD_SCOREBOARD_WIDTH / 2, y + offsetY);
	for (auto it : items) {
		it->SetPosition(x + offsetX, y + offsetY);
		it->Render();
	}
}
