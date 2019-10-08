#include "Light.h"


Lighter::Lighter()
{
	this->CamePos = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	this->Light = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	this->Ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Ambient_mat = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Diffuse_mat = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Emissive = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	this->Emissive_mat = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Specular = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Specular_mat = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	this->Specular_Power = 1.0f;
	this->Power = 1.0f;
}

void Lighter::SetVS(int index)
{
	DeviceHider::SetVertexShaderFloat(index + 0, &this->Diffuse.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 1, &this->Emissive.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 2, &this->Ambient.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 3, &this->Specular.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 4, &this->Light.x, 1);
				 
	DeviceHider::SetVertexShaderFloat(index + 5, &this->Diffuse_mat.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 6, &this->Emissive_mat.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 7, &this->Ambient_mat.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 8, &this->Specular_mat.x, 1);
				
	DeviceHider::SetVertexShaderFloat(index + 9, &this->Power, 1);
	DeviceHider::SetVertexShaderFloat(index + 10, &this->CamePos.x, 1);
	DeviceHider::SetVertexShaderFloat(index + 11, &this->Specular_Power, 1);
}

void Lighter::SetPS(int index)
{
	DeviceHider::SetPixelShaderFloat(index + 0, &this->Diffuse.x, 1);
	DeviceHider::SetPixelShaderFloat(index + 1, &this->Emissive.x, 1);
	DeviceHider::SetPixelShaderFloat(index + 2, &this->Ambient.x		, 1);
	DeviceHider::SetPixelShaderFloat(index + 3, &this->Specular.x, 1);
	DeviceHider::SetPixelShaderFloat(index + 4, &this->Light.x, 1);
	
	DeviceHider::SetPixelShaderFloat(index + 5, &this->Diffuse_mat.x, 1);
	DeviceHider::SetPixelShaderFloat(index + 6, &this->Emissive_mat.x, 1);
	DeviceHider::SetPixelShaderFloat(index + 7, &this->Ambient_mat.x	, 1);
	DeviceHider::SetPixelShaderFloat(index + 8, &this->Specular_mat.x, 1);
	
	DeviceHider::SetPixelShaderFloat(index + 9, &this->Power	, 1);
	DeviceHider::SetPixelShaderFloat(index + 10, &this->CamePos.x, 1);

	DeviceHider::SetPixelShaderFloat(index + 11, &this->Specular_Power, 1);
}
