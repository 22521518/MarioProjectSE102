#include "Texture.h"

CTexture::CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
{
	this->_tex = tex;
	this->_rsview = rsview;

	D3D10_TEXTURE2D_DESC desc;
	this->_tex->GetDesc(&desc);
	this->_width = desc.Width;
	this->_height = desc.Height;
}

CTexture::~CTexture()
{
	if (_rsview != NULL) this->_rsview->Release();
	if (_tex != NULL) this->_tex->Release();
}