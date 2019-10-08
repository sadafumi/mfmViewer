#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <d3dx9.h>  

class Light
{
public:
	void CreateLight();						//���C�g�̏����ݒ���s��
	void SetDevice();						//�f�o�C�X�ɃZ�b�g
	void SetLightType(D3DLIGHTTYPE InType);	//���̎�ނ��w��
	void SetPosition(D3DVECTOR InPos);		//���̏ꏊ���w��f�B���N�V���i�����Ɩ���
	void SetDirection(D3DVECTOR InDir);		//���̌������w��
	void SetDiffuse(D3DCOLORVALUE InColor);	//�f�B�t���[�Y���w��
	void SetAmbient(D3DCOLORVALUE InColor);	//�A���r�G���g���w��
	void SetSpecular(D3DCOLORVALUE InColor);//�X�y�L�����[���w��
	void SetRange(float InLen);				//���̓͂��������w��f�B���N�V���i�����Ɩ���
	void SetFalloff(float InLen);			//���Ɏg��Ȃ��ꍇ��1.0
	void SetAttenuation(int Num,float);		//��������ݒ�A�������Ō����̎�ނ��w��(0~2)�A���͎����l
	void SetTheta(float radian);			//�����R�[���̊p�x
	void SetPhi(float radian);				//�O���R�[���̊p�x
	void SetLightNumber(int InNum);			//���C�g�̃i���o�[���w�肷��A�f�t�H��0
	D3DLIGHT9 GetLight();
private:
	D3DLIGHT9 d3d_light;
	int LightNum;
};

#endif//__LIGHT_H__
