#include "Player.h"
#include "GameCamera.h"
#include "CreateData.h"



#define MoveSpeed (0.005f)
#define RotaSpeed (0.009f)
#define ReStoreSpeed (0.005f)
#define RotaPitchSpeed (0.010f)
#define AccselSpeed (0.005f)
#define CrossHold (0.00999f)
#define YCheckHold (0.01f)
#define ReStoreHold (0.004f)
#define Max_Speed (1.0f)

#define MAX_AREA (FieldSizeHalf) 

Light PlayerLight;
static D3DXQUATERNION qtRotation;
static D3DXMATRIX mtxRotation;
float a, ythe;
int tre;
bool brake;
D3DXVECTOR3 g_cross,g_RotoVec,g_Came;
void Player::Create(MFMMESHDATA *in)
{
	this->pRendModel = new Rendermfm;
	
	this->pRendModel->SetRendData(in);
	PlayerLight.CreateLight();	
	D3DXQuaternionIdentity(&qtRotation);
	this->spHitbox.pPosition = &this->Pos.Vec;
	this->spHitbox.Radius = 5;
	this->Pos.Vec = D3DXVECTOR3(0.0f,0.5f,0.0f);
}
void Player::Destroy()
{
	delete this->pRendModel;
}
void Player::Updata()
{
	Controller* PlayerController = GetController();
	PlayerController->Updata();
	static D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Playermae = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 PlayerRight = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 PlayerUp = D3DXVECTOR3(0, 1, 0);
	static D3DXVECTOR3 RightVec;
	static D3DXVECTOR3 PlayerOldPos;
	static float Accel = 0.0f;

	D3DXVECTOR3 RotetionVec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXMATRIX world;
	D3DXMATRIX Rotation;
	D3DXMATRIX Scaling;
	D3DXMATRIX Trans;
	
	static float radio = 0;

	D3DXVECTOR2 ControlStickL = PlayerController->GetAnalogStickL();
	D3DXVECTOR2 ControlStickR = PlayerController->GetAnalogStickR();
	int Trigger = PlayerController->GetTriggerR();

	D3DXVECTOR3 CameraVec = GetCameraVec();
	D3DXVECTOR3 Cross,CrossRight;
	D3DXVec3Cross(&Cross, &CameraVec, &this->FrontVec.Vec);
	D3DXVec3Cross(&CrossRight, &PlayerRight, &RightVec);
	g_cross = CrossRight;
	g_Came = CameraVec;
	if (Cross.y > 0.0f)
	{
		if(Cross.y < CrossHold)
		{
			this->FrontVec.Vec.x = CameraVec.x;
			this->FrontVec.Vec.z = CameraVec.z;
		}
		else
		{
			RotetionVec.y = RotaPitchSpeed;
		}
	}
	else
	{
		if (Cross.y > -CrossHold)
		{
			this->FrontVec.Vec.x = CameraVec.x;
			this->FrontVec.Vec.z = CameraVec.z;
		}
		else
		{
			RotetionVec.y = -RotaPitchSpeed;
		}
	}
	float YCheck = CameraVec.y + this->FrontVec.Vec.y;
	ythe = YCheck;
	if(YCheck < 0.0f)
	{
		if (YCheck > -YCheckHold)
		{
			this->FrontVec.Vec.y = CameraVec.y;
		}
		else
		{
			RotetionVec.x = -RotaSpeed;
		}
	}
	else
	{
		if (YCheck < YCheckHold)
		{
			this->FrontVec.Vec.y = CameraVec.y;
		}
		else
		{
			RotetionVec.x = RotaSpeed;
		}
	}
	
	if(CrossRight.z > 0.0f)
	{
		if(CrossRight.z < ReStoreHold)
		{
			RightVec = PlayerRight;
		}
		else
		{
			RotetionVec.z = -ReStoreSpeed;
		}
	}
	else
	{
		if (CrossRight.z > -ReStoreHold)
		{
			RightVec = PlayerRight;
		}
		else
		{
			RotetionVec.z = ReStoreSpeed;
		}
	}

	if(PlayerController->GetPressButton(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		RotetionVec.z += RotaSpeed;
	}
	if(PlayerController->GetPressButton(XINPUT_GAMEPAD_DPAD_LEFT))
	{
		RotetionVec.z += -RotaSpeed;
	}
	


	g_RotoVec += RotetionVec;

	if (ControlStickR.y > StickThreshold)
	{
		if(Accel < Max_Speed)
		{
			Accel += AccselSpeed;
		}
		else
		{
			Accel = Max_Speed;
		}
	}
	if (ControlStickR.y < -StickThreshold)
	{
		if (Accel > 0)
		{
			Accel -= AccselSpeed;
		}
	}

	if (Trigger != 0)
	{
		if (Accel > 0)
		{
			Accel -= AccselSpeed * 5;
		}
	}
	if (Accel < 0)
	{
		Accel = 0;
	}


	tre = Trigger;

	brake = Trigger != 0;
	a = Accel;
	QuaternionRotation(&qtRotation, &mtxRotation, RotetionVec);
	D3DXVec3TransformCoord(&Playermae, &Playermae, &mtxRotation);
	D3DXVec3TransformCoord(&PlayerUp, &PlayerUp, &mtxRotation);
	D3DXVec3TransformCoord(&PlayerRight, &PlayerRight, &mtxRotation);
	D3DXVec3Normalize(&PlayerUp,&PlayerUp);
	D3DXVec3Normalize(&Playermae, &Playermae);
	D3DXVec3Normalize(&PlayerRight, &PlayerRight);

	this->UpVec.Vec = PlayerUp;
	this->FrontVec.Vec = Playermae;
	RightVec = PlayerRight;
	Playermae.x *= Accel;
	Playermae.y *= Accel;
	Playermae.z *= Accel;
	this->Pos.Vec += Playermae;

	this->Pos.Vec.y -= 0.1f;
	if(this->Pos.Vec.x > MAX_AREA || this->Pos.Vec.x < -MAX_AREA)
	{
		if(this->Pos.Vec.x > MAX_AREA)
		{
			this->Pos.Vec.x = MAX_AREA;
		}
		else
		{
			this->Pos.Vec.x = -MAX_AREA;
		}
	}
	if(this->Pos.Vec.y > MAX_AREA || this->Pos.Vec.y < -MAX_AREA)
	{
		if (this->Pos.Vec.y > MAX_AREA)
		{
			this->Pos.Vec.y = MAX_AREA;
		}
		else
		{
			this->Pos.Vec.y = -MAX_AREA;
		}
	}
	if(this->Pos.Vec.z > MAX_AREA || this->Pos.Vec.z < -MAX_AREA)
	{
		if (this->Pos.Vec.z > MAX_AREA)
		{
			this->Pos.Vec.z = MAX_AREA;
		}
		else
		{
			this->Pos.Vec.z = -MAX_AREA;
		}
	}

	D3DXMatrixIdentity(&world);
	D3DXMatrixTranslation(&Trans, this->Pos.Vec.x, this->Pos.Vec.y, this->Pos.Vec.z);
	D3DXMatrixScaling(&Scaling, 0.015f, 0.015f, 0.015f);
	D3DXMatrixMultiply(&world, &world, &Scaling);
	D3DXMatrixMultiply(&world, &world, &mtxRotation);
	D3DXMatrixMultiply(&world, &world, &Trans);
	this->pRendModel->SetMtXWorld(world);
	this->pRendModel->SetLight(PlayerLight.GetLight());
	this->Moving.Vec = this->Pos.Vec - PlayerOldPos;
	PlayerOldPos = this->Pos.Vec;
}
void Player::Draw()
{
	PlayerLight.SetDevice();
	this->pRendModel->Draw();
	DebugText(50, 120,"アクセル%f\nブレーキ(%d)\nプレイヤー外積(%f)(%f)(%f)\n毎フレームの移動値(%f)(%f)(%f)\nカメラベクトル(%f)(%f)(%f)\nY軸回転の無効条件の値(%f)\nプレイヤーの前ベクトル(%f)(%f)(%f)\nプレイヤーの座標(%f)(%f)(%f)"
		,a ,brake, g_cross.x, g_cross.y, g_cross.z, g_RotoVec.x, g_RotoVec.y, g_RotoVec.z, g_Came.x, g_Came.y, g_Came.z, ythe,this->FrontVec.Vec.x, this->FrontVec.Vec.y, this->FrontVec.Vec.z,this->Pos.Vec.x, this->Pos.Vec.y, this->Pos.Vec.z);
}
void Player::SetCamera(D3DXMATRIX In)
{
	this->pRendModel->SetMtXView(In);
}
D3DXVECTOR3 Player::GetUpVec()
{
	return this->UpVec.Vec;
}