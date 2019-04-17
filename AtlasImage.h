#pragma once
#include "Object.h"
class AtlasImage :
	public Object
{
public:
	AtlasImage(string str);
	virtual ~AtlasImage();
	
private:
	Vector2 scroll = { 0, 0 };
	RECT lineRect = { 0, 0, 0, 0 };
	bool isOnDrawRect = false;
	string atlasName = "";

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	void ScrollControl();
	void CreateMouseLine();
	void AddAtlasData();

};

