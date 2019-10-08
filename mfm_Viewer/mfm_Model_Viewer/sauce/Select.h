#ifndef _SELECT_H_
#define _SELECT_H_

#include "scene.h"

class SelectScene :public Scene
{
	void Init();
	void UnInit();
	void Updata();
	void Draw();
};

#endif//_SELECT_H_