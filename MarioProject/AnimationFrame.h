#pragma once

#include "Sprite.h"

class CSprite;
typedef CSprite* LPSPRITE;

class CAnimationFrame
{
protected:
	LPSPRITE sprite;
	DWORD time;

public:
	virtual void Draw(float x, float y);

	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() const { return time; }
	virtual LPSPRITE GetSprite() const { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

