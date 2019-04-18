#pragma once
#include "Object.h"

class ImagePiece;
class UI;

class KeyDownToInt
{
public:
	KeyDownToInt() { }
	virtual ~KeyDownToInt() { }

public:
	bool isKeyUpdate = false;
	int result = 0;
	string str = "";

public:
	void Update();
	int GetResult();
};

class SpineAdmin :
	public Object
{
public:
	SpineAdmin(list<ImagePiece*> vImagePiece);
	virtual ~SpineAdmin();

private:
	list<ImagePiece*> vImagePiece;
	ImagePiece *nowMoveImage = nullptr;
	Vector2 spinePos = { 0, 0 };
	Vector2 spineScale = { 1, 1 };
	KeyDownToInt frameKeyDown;
	UI *startUi = nullptr;
	UI *endUi = nullptr;
	float spineRotate = 0;
	float frame = 0.0f;
	int maxFrame = 30;
	bool isImageMoveing = false;
	bool isFrameUpdate = false;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void MoveImagePiece();

public:
	list<ImagePiece*> GetImagePieces() { return vImagePiece; }
	void OptionFunc();
	void DrawOption();
	void DrawFrame();
	void FrameUpdateStart();
	void FrameUpdateEnd();
};
