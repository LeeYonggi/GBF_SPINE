#pragma once
#include "Singleton.h"

struct Texture
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 tex;
};
class ImageManager :
	public Singleton<ImageManager>
{
public:
	ImageManager();
	virtual ~ImageManager();

private:
	map<string, Texture*> m_Texture;

public:
	Texture *AddTexture(string str, string path);
	void DrawTexture(string str, Matrix pos, Matrix rotate, Matrix size);

};


#define IMAGEMANAGER ImageManager::GetInstance()