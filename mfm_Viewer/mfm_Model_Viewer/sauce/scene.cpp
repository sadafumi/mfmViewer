#include "scene.h"
#include "TitleInclude.h"
#include "SelectInclude.h"
#include "GameInclude.h"
#include "ResultInclude.h"


#define START_SCENE (SCENE_TITLE)	// デバッグ終わったらTITLEに直してね

//関数ポインター　()(関数の引数の型) 
//void(*pFaunc)(void) = InitTitle;
typedef void(*SceneFunc)(void);
typedef D3DXMATRIX(*SceneFuncMtx)(void);
Controller Con;
TitleScene g_title;
SelectScene g_select;
GameScene g_game;
ResultScene g_result;
static  Scene *g_Scene[SCENE_MAX] = { &g_title, &g_select, &g_game, &g_result };

static  const SceneFuncMtx g_pCamera[] =
{
	//各シーンのDrawが入る
	GatTitleCamera,
	GatSelectCamera,
	GetGameCamera,
	GetResultCamera
};

static SCENE_ID g_nID = START_SCENE; //今のシーン
static SCENE_ID g_nNextID = START_SCENE; //次のシーン

void InitScene()
{
	g_Scene[g_nID]->Init();
}
void UninitScene()
{
	g_Scene[g_nID]->UnInit();
}
void UpdateScene()
{
	CameraUpdate();
	UpdateKeyboard();
	g_Scene[g_nID]->Updata();
	SetBackgroundView(g_pCamera[g_nID]());
	BackgroundUpdate();
	UpdateFade();
}
void DrawScene()
{
	
	g_Scene[g_nID]->Draw();
	if(g_nNextID != g_nID )
	{
		UninitScene();
		g_nID = g_nNextID;
		InitScene();
	}
	DrawFade();
}
SCENE_ID ChangeScene(SCENE_ID id)
{
	g_nNextID = id;
	return g_nID;

}
Controller* GetController()
{
	return &Con;
}
