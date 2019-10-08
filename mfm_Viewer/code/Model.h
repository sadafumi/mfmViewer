#pragma once
#include "Render.h"
class Model
{
public:
	Model();
	~Model();
	void Init(const char* TeXCFileName);
	void Uninit();
	void Updata();
	void Draw();
	bool Active = false;
private:
	DATA_TYPE::MFMMESHDATA data;
	Render::Shader::Modelmfm model;
};

