#include "DXUT.h"
#include "SpineAdmin.h"

#include "ImagePiece.h"
#include "UI.h"


SpineAdmin::SpineAdmin(list<ImagePiece*> vImagePiece)
{
	this->vImagePiece = vImagePiece;
}


SpineAdmin::~SpineAdmin()
{
}

void SpineAdmin::Init()
{
	startUi = new UI([&]() {FrameUpdateStart(); }, { 1180, 200 }, {200, 100}, "../Image/Start.png");
	endUi = new UI([&]() {FrameUpdateEnd(); }, { 1180, 300 }, { 200, 100 }, "../Image/Stop.png");
	vPutIndex.push_back(KeyDownToInt({ 1100, 630 }, { 100, 40 }));
	vPutIndex.push_back(KeyDownToInt({ 1100, 585 }, { 80, 20 }));
	vPutIndex.push_back(KeyDownToInt({ 1200, 585 }, { 80, 20 }));
	vPutIndex.push_back(KeyDownToInt({ 1100, 550 }, { 80, 20 }));
	vPutIndex.push_back(KeyDownToInt({ 1200, 550 }, { 80, 20 }));
	vPutIndex.push_back(KeyDownToInt({ 1100, 520 }, { 80, 20 }));
}

void SpineAdmin::Update()
{
	if (isFrameUpdate)
		frame += DXUTGetElapsedTime() * 10;
	if (frame > maxFrame)
		frame = 0;
	for (auto iter = vImagePiece.begin(); iter != vImagePiece.end(); )
	{
		if ((*iter)->GetDestroy())
		{
			SAFE_RELEASE((*iter));
			SAFE_DELETE((*iter));
			iter = vImagePiece.erase(iter);
		}
		else
		{
			(*iter)->Update();
			if (isFrameUpdate)
				(*iter)->SetFrame(frame);
			++iter;
		}
	}
	MoveImagePiece();
	startUi->Update();
	endUi->Update();;
	OptionFunc();
}

void SpineAdmin::Render()
{
	for_each(vImagePiece.begin(), vImagePiece.end(), [](ImagePiece *imagePiece) { imagePiece->Render(); });
	if(nowMoveImage)
		DrawOption();
	startUi->Render();
	endUi->Render();
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

	SAFE_RELEASE(startUi);
	SAFE_DELETE(startUi);
	SAFE_RELEASE(endUi);
	SAFE_DELETE(endUi);
}

bool GetTuchImage(ImagePiece *imagePiece)
{
	POINT tempPos = { INPUTMANAGER->GetMouse().x - SCREEN_X * 0.5, INPUTMANAGER->GetMouse().y - SCREEN_Y * 0.5 };
	//if (imagePiece->IsCollisionRectMouse(tempPos, imagePiece->GetRectImageSize()))
	//	return true;
	if (imagePiece->IsPixelCollision(tempPos))
		return true;
	return false;
}

void SpineAdmin::MoveImagePiece()
{
	if (isImageMoveing == false && INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		//list 탐색
		list<ImagePiece*>::iterator tempIter;
		for (auto iter = vImagePiece.begin(); iter != vImagePiece.end(); iter++)
		{
			if (GetTuchImage(*iter))
			{
				tempIter = iter;
				nowMoveImage = *iter;
				isImageMoveing = true;
			}
		}

		//선택한 이미지가 앞으로 나오게
		if (isImageMoveing && frame == 0)
		{
			vImagePiece.erase(tempIter);
			vImagePiece.push_back(nowMoveImage);
		}
	}
	if (isImageMoveing && nowMoveImage)
	{
		//이미지 프레임 이동
		Vector2 tempMouse = { (float)INPUTMANAGER->GetMouse().x, (float)INPUTMANAGER->GetMouse().y };
		nowMoveImage->SetPos(tempMouse - Vector2(SCREEN_X * 0.5f, SCREEN_Y * 0.5f));
		nowMoveImage->AddKeyFrame(frame);
	}
	if (INPUTMANAGER->KeyUp(VK_LBUTTON))
	{
		isImageMoveing = false;
	}
}

void SpineAdmin::OptionFunc()
{
	if (!nowMoveImage) return;
	if (INPUTMANAGER->KeyDown('R'))
	{
		nowMoveImage->SetPos({ 0, 0 });
	}
	if (INPUTMANAGER->KeyDown('D'))
	{
		nowMoveImage->SetDestroy(true);
		nowMoveImage = nullptr;
	}
	vPutIndex[0].Update(&frame);
	Vector2 tempPos = nowMoveImage->GetPos(), tempSize = nowMoveImage->GetSize();
	float tempRotate = nowMoveImage->GetRotation();
	vPutIndex[1].Update(&tempPos.x);
	vPutIndex[2].Update(&tempPos.y);
	nowMoveImage->SetPos(tempPos);
	vPutIndex[3].Update(&tempSize.x);
	vPutIndex[4].Update(&tempSize.y);
	nowMoveImage->SetSize(tempSize);
	vPutIndex[5].Update(&tempRotate);
	nowMoveImage->SetRotation(tempRotate);
}

void SpineAdmin::DrawOption()
{
	string sizeStr = to_string(nowMoveImage->GetSize().x) + " " + to_string(nowMoveImage->GetSize().y);
	string posStr = to_string(nowMoveImage->GetPos().x) + " " + to_string(nowMoveImage->GetPos().y);

	IMAGEMANAGER->DrawFont("Rotate:" + to_string(nowMoveImage->GetRotation()), { 1000, 510 }, 20);
	IMAGEMANAGER->DrawFont("Scale:" + sizeStr, { 1000, 540 }, 20);
	IMAGEMANAGER->DrawFont("Pos:" + posStr, { 1000, 570 }, 20);
}

void SpineAdmin::DrawFrame()
{
	IMAGEMANAGER->DrawFont("Frame: " + to_string((int)frame), { 1000, 600 }, 30);
	IMAGEMANAGER->DrawFont("MaxFrame: " + to_string(maxFrame), { 1000, 650 }, 30);
}

void SpineAdmin::FrameUpdateStart()
{
	for_each(vImagePiece.begin(), vImagePiece.end(), [](ImagePiece *imagePiece) { imagePiece->SetFrameMove(true); });
	isFrameUpdate = true;
	frame = 0;
}

void SpineAdmin::FrameUpdateEnd()
{
	for_each(vImagePiece.begin(), vImagePiece.end(), [](ImagePiece *imagePiece) { imagePiece->SetFrameMove(false); });
	isFrameUpdate = false;
	frame = 0;
}

void KeyDownToInt::Update(float *resultPoint)
{
	if (IsCollisionRectMouse(pos, size) && INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		isKeyUpdate = true;
		str = "";
	}
	if (isKeyUpdate == true)
	{
		for (int i = 48; i < 58; i++)
		{
			if(INPUTMANAGER->KeyDown(i))
				str.push_back(i);
		}
		for (int i = 189; i <= 190; i++)
		{
			if (INPUTMANAGER->KeyDown(i))
				str.push_back(i - 144);
		}
	}
	if (isKeyUpdate && INPUTMANAGER->KeyDown(VK_RETURN))
	{
		isKeyUpdate = false;
		*resultPoint = GetResult();
	}
}

float KeyDownToInt::GetResult()
{
	return atoi(str.c_str());
}
