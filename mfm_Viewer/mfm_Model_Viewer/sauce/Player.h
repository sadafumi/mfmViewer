#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"
#include "DrawData.h"
#include "Render.h"
#include "Light.h"
#include "Xinput.h"
#include "scene.h"


class Player : public Object
{
public:
	void Create(MFMMESHDATA *in);
	void Destroy();
	void Updata();
	void Draw();
	void SetCamera(D3DXMATRIX In);
	D3DXVECTOR3 GetUpVec();
private:
	Vecter3 UpVec;
	Rendermfm *pRendModel;
};

#endif//__PLAYER_H__

