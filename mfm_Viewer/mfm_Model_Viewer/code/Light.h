#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "DrawData.h"
#include "Graphics.h"


class Lighter:protected DeviceHider
{
public:
	Lighter();
	void SetVS(int);
	void SetPS(int );
	D3DXVECTOR4 CamePos;
	D3DXVECTOR4 Light;
	D3DXVECTOR4 Ambient;
	D3DXVECTOR4 Ambient_mat;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR4 Diffuse_mat;
	D3DXVECTOR4 Emissive;
	D3DXVECTOR4 Emissive_mat;
	D3DXVECTOR4 Specular;
	D3DXVECTOR4 Specular_mat;
	float Specular_Power;
	float Power;
};


#endif//__LIGHT_H__
