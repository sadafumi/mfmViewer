#include "game.h"
#include "GameInclude.h"

void GameScene::Init()
{
	InitGameField();
	InitGameObject();
	InitGameUI();
}
void GameScene::UnInit()
{
	UnInitGameField();
	UnInitGameObject();
	UnInitGameUI();
}
void GameScene::Updata()
{
	UpdateGameField();
	UpdateGameObject();
	UpdateGameCamera();
	UpdateGameUI();
	if (IsFadeIN())
	{
		ChangeScene(SCENE_RESULT);
		Fade(FADE_OUT, D3DCOLOR_RGBA(0, 0, 0, 0));
	}
	if (IsFadeOUT())
	{
		SetKeyboardActive(KEYBOARDON);
	}
}
void GameScene::Draw()
{
	DrawGameField();
	DrawGameObject();
	DrawGameUI();
	DrawGameCamera();
}
