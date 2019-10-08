#include "Tower.h"
#include "GameCamera.h"

Light TowerLight;

void Tower::Create(MESHDATA *SetData, D3DXVECTOR3 Pos, D3DXVECTOR3 Roto, D3DXVECTOR3 Scale)
{
	this->RenderData = new RenderMesh;
	this->RenderData->SetRendData(SetData);
	TowerLight.CreateLight();
	this->RenderData->SetLight(TowerLight.GetLight());
	this->Pos.Vec = Pos;
	this->Roto.Vec = Roto;
	this->Scaleing.Vec = Scale;
}
void Tower::Destroy()
{
	delete this->RenderData;
}
void Tower::Update()
{
	D3DXMATRIX world, Scale, Roto, Pos;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranslation(&Pos, this->Pos.Vec.x, this->Pos.Vec.y, this->Pos.Vec.z );
	D3DXMatrixScaling(&Scale,this->Scaleing.Vec.x, this->Scaleing.Vec.y, this->Scaleing.Vec.z);
	D3DXMatrixRotationYawPitchRoll(&Roto,this->Roto.Vec.x, this->Roto.Vec.y, this->Roto.Vec.z);
	
	D3DXMatrixMultiply(&world, &world,&Scale);
	D3DXMatrixMultiply(&world, &world, &Roto);
	D3DXMatrixMultiply(&world, &world, &Pos);
	

	this->RenderData->SetMtXWorld(world);
	this->RenderData->SetMtXView(GetGameCamera());
}
void Tower::Draw()
{
	this->RenderData->Draw();
}
