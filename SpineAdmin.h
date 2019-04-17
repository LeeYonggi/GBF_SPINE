#pragma once
#include "Object.h"

class ImagePiece;
class SpineAdmin :
	public Object
{
public:
	SpineAdmin(list<ImagePiece*> vImagePiece);
	virtual ~SpineAdmin();

private:
	list<ImagePiece*> vImagePiece;
	ImagePiece *nowMoveImage = nullptr;
	bool isImageMoveing = false;
	int maxFrame = 30;
	float frame = 0.0f;
	Vector2 spinePos = { 0, 0 };
	Vector2 spineScale = { 1, 1 };
	float spineRotate = 0;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void MoveImagePiece();

public:
	list<ImagePiece*> GetImagePieces() { return vImagePiece; }
	void DrawOption();
	void DrawFrame();
};

