#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

protected:
	Vector2 pos = { 0, 0 };
	Vector2 size = { 1, 1 };
	Texture *texture = nullptr;
	float rotation = 0;
	bool isDestroy = false;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

public:
	bool IsCollisionRectMouse(POINT p1, POINT reSize);

public:
	Vector2 GetPos() { return pos; }
	Vector2 GetSize() { return size; }
	float GetRotation() { return rotation; }
	bool GetDestroy() { return isDestroy; }

public:
	void SetPos(Vector2 vec2) { pos = vec2; }
	void SetSize(Vector2 vec2) { size = vec2; }
	void SetRotation(float rotate) { rotation = rotate; }
	void SetDestroy(bool param) { isDestroy = param; }
};

