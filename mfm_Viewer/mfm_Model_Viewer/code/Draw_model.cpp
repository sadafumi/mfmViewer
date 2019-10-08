#include "Draw_model.h"
#include "Camera.h"

void Draw_model::Init(DATA_TYPE::MFMMESHDATA* in_model)
{
	p_model = in_model;
}

void Draw_model::Uninit()
{
}

void Draw_model::Update()
{
	Render.SetRendData(p_model);
	Render.SetMtXView(Camera::GetViewMtx());
}

void Draw_model::Draw()
{
	if (p_model != NULL)
	{
		Render.Draw();
	}
}

void Draw_model::Reset(DATA_TYPE::MFMMESHDATA* in_model)
{
	p_model = in_model;
	
}
