//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "Include.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================

void SelectScene::Init()
{
	SelectGarageInit();
	InitSelectUI();
}

//=============================================================================
// 終了処理
//=============================================================================
void SelectScene::UnInit()
{
	SelectGarageUninit();
	UninitSelectUI();
}

//=============================================================================
// 更新処理
//=============================================================================
void SelectScene::Updata()
{
	UpdateSelectCamera();
	SelectGarageUpadate();
	UpdateSelectUI();
	if (IsFadeIN())
	{
		ChangeScene(SCENE_GAME);		// 選択画面へ
		Fade(FADE_OUT, D3DCOLOR_RGBA(0, 0, 0, 0));
	}
	if (IsFadeOUT())
	{
		SetKeyboardActive(KEYBOARDON);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SelectScene::Draw()
{
	SelectGarageDraw();
	DrawSelectUI();
}
