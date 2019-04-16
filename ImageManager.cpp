#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

Texture * ImageManager::AddTexture(string str, string path)
{
	auto iter = m_Texture.find(str);
	if (iter != m_Texture.end()) return iter->second;

	Texture *temp = new Texture();

	D3DXCreateTextureFromFileExA(
		DEVICE,
		path.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		&temp->info,
		nullptr,
		&temp->tex);

	m_Texture.insert(make_pair(str, temp));

	return temp;
}

void ImageManager::DrawTexture(string str, Matrix pos, Matrix rotate, Matrix size)
{
}
