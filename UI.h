#pragma once

#include "Object.h"

class UI:
	public Object
{
public:
	UI(function<void()> func, Vector2 pos, Vector2 size, string str);
	virtual ~UI();

private:
	function<void()> func;

public:
	void Init();
	void Update();
	void Render();
	void Release();

};

