#include "DXUT.h"
#include "SpineAdmin.h"

#include "ImagePiece.h"

SpineAdmin::SpineAdmin(list<ImagePiece*> vImagePiece)
{
	this->vImagePiece = vImagePiece;
}


SpineAdmin::~SpineAdmin()
{
}

void SpineAdmin::Init()
{
}

void SpineAdmin::Update()
{
	for_each(vImagePiece.begin(), vImagePiece.end(), [](ImagePiece *imagePiece) { imagePiece->Update(); });
	MoveImagePiece();
}

void SpineAdmin::Render()
{
	for_each(vImagePiece.begin(), vImagePiece.end(), [](ImagePiece *imagePiece) { imagePiece->Render(); });
	if(nowMoveImage)
		DrawOption();
	DrawFrame();
}

void SpineAdmin::Release()
{
	for (auto iter : vImagePiece)
	{
		SAFE_RELEASE(iter);
		SAFE_DELETE(iter);
	}
	vImagePiece.clear();
}

bool GetTuchImage(ImagePiece *imagePiece)
{
	POINT tempPos = { imagePiece->GetPos().x + SCREEN_X * 0.5, imagePiece->GetPos().y + SCREEN_Y * 0.5 };
	if (imagePiece->IsCollisionRectMouse(tempPos, imagePiece->GetRectImageSize()))
		return true;
	return false;
}

void SpineAdmin::MoveImagePiece()
{
	if (isImageMoveing == false && INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		//list 탐색
		list<ImagePiece*>::iterator tempImage;

		for (auto iter = vImagePiece.begin(); iter != vImagePiece.end(); iter++)
		{
			if (GetTuchImage(*iter))
			{
				nowMoveImage = *iter;
				tempImage = iter;
				isImageMoveing = true;
			}
		}

		//선택한 이미지가 앞으로 나오게
		if (isImageMoveing)
		{
			vImagePiece.erase(tempImage);
			vImagePiece.push_back(nowMoveImage);
		}
	}
	if (isImageMoveing && nowMoveImage)
	{
		//이미지 이동
		Vector2 tempMouse = { (float)INPUTMANAGER->GetMouse().x, (float)INPUTMANAGER->GetMouse().y };
		nowMoveImage->SetPos(tempMouse - Vector2(SCREEN_X * 0.5f, SCREEN_Y * 0.5f));
		nowMoveImage->AddKeyFrame(frame);
	}
	if (INPUTMANAGER->KeyUp(VK_LBUTTON))
	{
		isImageMoveing = false;
	}
	if (INPUTMANAGER->KeyDown('R') && nowMoveImage)
	{
		nowMoveImage->SetPos({ 0, 0 });
	}
}

void SpineAdmin::DrawOption()
{
	IMAGEMANAGER->DrawFont("Rotate:" + to_string(nowMoveImage->GetRotation()), { 1000, 510 }, 20);
	IMAGEMANAGER->DrawFont("Scale:" + to_string(nowMoveImage->GetSize().x) + " " + to_string(nowMoveImage->GetSize().y), { 1000, 540 }, 20);
	IMAGEMANAGER->DrawFont("Pos:" + to_string(nowMoveImage->GetPos().x) + " " + to_string(nowMoveImage->GetPos().y), { 1000, 570 }, 20);
}

void SpineAdmin::DrawFrame()
{
	IMAGEMANAGER->DrawFont("Frame: " + to_string((int)frame), { 1000, 600 }, 30);
	IMAGEMANAGER->DrawFont("MaxFrame: " + to_string(maxFrame), { 1000, 650 }, 30);
}
