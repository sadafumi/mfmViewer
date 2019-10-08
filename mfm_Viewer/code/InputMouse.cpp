#include "InputMouse.h"

POINT InputMouse::point;
HWND* InputMouse::hWnd;

void InputMouse::Init(HWND * inhWnd)
{
	hWnd = inhWnd;
}

void InputMouse::Uninit()
{
}

void InputMouse::Updata()
{
}

D3DXVECTOR2 InputMouse::GetMousePos()
{
	GetCursorPos(&point);
	ScreenToClient(*hWnd, &point);
	return D3DXVECTOR2((float)point.x, (float)point.y);
}
