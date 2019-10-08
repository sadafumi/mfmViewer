#include "Include.h"

Camera TitleCame;

void TitleCameraInit(void)
{

}
void TitleCameraDraw(void)
{

}
void TitleCameraUpdate(void)
{
	static D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//’Ž‹“_
	static D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//ƒJƒƒ‰‚ÌŒü‚«
	static D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	static float i = 0;
	at.x = (float)sin(i * PI / 180.0f);
	at.z = (float)cos(i * PI / 180.0f);
	TitleCame.SetCameraUp(up);
	TitleCame.SetEyePos(eye);
	TitleCame.SetLookat(at);
	TitleCame.Updata();
	i += 0.05f;
	if(i >= 360)
	{
		i = 0;
	}
}
void TitleCameraUninit(void)
{

}
D3DXMATRIX GatTitleCamera()
{
	return TitleCame.GetMatrix();
}

