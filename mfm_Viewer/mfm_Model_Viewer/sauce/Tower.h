#ifndef __TOWER_H__
#define __TOWER_H__

#include "Object.h"
#include "DrawData.h"
#include "Render.h"
#include "Light.h"
#include "scene.h"

class Tower:public Object
{
public:
	void Create(MESHDATA *SetData, D3DXVECTOR3 Pos, D3DXVECTOR3 Roto, D3DXVECTOR3 Scale);
	void Destroy();
	void Update();
	void Draw();
private:
	RenderMesh *RenderData;
};

#endif//__TOWER_H__

