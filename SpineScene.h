#pragma once
#include "Scene.h"

class UI;
class ImagePiece;
class SpineAdmin;
class SpineScene :
	public Scene
{
public:
	SpineScene();
	virtual ~SpineScene();

private:
	UI * fileOpenUi = nullptr;
	SpineAdmin *spineAdmin = nullptr;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void AddAtlasImage();

};

