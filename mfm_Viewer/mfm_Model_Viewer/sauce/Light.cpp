#include "Include.h"


void Light::CreateLight()
{
	ZeroMemory(&this->d3d_light, sizeof(this->d3d_light));
	this->d3d_light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&this->d3d_light.Direction, &vecDir);
	this->d3d_light.Diffuse.r = 1.0f;
	this->d3d_light.Diffuse.g = 1.0f;
	this->d3d_light.Diffuse.b = 1.0f;
	this->d3d_light.Diffuse.a = 1.0f;
	this->LightNum = 0;
}
void Light::SetDevice()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();
	Device->SetLight( this->LightNum, &this->d3d_light );
	Device->LightEnable( this->LightNum, TRUE);
}
void  Light::SetLightType(D3DLIGHTTYPE InType)
{
	this->d3d_light.Type = InType;
}
void Light::SetPosition(D3DVECTOR InPos)		//光の場所を指定ディレクショナルだと無効
{
	this->d3d_light.Position = InPos;
}
void Light::SetDirection(D3DVECTOR InDir)		//光の向きを指定
{
	this->d3d_light.Direction = InDir;
}
void Light::SetDiffuse(D3DCOLORVALUE InColor)	//ディフューズを指定
{
	this->d3d_light.Diffuse = InColor;
}
void Light::SetAmbient(D3DCOLORVALUE InColor)	//アンビエントを指定
{
	this->d3d_light.Ambient = InColor;
}
void Light::SetSpecular(D3DCOLORVALUE InColor)	//スペキュラーを指定
{
	this->d3d_light.Specular = InColor;
}
void Light::SetRange(float InLen)				//光の届く長さを指定ディレクショナルだと無効
{
	this->d3d_light.Range = InLen;
}
void Light::SetFalloff(float InLen)				//特に使わない場合は1.0
{
	this->d3d_light.Falloff = InLen;
}
void Light::SetAttenuation(int Num, float InValue)		//減衰率を設定、第一引数で減衰の種類を指定(0~2)、第二は実数値
{
	if(Num == 0)
	{
		this->d3d_light.Attenuation0 = InValue;
	}
	else if(Num == 1)
	{
		this->d3d_light.Attenuation1 = InValue;
	}
	else if(Num == 2)
	{
		this->d3d_light.Attenuation2 = InValue;
	}
	else 
	{
		this->d3d_light.Attenuation0 = InValue;
	}
}
void Light::SetTheta(float radian)				//内部コーンの角度
{
	this->d3d_light.Theta = radian;
}
void Light::SetPhi(float radian)				//外部コーンの角度
{
	this->d3d_light.Phi = radian;
}
void Light::SetLightNumber(int InNum)
{
	this->LightNum = InNum;
}
D3DLIGHT9 Light::GetLight()
{
	return this->d3d_light;
}