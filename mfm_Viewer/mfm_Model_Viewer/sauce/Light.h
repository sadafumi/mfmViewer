#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <d3dx9.h>  

class Light
{
public:
	void CreateLight();						//ライトの初期設定を行う
	void SetDevice();						//デバイスにセット
	void SetLightType(D3DLIGHTTYPE InType);	//光の種類を指定
	void SetPosition(D3DVECTOR InPos);		//光の場所を指定ディレクショナルだと無効
	void SetDirection(D3DVECTOR InDir);		//光の向きを指定
	void SetDiffuse(D3DCOLORVALUE InColor);	//ディフューズを指定
	void SetAmbient(D3DCOLORVALUE InColor);	//アンビエントを指定
	void SetSpecular(D3DCOLORVALUE InColor);//スペキュラーを指定
	void SetRange(float InLen);				//光の届く長さを指定ディレクショナルだと無効
	void SetFalloff(float InLen);			//特に使わない場合は1.0
	void SetAttenuation(int Num,float);		//減衰率を設定、第一引数で減衰の種類を指定(0~2)、第二は実数値
	void SetTheta(float radian);			//内部コーンの角度
	void SetPhi(float radian);				//外部コーンの角度
	void SetLightNumber(int InNum);			//ライトのナンバーを指定する、デフォは0
	D3DLIGHT9 GetLight();
private:
	D3DLIGHT9 d3d_light;
	int LightNum;
};

#endif//__LIGHT_H__
