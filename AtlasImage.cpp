#include "DXUT.h"
#include "AtlasImage.h"



AtlasImage::AtlasImage(string str)
{
	texture = IMAGEMANAGER->AddTexture(str, str);
	pos = { 0, 0 };
}

AtlasImage::~AtlasImage()
{
}

void AtlasImage::Init()
{
}

void AtlasImage::Update()
{
	ScrollControl();
	CreateMouseLine();
}

void AtlasImage::Render()
{
	Vector2 texInfo = { (float)texture->info.Width, (float)texture->info.Height };
	Vector2 center = scroll + pos + texInfo * 0.5;

	IMAGEMANAGER->DrawTexture(texture, center, {0, 0, (int)texture->info.Width, (int)texture->info.Height });

	//DrawMouseLine
	vector<Vector2> vLine;
	vLine.push_back(scroll + Vector2(lineRect.left, lineRect.top));
	vLine.push_back(scroll + Vector2(lineRect.right, lineRect.top));
	vLine.push_back(scroll + Vector2(lineRect.right, lineRect.bottom));
	vLine.push_back(scroll + Vector2(lineRect.left, lineRect.bottom));
	vLine.push_back(scroll + Vector2(lineRect.left, lineRect.top));

	IMAGEMANAGER->DrawLine(vLine);
}

void AtlasImage::Release()
{
}

void AtlasImage::ScrollControl()
{
	if (INPUTMANAGER->KeyPress(VK_UP))
	{
		scroll.y += 5;
	}
	if (INPUTMANAGER->KeyPress(VK_DOWN))
	{
		scroll.y -= 5;
	}
	if (INPUTMANAGER->KeyPress(VK_LEFT))
	{
		scroll.x += 5;
	}
	if (INPUTMANAGER->KeyPress(VK_RIGHT))
	{
		scroll.x -= 5;
	}
}

void AtlasImage::CreateMouseLine()
{
	if (INPUTMANAGER->KeyDown(VK_LBUTTON) && isOnMouseLine == false)
	{
		lineRect.left = INPUTMANAGER->GetMouse().x - scroll.x;
		lineRect.top = INPUTMANAGER->GetMouse().y - scroll.y;
		isOnMouseLine = true;
	}
	if (isOnMouseLine)
	{
		lineRect.right = INPUTMANAGER->GetMouse().x - scroll.x;
		lineRect.bottom = INPUTMANAGER->GetMouse().y - scroll.y;
		if (INPUTMANAGER->KeyUp(VK_LBUTTON))
			isOnMouseLine = false;
	}
}
