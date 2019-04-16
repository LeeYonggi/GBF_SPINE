#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

protected:
	Vector2 pos;
	Vector2 size;
	Texture *texture = nullptr;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

public:
	bool IsCollisionRectMouse(POINT p1, POINT reSize);

};

