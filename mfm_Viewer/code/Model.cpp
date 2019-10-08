#include "Model.h"
#include "Camera.h"
#include "CreateData.h"

Model::Model()
{
}


Model::~Model()
{
}

void Model::Init(const char* TeXCFileName)
{
	Create::MFMMesh(&data, TeXCFileName);
	this->Active = true;
	model.SetRendData(&data);
}

void Model::Uninit()
{
	this->Active = false;
}

void Model::Updata()
{
	model.SetMtXView(Camera::GetViewMtx());
}

void Model::Draw()
{
	if (this->Active)
	{
		model.Draw();
	}
}
