#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "DrawData.h"
#include "InputKeyboard.h"

class Camera
{
public:
	static void Updata();
	static D3DXMATRIX GetViewMtx() { return mtxView; };
private:
	static const int YHOLLD;
	static const int ROTO_SPEED ;
	static D3DXMATRIX mtxView;
	
};

#endif//__CAMERA_H__