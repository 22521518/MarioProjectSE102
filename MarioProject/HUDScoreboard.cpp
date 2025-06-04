#include "HUDScoreboard.h"
#include "HUDConfig.h"
#include "HUDSpriteIDs.h"
#include "Sprites.h"

CHUDScoreboard::CHUDScoreboard(ULONGLONG* time, ULONGLONG* score, ULONGLONG* life, ULONGLONG* coin)
{
	this->backgroundId = ID_SPRITE_HUD_SCORE_BACKGROUND;
	this->offsetX = 14.f, this->offsetY = 8.f;
	this->time_remain = time;
	this->scores = score;
	this->lives = life;
	this->coins = coin;
}

void CHUDScoreboard::Render()
{
	CSprites::GetInstance()->Get(backgroundId)->Draw(x + offsetX + HUD_SCOREBOARD_WIDTH / 2, y + offsetY);
	for (auto it : items) {
		it->SetPosition(x + offsetX, y + offsetY);
		it->Render();
	}
}
