#include "Include.h"

#define MMOVE_SPEED (1)
#define ROTO_SPEED (2)

static D3DXMATRIX g_mtxView;
static D3DXVECTOR3 g_vecMove;

void CameraInit()
{

}
void CameraUninit()
{

}
void CameraUpdate()
{
	g_vecMove.x = 0;
	g_vecMove.y = 0;
	g_vecMove.z = 0;
	static float angle = 0;
	static float fYaw = 0, fPitch = 0, fRoll = 0;
	static D3DXMATRIX mtxRotation, mtxMove;
	static D3DXQUATERNION qtRotation;
	D3DXVECTOR3 maeVector(0.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 maePos(0.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 Oldeye;
	//カメラ座標
	static D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	//注視点
	static D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//カメラの向き
	static D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	static BOOL  boOneTime = FALSE;
	if (!boOneTime)
	{
		boOneTime = TRUE;
		D3DXQuaternionIdentity(&qtRotation);
	}
	if (GetKeyboardPress(DIK_P))
	{
		fYaw = -0.02f;
	}
	if (GetKeyboardPress(DIK_O))
	{
		fYaw = 0.02f;
	}
	if (GetKeyboardPress(DIK_UP))
	{
		fPitch = -0.02f;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		fPitch = 0.02f;
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		fRoll = 0.02f;
		
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		fRoll = -0.02f;
	}
	if (GetKeyboardPress(DIK_H))
	{
		at = at;
	}

	D3DXMATRIX mtxMome;
	D3DXQUATERNION qtAxis;
	D3DXQUATERNION qtYaw;
	D3DXQUATERNION qtPitch;
	D3DXQUATERNION qtRoll;
	D3DXQuaternionRotationAxis( &qtYaw,   &D3DXVECTOR3(mtxRotation._21, mtxRotation._22, mtxRotation._23), fYaw);
	D3DXQuaternionRotationAxis( &qtPitch, &D3DXVECTOR3(mtxRotation._11, mtxRotation._12, mtxRotation._13), fPitch);
	D3DXQuaternionRotationAxis( &qtRoll,  &D3DXVECTOR3(mtxRotation._31, mtxRotation._32, mtxRotation._33), fRoll);
	D3DXQuaternionMultiply( &qtRotation, &qtRotation, &qtYaw);
	D3DXQuaternionMultiply( &qtRotation, &qtRotation, &qtPitch);
	D3DXQuaternionMultiply( &qtRotation, &qtRotation, &qtRoll);
	D3DXMatrixRotationQuaternion(&mtxRotation, &qtRotation);
	fYaw = fPitch = fRoll = 0;

	D3DXMatrixTranslation(&mtxMome, 1, 0, 0);
	mtxMove *= mtxMome;

	D3DXVECTOR3 vecEye(0, 0, 0);
	D3DXVECTOR3 vecLook(0, 0, 1);
	D3DXVECTOR3 vecUp(0, 1, 0);
	D3DXVECTOR3 vecMove(0, 0, 0);
	D3DXVec3TransformCoord(&vecMove, &vecMove, &mtxMove);
	D3DXVec3TransformCoord(&vecLook, &vecLook, &mtxRotation);
	D3DXVec3TransformCoord(&vecUp, &vecUp, &mtxRotation);
	if (GetKeyboardPress(DIK_W))
	{
		maeVector += (vecLook - vecEye);
	}
	//下
	if (GetKeyboardPress(DIK_S))
	{
		maeVector += (vecEye - vecLook);
	}
	maePos += maeVector;
	//上

	vecEye  += maePos * 0.1f;
	vecLook += maePos * 0.1f;

	D3DXMatrixLookAtLH(&g_mtxView, &vecEye, &vecLook, &vecUp);
	
	g_vecMove = maePos - Oldeye;
	Oldeye = maePos;
}
D3DXMATRIX GetViewMtx()
{
	return g_mtxView;
}
D3DXVECTOR3 GetCameraMove()
{
	return g_vecMove;
}
Camera::Camera()
{
	this->vecEyePos   = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	this->vecLookat   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}
Camera::~Camera()
{

}
void Camera::SetEyePos(D3DXVECTOR3 In)
{
	this->vecEyePos = In;
}
void Camera::SetLookat(D3DXVECTOR3 In)
{
	this->vecLookat = In;
}
void Camera::SetCameraUp(D3DXVECTOR3 In)
{
	this->vecCameraUp = In;
}
void Camera::Updata()
{
	D3DXMatrixLookAtLH(&this->mtxView, &this->vecEyePos, &this->vecLookat, &this->vecCameraUp);
}
D3DXMATRIX Camera::GetMatrix()
{
	return this->mtxView;
}
