#pragma once
#include <unordered_map>
#include "StaticObject.h"

using namespace std;

class CPlatform :
    public CStaticObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
public:
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end);

	static unordered_map<string, float> GetAdditionalFieldInfo(vector<string> tokens);
	
	// game object method
	virtual void Render() override;

	// physical object method
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	virtual void GetBoundingBox(RECT& rect) override;
	virtual int IsDirectionColliable(DirectionXAxisType nx, DirectionYAxisType ny) override;
	virtual void RenderBoundingBox() override;
};

typedef CPlatform* LPPLATFORM;

