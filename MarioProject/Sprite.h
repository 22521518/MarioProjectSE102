#pragma once

#include "Texture.h"
#include "Game.h"

class CSprite
{
	int id;			

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite();
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);
	~CSprite();
	int GetTop() { return top; }
	int GetLeft() { return left; }
	int GetRight() { return right; }
	int GetBottom() { return bottom; }
	void Draw(float x, float y);
	void DrawOnScreen(float x, float y);
};

typedef CSprite* LPSPRITE;