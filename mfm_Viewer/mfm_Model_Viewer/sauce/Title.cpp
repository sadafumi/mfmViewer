#include "Title.h"
#include "TitleInclude.h"
#include "Fade.h"

void TitleScene::Init()
{
	TitleUIInit();
}
void TitleScene::UnInit()
{
	TitleUIUninit();
}
void TitleScene::Updata()
{
	TitleCameraUpdate();
	TitleUIUpdate();
	if (IsFadeIN())
	{
		ChangeScene(SCENE_SELECT);
		Fade(FADE_OUT, D3DCOLOR_RGBA(0, 0, 0, 0));
	}
	if (IsFadeOUT())
	{
		SetKeyboardActive(KEYBOARDON);
	}
}
void TitleScene::Draw()
{
	TitleUIDraw();
}
