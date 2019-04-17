#include "DXUT.h"
#include "ImagePiece.h"

Matrix GetTransformationMatrix(Vector2 pos, Vector2 scale, float rotate)
{
	Matrix matW, matS, matR, matT;

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotate));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;
	return matW;
}

ImagePiece::ImagePiece(Texture * atlasImage, RECT rectImage, string pieceName, float maxFrame)
{
	this->atlasImage = atlasImage;
	this->rectImage = rectImage;
	this->pieceName = pieceName;
	pos = { 0, 0 };

	KeyFrame first;
	first.isKeyFrame = true;
	first.mat = GetTransformationMatrix(pos, size, rotation);
	vFrameMatrix.push_back(first);
	for (int i = 0; i < maxFrame; i++)
	{
		KeyFrame temp;
		temp.isKeyFrame = false;
		temp.mat = GetTransformationMatrix(pos, size, rotation);
		vFrameMatrix.push_back(temp);
	}
}

ImagePiece::~ImagePiece()
{
}

void ImagePiece::Init()
{
}

void ImagePiece::Update()
{
	vector<int> vTempFrame;
	for (int i = 0; i < vFrameMatrix.size(); i++)
	{
		if (vFrameMatrix[i].isKeyFrame == true)
			vTempFrame.push_back(i);
	}
	if (vTempFrame.size() >= 2)
	{

	}
	KeyFrame tempKey = vFrameMatrix[vTempFrame.back()];
	tempKey.isKeyFrame = false;
	for (int i = vTempFrame.back() + 1; i < vFrameMatrix.size(); i++)
	{
		vFrameMatrix[i] = tempKey;
	}
}

void ImagePiece::Render()
{
	IMAGEMANAGER->DrawTexture(atlasImage, pos + center, rectImage, rotation, size);
}

void ImagePiece::Release()
{
}

void ImagePiece::AddKeyFrame(int frame)
{
	KeyFrame temp;
	temp.isKeyFrame = true;
	temp.mat = GetTransformationMatrix(pos, size, rotation);
	vFrameMatrix[frame] = temp;
}
