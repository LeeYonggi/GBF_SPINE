#include "DXUT.h"
#include "UI.h"



UI::UI(function<void()> func, Vector2 pos, Vector2 size, string str)
{
	this->func = func;
	this->pos = pos;
	this->size = size;

	texture = IMAGEMANAGER->AddTexture(str, str);
}

UI::~UI()
{
}

void UI::Init()
{
}

void UI::Update()
{
	if (IsCollisionRectMouse({(int)pos.x, (int)pos.y}, { (int)size.x, (int)size.y}) 
		&& INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		func();
	}
}

void UI::Render()
{
	IMAGEMANAGER->DrawTexture(texture, pos, {0, 0, (int)texture->info.Width, (int)texture->info.Height });
}

void UI::Release()
{
}

