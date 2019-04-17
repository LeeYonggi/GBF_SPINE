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
	LPD3DXSPRITE sprite;
	ID3DXLine *line;

public:
	Texture *AddTexture(string str, string path);
	void DrawTexture(Texture *tex, Matrix pos, Matrix rotate, Matrix scale, RECT cutImage);
	void DrawTexture(Texture *tex, Vector2 pos, RECT cutImage, float rotate = 0, Vector2 size = { 1, 1 });
	void DrawLine(vector<Vector2> vLine, D3DXCOLOR color = D3DXCOLOR(0, 0, 0, 1));
	void DrawFont(string str, Vector2 pos, float size);
	void BeginSprite();
	void EndSprite();

};


#define IMAGEMANAGER ImageManager::GetInstance()