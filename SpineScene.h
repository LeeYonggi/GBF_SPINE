#pragma once
#include "Scene.h"
class SpineScene :
	public Scene
{
public:
	SpineScene();
	virtual ~SpineScene();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

