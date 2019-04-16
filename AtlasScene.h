#pragma once
#include "Scene.h"

class UI;
class AtlasImage;
class AtlasScene :
	public Scene
{
public:
	AtlasScene();
	virtual ~AtlasScene();

private:
	UI * ui = nullptr;
	AtlasImage *atlasImage = nullptr;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void AddAtlasImage();
};

