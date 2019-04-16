#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
	D3DXCreateSprite(DEVICE, &sprite);
	D3DXCreateLine(DEVICE, &line);
	line->SetWidth(2);
	line->SetAntialias(true);
}


ImageManager::~ImageManager()
{
	SAFE_RELEASE(sprite);
	SAFE_RELEASE(line);
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
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

void ImageManager::DrawTexture(Texture *tex, Matrix pos, Matrix rotate, Matrix scale, RECT cutImage)
{
	Matrix matW;

	matW = scale * rotate * pos;

	sprite->SetTransform(&matW);

	Vector3 center = { tex->info.Width * 0.5f, tex->info.Height * 0.5f, 0 };

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(tex->tex, &cutImage, &center, nullptr, D3DXCOLOR(1, 1, 1, 1));
	sprite->End();
}

void ImageManager::DrawTexture(Texture *tex, Vector2 pos, RECT cutImage, float rotate, float size)
{
	Matrix matW, matS, matR, matT;

	D3DXMatrixScaling(&matS, size, size, 1);
	D3DXMatrixRotationZ(&matR, rotate);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	Vector3 center = { tex->info.Width * 0.5f, tex->info.Height * 0.5f, 0 };

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(tex->tex, &cutImage, &center, nullptr, D3DXCOLOR(1, 1, 1, 1));
	sprite->End();
}

void ImageManager::DrawLine(vector<Vector2> vLine, D3DXCOLOR color)
{
	line->Begin();

	line->Draw(&vLine[0], vLine.size(), color);

	line->End();
}

void ImageManager::BeginSprite()
{
}

void ImageManager::EndSprite()
{
}
