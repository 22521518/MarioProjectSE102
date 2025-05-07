#pragma once
#include "StaticObject.h"
#include <unordered_map>

class CPlatform9Sprite : public CStaticObject {

protected:
	int length, height;				
	float cellWidth, cellHeight; // Unit: cell 
	int spriteIdTopLeft, spriteIdTopMiddle, spriteIdTopEnd,
		spriteIdMidLeft, spriteIdMidMiddle, spriteIdMidEnd,
	spriteIdBottomLeft, spriteIdBottomMiddle, spriteIdBottomEnd;
public:
	CPlatform9Sprite(float x = 0, float y = 0, int length = 1, int height = 1,
		float cell_width = 16, float cell_height = 16,
		int sprite_id_top_begin, int sprite_id_top_mid_topdle, int sprite_id_top_end,
		int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end,
		int sprite_id_bottom_begin, int sprite_id_bottom_middle, int sprite_id_bottom_end
	);

	static unordered_map<string, float> GetAdditionalFieldInfo(vector<string> tokens);

	// game object method
	virtual void Render() override;

	// physical object method
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) = 0;
};