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
void Light::SetPosition(D3DVECTOR InPos)		//���̏ꏊ���w��f�B���N�V���i�����Ɩ���
{
	this->d3d_light.Position = InPos;
}
void Light::SetDirection(D3DVECTOR InDir)		//���̌������w��
{
	this->d3d_light.Direction = InDir;
}
void Light::SetDiffuse(D3DCOLORVALUE InColor)	//�f�B�t���[�Y���w��
{
	this->d3d_light.Diffuse = InColor;
}
void Light::SetAmbient(D3DCOLORVALUE InColor)	//�A���r�G���g���w��
{
	this->d3d_light.Ambient = InColor;
}
void Light::SetSpecular(D3DCOLORVALUE InColor)	//�X�y�L�����[���w��
{
	this->d3d_light.Specular = InColor;
}
void Light::SetRange(float InLen)				//���̓͂��������w��f�B���N�V���i�����Ɩ���
{
	this->d3d_light.Range = InLen;
}
void Light::SetFalloff(float InLen)				//���Ɏg��Ȃ��ꍇ��1.0
{
	this->d3d_light.Falloff = InLen;
}
void Light::SetAttenuation(int Num, float InValue)		//��������ݒ�A�������Ō����̎�ނ��w��(0~2)�A���͎����l
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
void Light::SetTheta(float radian)				//�����R�[���̊p�x
{
	this->d3d_light.Theta = radian;
}
void Light::SetPhi(float radian)				//�O���R�[���̊p�x
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