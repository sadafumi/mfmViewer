#ifndef _SCENE_H_
#define _SCENE_H_

#include "Xinput.h"

#define StickThreshold (5000)

typedef enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,		// タイトル画面
	SCENE_SELECT,
	SCENE_GAME,			// ゲーム画面
	SCENE_RESULT,		// リザルト画面
	SCENE_MAX
}SCENE_ID;


void InitScene();
void UninitScene();
void UpdateScene();
void DrawScene();

class Scene
{
public:
	virtual void Init(){}
	virtual void UnInit() = 0;
	virtual void Updata() = 0;
	virtual void Draw() = 0;
};

SCENE_ID ChangeScene(SCENE_ID id);
Controller* GetController();


#endif//_SCENE_H_