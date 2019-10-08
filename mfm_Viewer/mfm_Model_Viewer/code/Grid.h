#pragma once

#include "Render.h"
#include "DrawData.h"

class Grid
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	Render::Shader::VtxStripLine Render;
	DATA_TYPE::VERTEXDATA Grid_Vertex;
};

