#include "Flag.h"

#define FlagModelPath ("resource\\model\\cube.x")
Light FlagLight;

void Flag::Create(FlagBelong in, D3DXVECTOR3 Pos)
{
	this->pRendModel = new RenderMesh;
	CreateMesh(&this->dataFlag, FlagModelPath);
	this->pRendModel->SetRendData(&this->dataFlag);
	this->Belong = in;
	this->Pos.Vec = Pos;
	this->Atteribute = DefaultState;
	this->spHitbox.pPosition = &this->Pos.Vec;
	this->spHitbox.Radius = 3;
	FlagLight.CreateLight();
}
void Flag::Destroy()
{
	delete this->pRendModel;
	this->dataFlag.Destroy();
}
void Flag::Updata()
{
	D3DXMATRIX Trans;
	D3DXMatrixTranslation(&Trans, this->Pos.Vec.x, this->Pos.Vec.y, this->Pos.Vec.z);
	this->pRendModel->SetMtXWorld(Trans);
}
void Flag::Draw()
{
	FlagLight.SetDevice();
	this->pRendModel->Draw();
}
void Flag::SetState(FlghAttribute in)
{
	this->Atteribute = in;
}
int Flag::GetState()
{
	return this->Atteribute;
}
void Flag::SetCamera(D3DXMATRIX in)
{
	this->pRendModel->SetMtXView(in);
}