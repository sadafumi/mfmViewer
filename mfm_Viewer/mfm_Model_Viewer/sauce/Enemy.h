#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
#include "DrawData.h"
#include "Render.h"
#include "Light.h"

class Enemy : public Object
{
public:
	enum ENEMYTEAM 
	{
		TEAMRED,
		TEAMGREEN,
		TEAMBLUE,
		TEAMMAX
	};
	void Create(MFMMESHDATA *in, ENEMYTEAM, D3DXVECTOR3 Pos);
	void Destroy();
	void Updata();
	void Draw();
	void ControlVec(D3DXVECTOR3 in);
private:
	Rendermfm *pRendModel;
};

#endif//__ENEMY_H__

