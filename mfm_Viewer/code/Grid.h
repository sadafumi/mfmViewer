#ifndef __GRID_H__
#define __GRID_H__

#include "Render.h"

class Grid
{
public:
	void Init();
	void Uninit();
	void Updata();
	void Draw();
private:
	Render::Shader::Line Render;
	DATA_TYPE::VERTEX data;
};


#endif//__POLYGON3D_H__