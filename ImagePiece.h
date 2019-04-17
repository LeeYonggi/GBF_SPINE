#pragma once
#include "Object.h"

struct KeyFrame
{
	Matrix mat;
	bool isKeyFrame = false;
};
class ImagePiece :
	public Object
{
public:
	ImagePiece(Texture *atlasImage, RECT rectImage, string pieceName, float maxFrame);
	virtual ~ImagePiece();

private:
	Texture * atlasImage;
	RECT rectImage;
	string pieceName = "";
	Vector2 center = { SCREEN_X * 0.5f, SCREEN_Y * 0.5f };
	vector<KeyFrame> vFrameMatrix;
	float frame = 0.0f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	POINT GetRectImageSize() { return {rectImage.right - rectImage.left, rectImage.bottom - rectImage.top }; }
	void AddKeyFrame(int frame);

public:
	void SetFrame(float param) { frame = param; }
};

