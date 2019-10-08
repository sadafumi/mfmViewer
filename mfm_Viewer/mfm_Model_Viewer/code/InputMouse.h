#pragma once
#include "DrawData.h"
class InputMouse
{
public:
	static void Init(HWND* hWnd);
	static void Uninit();
	static void Updata();
	static D3DXVECTOR2 GetMousePos();
private:
	static  POINT point;
	static  HWND* hWnd;
};

