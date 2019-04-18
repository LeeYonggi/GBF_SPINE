#pragma once
#include "Object.h"

struct KeyFrame
{
	Vector2 pos = { 0, 0 };
	Vector2 scale = { 1, 1 };
	float rotation = 0.0f;
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
	vector<KeyFrame> vKeyFrame;
	float frame = 0.0f;
	bool isFrameMove = false;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	POINT GetRectImageSize() { return {rectImage.right - rectImage.left, rectImage.bottom - rectImage.top }; }
	void AddKeyFrame(int frame);
	void SetFrameMove(bool param) { isFrameMove = param; }

public:
	void SetFrame(float param) { frame = param; }
	bool GetFrameMove() { return isFrameMove; }
};

