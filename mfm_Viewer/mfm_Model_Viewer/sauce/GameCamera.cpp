#include "GameCamera.h"
#include "Camera.h"
#include "Xinput.h"

#define MMOVE_SPEED (1)
#define ROTO_SPEED (0.3f)
#define CROSSHOLD (0.1)
#define YHOLLD (0.7)
#define CAMERA1 (D3DXVECTOR3(500.0f, 500.0f, 500.0f))
#define CAMERA2 (D3DXVECTOR3(-500.0f, 500.0f, 500.0f))
#define CAMERA3 (D3DXVECTOR3(500.0f, 500.0f, -500.0f))
#define CAMERA4 (D3DXVECTOR3(-500.0f, 500.0f, -500.0f))


Camera GameCame;
static D3DXVECTOR3 g_Vector, g_Cross;
D3DXVECTOR2 ControlStickL;
int g_Camera;

void InitGameCamera()
{
}
void UnInitGameCamera()
{
}
void UpdateGameCamera()
{
	Controller *CameCon = GetController();
	Player* Playerdata = GetPlayer();
	D3DXVECTOR3 PlayerPos = Playerdata->GetPos();
	D3DXVECTOR3 PlayerVec = Playerdata->GetFrontVec();
	D3DXVECTOR3 PlayerUp = Playerdata->GetUpVec();
	bool PressB = false;
	bool PressA = false;

	static D3DXVECTOR3 ueVector(0.0f, 1.0f, 0.0f);
	static D3DXVECTOR3 maeVector(0.0f, 0.0f, 1.0f);
	static D3DXVECTOR3 migiVector(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 Vector(1.0f,0.0f,0.0f);
	static D3DXVECTOR3 HoldVector;
	static D3DXVECTOR3 CameraPos = CAMERA1;
	static D3DXVECTOR3 HoldmaeVector;
	static int CameraCan = 0;
	g_Camera = CameraCan;
	D3DXMATRIX rotY;
	D3DXMATRIX rotAc;

	//カメラ座標
	static D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//注視点
	static D3DXVECTOR3 at = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//カメラの向き
	static D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Vector = (eye - at);
	maeVector = (eye - at);
	D3DXVec3Cross(&migiVector, &maeVector, &ueVector);
	D3DXVec3Normalize(&maeVector, &maeVector);
	D3DXVec3Normalize(&migiVector, &migiVector);
	D3DXVec3Normalize(&Vector, &Vector);


	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &Vector, &ueVector);
	ControlStickL = CameCon->GetAnalogStickL();
	bool LockatUp = !(Vector.y > YHOLLD);
	bool LockatUnder = !(Vector.y < -YHOLLD);
 	g_Cross = Cross;

	if (CameCon->GetPressButton(XINPUT_GAMEPAD_B))
	{
		PressB = true;
	}
	if (CameCon->GetPressButton(XINPUT_GAMEPAD_A))
	{
		PressA = true;
	}

	if(!PressB)
	{
		if (ControlStickL.y > StickThreshold)
		{
			if (LockatUp)
			{
				D3DXMatrixRotationAxis(&rotAc, &migiVector, D3DXToRadian(ROTO_SPEED));
				D3DXVec3TransformNormal(&Vector, &Vector, &rotAc);
			}
		}
		if (ControlStickL.y < -StickThreshold)
		{
			if (LockatUnder)
			{
				D3DXMatrixRotationAxis(&rotAc, &migiVector, -D3DXToRadian(ROTO_SPEED));
				D3DXVec3TransformNormal(&Vector, &Vector, &rotAc);
			}
		}
		if (ControlStickL.x > StickThreshold)
		{
			D3DXMatrixRotationY(&rotY, D3DXToRadian(ROTO_SPEED));
			D3DXVec3TransformNormal(&Vector, &Vector, &rotY);
		}
		if (ControlStickL.x < -StickThreshold)
		{
			D3DXMatrixRotationY(&rotY, -D3DXToRadian(ROTO_SPEED));
			D3DXVec3TransformNormal(&Vector, &Vector, &rotY);
		}
	}
	if(CameCon->GetTriggerButton(XINPUT_GAMEPAD_Y))
	{

		CameraCan++;
		if(CameraCan == 0)
		{
			CameraPos = CAMERA1;
		}
		if (CameraCan == 1)
		{
			CameraPos = CAMERA2;
		}
		if (CameraCan == 2)
		{
			CameraPos = CAMERA3;
		}
		if (CameraCan == 3)
		{
			CameraPos = CAMERA4;
			CameraCan = -1;
		}
	}
	g_Camera = CameraCan;
	if(PressB)
	{
		g_Vector = HoldVector;
		at = PlayerPos;
		eye = CameraPos;
		eye.y += 2;
	}
	else if(PressA)
	{
		eye = PlayerPos + Vector * 6;
		at = PlayerPos;
		g_Vector = HoldVector;
		eye.y += 2;
	}
	else

	{
		eye = PlayerPos + Vector * 6;
		at = PlayerPos;
		g_Vector = Vector;
		HoldVector = g_Vector;
		eye.y += 2;
	}

	//at = PlayerPos ; 
	//eye = PlayerPos - PlayerVec * 5;

	
	GameCame.SetCameraUp(up);
	GameCame.SetEyePos(eye);
	GameCame.SetLookat(at);
	GameCame.Updata();
	eye = PlayerPos + Vector * 6;
	at = PlayerPos;

}
void DrawGameCamera()
{
	DebugText(50, 50,"前ベクトル(%f)(%f)(%f)\n外積ベクトル(%f)(%f)(%f)\nコントローター←(%d)→(%d)↑(%d)↓(%d)\nカメラ(%d)",
		g_Vector.x, g_Vector.y, g_Vector.z,
		g_Cross.x, g_Cross.y, g_Cross.z,
		ControlStickL.x < -StickThreshold, ControlStickL.x > StickThreshold, ControlStickL.y > StickThreshold, ControlStickL.y < -StickThreshold),
		g_Camera;
}
D3DXMATRIX GetGameCamera()
{
	return GameCame.GetMatrix();
}
D3DXVECTOR3 GetCameraVec()
{
	return g_Vector;
}