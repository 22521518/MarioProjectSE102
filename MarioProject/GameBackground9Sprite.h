#pragma once

#include "GameDecor.h"

class CGameBackground9Sprite :
    public CGameDecor
{
protected:
	int length, height;
	float cellWidth, cellHeight; // Unit: cell 
	int spriteIdTopBegin, spriteIdTopMiddle, spriteIdTopEnd,
		spriteIdMidBegin, spriteIdMidMiddle, spriteIdMidEnd,
		spriteIdBotBegin, spriteIdBotMiddle, spriteIdBotEnd;
public:
	static CGameBackground9Sprite* FromSingleSprite (float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id);
	CGameBackground9Sprite(float x = 0, float y = 0, int length = 1, int height = 1,
		float cell_width = 16, float cell_height = 16,
		int sprite_id_top_begin = 0, int sprite_id_top_middle = 0, int sprite_id_top_end = 0,
		int sprite_id_mid_begin = 0, int sprite_id_mid_middle = 0, int sprite_id_mid_end = 0,
		int sprite_id_bot_begin = 0, int sprite_id_bot_middle = 0, int sprite_id_bot_end = 0
	);

	static unordered_map<string, float> GetAdditionalFieldInfo(vector<string> tokens);

	// game object method
	void Render() override;
	void RenderByRow(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) const;

	// physical object method
	void GetBoundingBox(float& l, float& t, float& r, float& b) override {};
};

typedef CGameBackground9Sprite* LPGAMEBACKGROUND9SPRITE;