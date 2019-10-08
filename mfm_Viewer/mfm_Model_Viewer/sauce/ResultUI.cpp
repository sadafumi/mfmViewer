//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "Include.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// UI・テクスチャ
// タイトル用UI仮置き
#define TITLEUI1 ("resource\\Title\\titleUI_1.png")
#define TITLEUI2 ("resource\\Title\\titleUI_2.png")

#define MAX_RESULT_RANKING_UI	(3)	// 順位
#define MAX_RESULT_SELECT_UI	(1)	// 選択子
#define MAX_RESULT_HELP_UI	(1)	// ヘルプ

#define MAX_UI	(MAX_RESULT_RANKING_UI + MAX_RESULT_SELECT_UI + MAX_RESULT_HELP_UI)

// UI一括設定////////////////////////////////////////////////////////////////////////////////////
#define RANKING_SCALE_X	(0.8f)
#define RANKING_SCALE_Y	(0.25f)
/////////////////////////////////////////////////////////////////////////////////////////////////
#define KEY_OK			(DIK_RETURN)		// 決定       : [ ENTER ]キー
#define KEY_CANCEL		(DIK_BACKSPACE)		// キャンセル : [ BACKSPACE ]キー
#define KEY_UP			(DIK_W)				// ↑         : [ UP ]キー
#define KEY_DOWN		(DIK_S)				// ↓         : [ DOWN ]キー
#define KEY_RIGHT		(DIK_D)				// →         : [ RIGHT ]キー
#define KEY_LEFT		(DIK_A)				// ←         : [ LEFT ]キー

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VERTEXDATA ResultUIDATA[MAX_UI];
RenderUI* RankingUI;
RenderUI* RSelectUI;

//=============================================================================
// 初期化処理
//=============================================================================
void InitResultUI(void)
{
	// テクスチャ入力
	CreateMeshBoard(&ResultUIDATA[0], TITLEUI1);
	CreateMeshBoard(&ResultUIDATA[1], TITLEUI2);

	// メモリ確保
	RankingUI = new RenderUI[MAX_RESULT_RANKING_UI];
	RankingUI[0].SetRendData(&ResultUIDATA[0]);
	RankingUI[1].SetRendData(&ResultUIDATA[0]);
	RankingUI[2].SetRendData(&ResultUIDATA[0]);

	RSelectUI = new RenderUI[MAX_RESULT_SELECT_UI];
	RSelectUI[0].SetRendData(&ResultUIDATA[1]);
	//RSelectUI[1].SetRendData(&ResultUIDATA[1]);

	// 1位------------------------------------------
	RankingUI[0].SetMtXPos(D3DXVECTOR3(0.0f, 0.4f, NULL));
	RankingUI[0].SetMtXScale(D3DXVECTOR3(RANKING_SCALE_X, RANKING_SCALE_Y, NULL));
	// 2位------------------------------------------
	RankingUI[1].SetMtXPos(D3DXVECTOR3(-0.5f, 0.1f, NULL));
	RankingUI[1].SetMtXScale(D3DXVECTOR3(RANKING_SCALE_X, RANKING_SCALE_Y, NULL));
	// 3位------------------------------------------
	RankingUI[2].SetMtXPos(D3DXVECTOR3(0.5f, 0.1f, NULL));
	RankingUI[2].SetMtXScale(D3DXVECTOR3(RANKING_SCALE_X, RANKING_SCALE_Y, NULL));

	// 選択肢
	RSelectUI[0].SetMtXPos(D3DXVECTOR3(-0.65f, -0.4f, NULL));
	RSelectUI[0].SetMtXScale(D3DXVECTOR3(0.5f, 0.15f, NULL));
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultUI(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultUI(void)
{
	// 決定
	if (GetKeyboardTrigger(KEY_OK))
	{
		Fade(FADE_IN, D3DCOLOR_RGBA(0, 0, 0, 0));
		SetKeyboardActive(KEYBOARDOFF);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultUI(void)
{
	for (int i = 0; i < MAX_RESULT_RANKING_UI; i++)
	{
		RankingUI[i].Draw();
	}
	for (int i = 0; i < MAX_RESULT_SELECT_UI; i++)
	{
		RSelectUI[i].Draw();
	}
}
