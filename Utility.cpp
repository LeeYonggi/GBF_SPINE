#include "DXUT.h"
#include "Utility.h"


bool IsCollisionRectMouse(POINT p1, POINT reSize)
{
	RECT re, uiRect, mouse;
	uiRect = { p1.x - (int)(reSize.x * 0.5), p1.y - (int)(reSize.y * 0.5),
		p1.x + (int)(reSize.x * 0.5), p1.y + (int)(reSize.y * 0.5) };
	mouse = { INPUTMANAGER->GetMouse().x, INPUTMANAGER->GetMouse().y,
		INPUTMANAGER->GetMouse().x + 1, INPUTMANAGER->GetMouse().y + 1 };
	return IntersectRect(&re, &uiRect, &mouse);
}