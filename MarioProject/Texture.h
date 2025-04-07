#pragma once

#include <d3d10.h>
#include <d3dx10.h>

class CTexture
{
protected:
	ID3D10Texture2D* _tex;
	ID3D10ShaderResourceView* _rsview;
	int _width;
	int _height;
public:
	CTexture();
	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview);
	~CTexture();

	ID3D10ShaderResourceView* GetShaderResourceView() const { return this->_rsview; }
	int GetWidth() const { return this->_width; }
	int GetHeight() const { return this->_height; }
};

typedef CTexture* LPTEXTURE;

