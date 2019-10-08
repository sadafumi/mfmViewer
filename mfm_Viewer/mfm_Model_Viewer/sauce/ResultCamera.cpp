//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "Include.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

Camera ResultCame;

void InitResultCamera(void)
{

}
void UninitResultCamera(void)
{

}
void UpdateResultCamera(void)
{
	static D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//注視点
	static D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//カメラの向き
	static D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	static float i = 0;
	at.x = (float)sin(i * PI / 180.0f);
	at.z = (float)cos(i * PI / 180.0f);
	ResultCame.SetCameraUp(up);
	ResultCame.SetEyePos(eye);
	ResultCame.SetLookat(at);
	ResultCame.Updata();
	i += 0.05f;
	if (i >= 360)
	{
		i = 0;
	}
}
void DrawResultCamera(void)
{

}
D3DXMATRIX GetResultCamera()
{
	return ResultCame.GetMatrix();
}