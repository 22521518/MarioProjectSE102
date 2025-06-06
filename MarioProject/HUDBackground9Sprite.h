#pragma once
#include "HUDObject.h"
class CHUDBackground9Sprite : public CHUDObject {
protected:
	int length = 0, height = 0;
	float cellWidth = 0, cellHeight = 0; // Unit: cell 
	int spriteIdTopBegin = 0, spriteIdTopMiddle = 0, spriteIdTopEnd = 0,
		spriteIdMidBegin = 0, spriteIdMidMiddle = 0, spriteIdMidEnd = 0,
		spriteIdBotBegin = 0, spriteIdBotMiddle = 0, spriteIdBotEnd = 0;
public:
	CHUDBackground9Sprite(float offX = 0, float offY = 0) : CHUDObject(offX, offY) {};
	static CHUDBackground9Sprite* FromSingleSprite(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id, float offX = 0, float offY = 0);
	CHUDBackground9Sprite(float x, float y, int length, int height, float cell_width, float cell_height, int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end, int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end, int sprite_id_bot_begin, int sprite_id_bot_middle, int sprite_id_bot_end, float offX = 0, float offY = 0);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {};
	void Render() override;
	void RenderByRow(float xx, float yy, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) const;

};