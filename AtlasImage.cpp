#include "DXUT.h"
#include "AtlasImage.h"

#include <fstream>


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
	
	if (isOnDrawRect)
		AddAtlasData();

}

void AtlasImage::Render()
{
	Vector2 texInfo = { (float)texture->info.Width, (float)texture->info.Height };
	Vector2 center = scroll + pos + texInfo * 0.5;

	IMAGEMANAGER->DrawTexture(texture, center, {0, 0, (int)texture->info.Width, (int)texture->info.Height });

	//DrawMouseLine
	if (isOnDrawRect)
	{
		vector<Vector2> vLine;
		vLine.push_back(scroll + Vector2(lineRect.left, lineRect.top));
		vLine.push_back(scroll + Vector2(lineRect.right, lineRect.top));
		vLine.push_back(scroll + Vector2(lineRect.right, lineRect.bottom));
		vLine.push_back(scroll + Vector2(lineRect.left, lineRect.bottom));
		vLine.push_back(scroll + Vector2(lineRect.left, lineRect.top));

		IMAGEMANAGER->DrawLine(vLine);
	}
	IMAGEMANAGER->DrawFont(atlasName, {50, 650}, 70);
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
	if (INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		atlasName = "";
		lineRect.left = INPUTMANAGER->GetMouse().x - scroll.x;
		lineRect.top = INPUTMANAGER->GetMouse().y - scroll.y;
		lineRect.right = INPUTMANAGER->GetMouse().x - scroll.x;
		lineRect.bottom = INPUTMANAGER->GetMouse().y - scroll.y;
		isOnDrawRect = true;
	}
	if (INPUTMANAGER->KeyPress(VK_LBUTTON))
	{
		lineRect.right = INPUTMANAGER->GetMouse().x - scroll.x;
		lineRect.bottom = INPUTMANAGER->GetMouse().y - scroll.y;
	}
}

void AddNumberStreamFile(fstream *fs, int number)
{
	*fs << number << ",";
}
void AtlasImage::AddAtlasData()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (INPUTMANAGER->KeyDown(VK_BACK) && atlasName.size() != 0)
		{
			atlasName.pop_back();
			break;
		}
		else if (INPUTMANAGER->KeyDown(VK_RETURN))
		{
			std::fstream fs;
			fs.open(L"../Data/AtlasData.txt", ios::app);

			if (fs.fail())
			{
				fs.close();
				return;
			}
			//WriteAtlasName
			fs << atlasName << "/";

			//WriteRectInfo
			AddNumberStreamFile(&fs, min(lineRect.left, lineRect.right));
			AddNumberStreamFile(&fs, min(lineRect.top, lineRect.bottom));
			AddNumberStreamFile(&fs, max(lineRect.right, lineRect.left));
			AddNumberStreamFile(&fs, max(lineRect.bottom, lineRect.top));
			fs << endl;

			fs.close();
			break;
		}
		else if (INPUTMANAGER->KeyDown(i) && i != VK_LBUTTON)
		{
			atlasName.push_back(i);
		}
	}
}
