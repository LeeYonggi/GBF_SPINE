#include "DXUT.h"
#include "ImagePiece.h"

KeyFrame GetTransformationKeyFrame(Vector2 pos, Vector2 scale, float rotate, bool isKeyFrame)
{
	KeyFrame temp;

	temp.isKeyFrame = isKeyFrame;
	temp.pos = pos;
	temp.scale = scale;
	temp.rotation = rotate;
	return temp;
}

ImagePiece::ImagePiece(Texture * atlasImage, RECT rectImage, string pieceName, float maxFrame)
{
	this->atlasImage = atlasImage;
	this->rectImage = rectImage;
	this->pieceName = pieceName;
	pos = { 0, 0 };

	KeyFrame first;
	first.isKeyFrame = true;
	first.pos = pos;
	vKeyFrame.push_back(first);
	for (int i = 0; i < maxFrame; i++)
	{
		KeyFrame temp;
		temp = GetTransformationKeyFrame(pos, size, rotation, false);
		vKeyFrame.push_back(temp);
	}
}

ImagePiece::~ImagePiece()
{
}

void ImagePiece::Init()
{
}

//프레임 보간
KeyFrame KeyFrameLerp(KeyFrame frame1, KeyFrame frame2, float d)
{
	KeyFrame tempKey;

	tempKey.pos = Lerp(frame1.pos, frame2.pos, d);
	tempKey.rotation = Lerp(frame1.rotation, frame2.rotation, d);
	tempKey.scale = Lerp(frame1.scale, frame2.scale, d);
	tempKey.isKeyFrame = false;

	return tempKey;
}

void KeyFrameVecLerp(vector<int> keyIndexCheck, vector<KeyFrame> *keyFrameData)
{
	for (int i = 0; i < keyIndexCheck.size() - 1; i++)
	{
		for (int j = keyIndexCheck[i] + 1; j < keyIndexCheck[i + 1]; j++)
		{
			KeyFrame firstKeyFrame = (*keyFrameData)[keyIndexCheck[i]];
			KeyFrame secondKeyFrame = (*keyFrameData)[keyIndexCheck[i + 1]];
			
			//키프레임 사이를 보간
			(*keyFrameData)[j] = KeyFrameLerp(firstKeyFrame, secondKeyFrame, 
				((float)j - keyIndexCheck[i]) / ((float)keyIndexCheck[i + 1] - keyIndexCheck[i]));
		}
	}
}

void ImagePiece::Update()
{
	vector<int> vTempFrame;
	for (int i = 0; i < vKeyFrame.size(); i++)
	{
		if (vKeyFrame[i].isKeyFrame == true)
			vTempFrame.push_back(i);
	}
	if (vTempFrame.size() >= 2)
	{
		KeyFrameVecLerp(vTempFrame, &vKeyFrame);
	}
	KeyFrame tempKey = vKeyFrame[vTempFrame.back()];
	tempKey.isKeyFrame = false;
	for (int i = vTempFrame.back() + 1; i < vKeyFrame.size(); i++)
	{
		vKeyFrame[i] = tempKey;
	}
}

void ImagePiece::Render()
{
	if (isFrameMove)
	{
		IMAGEMANAGER->DrawTexture(atlasImage, vKeyFrame[frame].pos + center, rectImage, vKeyFrame[frame].rotation, vKeyFrame[frame].scale);
	}
	else
	{
		IMAGEMANAGER->DrawTexture(atlasImage, pos + center, rectImage, rotation, size);
	}
}

void ImagePiece::Release()
{
}

void ImagePiece::AddKeyFrame(int frame)
{
	KeyFrame temp;
	temp = GetTransformationKeyFrame(pos, size, rotation, true);
	vKeyFrame[frame] = temp;
}

bool ImagePiece::IsPixelCollision(POINT point)
{
	D3DLOCKED_RECT lock;
	bool isCollision = false;
	
	int infoX = rectImage.right - rectImage.left;
	int infoY = rectImage.bottom - rectImage.top;
	int x = (point.x - pos.x) + infoX * 0.5f;
	int y = (point.y - pos.y) + infoY * 0.5f;

	if (x < 0 || x > infoX ||
		y < 0 || y > infoY)
		return false;

	atlasImage->tex->LockRect(0, &lock, nullptr, D3DLOCK_DISCARD);

	DWORD *color = (DWORD*)lock.pBits;

	int colorY = atlasImage->info.Width * (rectImage.top + y);
	if (D3DXCOLOR(color[colorY + rectImage.left + x]).a != 0)
		isCollision = true;
	else
		isCollision = false;

	atlasImage->tex->UnlockRect(0);

	return isCollision;
}
