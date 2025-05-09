#include "Sprite.h"

CSprite::CSprite()
{
	this->id = 0;
	this->left = this->top = this->right = this->bottom = 0;
	this->texture = nullptr;

	sprite.pTexture = nullptr;
	sprite.TexCoord = { 0, 0 };
	sprite.TexSize = { 0, 0 };
	sprite.ColorModulate = D3DXCOLOR(0, 0, 0, 0);

	D3DXMatrixIdentity(&this->matScaling);
}

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	float texWidth = (float)tex->GetWidth();
	float texHeight = (float)tex->GetHeight();
	int spriteWidth = (this->GetRight() - this->GetLeft() + 1);
	int spriteHeight = (this->GetBottom() - this->GetTop() + 1);

	sprite.pTexture = tex->GetShaderResourceView();
	sprite.TexCoord.x = this->GetLeft() / texWidth;
	sprite.TexCoord.y = this->GetTop() / texHeight;
	sprite.TexSize.x = spriteWidth / texWidth;
	sprite.TexSize.y = spriteHeight / texHeight;

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
}

void CSprite::DrawOnScreen(float x, float y)
{
	CGame* g = CGame::GetInstance();

	D3DXMATRIX matTranslation;

	x = (FLOAT)floor(x);
	y = (FLOAT)floor(y);

	D3DXMatrixTranslation(&matTranslation, x, g->GetBackBufferHeight() - y, 0.1f);

	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}
void CSprite::Draw(float x, float y)
{
	if (id == 0 || texture == nullptr) return;
	CGame* g = CGame::GetInstance();
	float cx = 0, cy = 0;
	g->GetCamPos(cx, cy);

	cx = (FLOAT)floor(cx);
	cy = (FLOAT)floor(cy);

	D3DXMATRIX matTranslation;

	x = (FLOAT)floor(x);
	y = (FLOAT)floor(y);

	D3DXMatrixTranslation(&matTranslation, x - cx, g->GetBackBufferHeight() - y + cy, 0.1f);

	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&this->sprite, 1, 0, 0);
}

CSprite::~CSprite()
{
}