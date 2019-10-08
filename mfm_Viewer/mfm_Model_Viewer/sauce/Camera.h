#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Include.h"


void CameraInit();
void CameraUninit();
void CameraUpdate();
void CameraDraw();
D3DXMATRIX GetViewMtx();
D3DXVECTOR3 GetCameraMove();

class Camera
{
public:
	Camera();
	~Camera();
	void Updata();
	void SetEyePos(D3DXVECTOR3 In);
	void SetLookat(D3DXVECTOR3 In);
	void SetCameraUp(D3DXVECTOR3 In);
	D3DXMATRIX GetMatrix();
private:
	D3DXMATRIX mtxView;
	D3DXVECTOR3 vecEyePos;
	D3DXVECTOR3 vecLookat;
	D3DXVECTOR3 vecCameraUp;

};

#endif//__CAMERA_H__
