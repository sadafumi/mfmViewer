#pragma once
#include "Render.h"
#include "DrawData.h"

class Draw_model
{
public:
	void Init(DATA_TYPE::MFMMESHDATA*);
	void Uninit();
	void Update();
	void Draw();
	void Reset(DATA_TYPE::MFMMESHDATA*);
private:
	Render::Shader::Modelmfm Render;
	DATA_TYPE::MFMMESHDATA* p_model;
};

