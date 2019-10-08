#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "DrawData.h"
#include "InputKeyboard.h"

class Camera
{
public:
	static void SetVec(D3DXVECTOR3 In)
	{
		Vec = In;
	};
	static void SetPos(D3DXVECTOR3 In)
	{
		Pos = In;
	};
	static D3DXVECTOR3 GetPos();
	static D3DXVECTOR3 GetVec();
	static void Updata();
	static D3DXMATRIX GetViewMtx() { return mtxView; };
private:
	static const int YHOLLD = 7;
	static const int ROTO_SPEED = 2;
	static D3DXMATRIX mtxView;
	static D3DXVECTOR3 Pos;
	static D3DXVECTOR3 Vec;
	static D3DXVECTOR3 Eye;
	static D3DXVECTOR3 At;
	static D3DXVECTOR3 Up;


};

#endif//__CAMERA_H__
