#include "Include.h"

// UI・テクスチャ
#define TITLEUI1 ("resource\\Title\\titleUI_1.png")
#define TITLEUI2 ("resource\\Title\\titleUI_2.png")

#define MAX_TITLE_LOGO_UI	(1)	// タイトルロゴ
#define MAX_TITLE_SELECT_UI	(3)	// 選択子
#define MAX_TITLE_HELP_UI	(1)	// ヘルプ

#define MAX_UI		(MAX_TITLE_LOGO_UI + MAX_TITLE_SELECT_UI + MAX_TITLE_HELP_UI)

// UI一括設定////////////////////////////////////////////////////////////////////////////////////
#define SELECT_SPEED		( 0.4f ) // 選択された時の変化速度

// ロゴ部分
#define TITLELOGO_COLOR   D3DCOLOR_ARGB(255, 255, 0, 0)
#define TITLELOGO_SCALE_X (  1.2f)
#define TITLELOGO_SCALE_Y ( 0.25f)
#define TITLELOGO_POS_X   ( -0.4f)
#define TITLELOGO_POS_Y   ( 0.45f)

// 選択肢部分
#define SELECTER_NONECOLOR   D3DCOLOR_RGBA(255, 255, 255, 255)	// 非選択時の色
#define SELECTER_NONESCALE_X ( 0.65f)						// 非選択時の大きさ
#define SELECTER_NONESCALE_Y ( 0.12f)						// 非選択時の大きさ
#define SELECTER_NONEPOS_X   ( -0.60f)
#define SELECTER_NONEPOS_Y   (  0.0f)
#define SELECTER_COLOR       D3DCOLOR_RGBA(255, 0, 0, 255)	// 選択時の色
#define SELECTER_SCALE_X     (  0.8f)						// 選択時の大きさ
#define SELECTER_SCALE_Y     ( 0.15f)						// 選択時の大きさ
#define SELECTER_POS_X       ( -0.45f)
#define SELECTER_POS_Y       ( -0.1f)
#define SELECTER_POS_DIFF    (  0.2f)	// 選択肢ごとの間隔

// ヘルプ部分
#define HELP_COLOR   D3DCOLOR_ARGB(255, 255, 0, 0)
#define HELP_SCALE_X (  0.8f)
#define HELP_SCALE_Y ( 0.15f)
#define HELP_POS_X   ( -0.4f)
#define HELP_POS_Y   ( 0.45f)
/////////////////////////////////////////////////////////////////////////////////////////////////

// 入力マクロ テンプレート
// キーボード入力
#define KEY_OK			(DIK_RETURN)		// 決定       : [ ENTER ]キー
#define KEY_CANCEL		(DIK_BACKSPACE)		// キャンセル : [ BACKSPACE ]キー
#define KEY_UP			(DIK_W)				// ↑         : [ UP ]キー
#define KEY_DOWN		(DIK_S)				// ↓         : [ DOWN ]キー
#define KEY_RIGHT		(DIK_D)				// →         : [ RIGHT ]キー
#define KEY_LEFT		(DIK_A)				// ←         : [ LEFT ]キー
// コントローラー入力
#define CNT_OK			(XINPUT_GAMEPAD_B)			// 決定       : [ B ]ボタン
#define CNT_CANCEL		(XINPUT_GAMEPAD_A)			// キャンセル : [ A ]ボタン
#define CNT_UP			(XINPUT_GAMEPAD_DPAD_UP)	// ↑         : 十字[ ↑ ]ボタン
#define CNT_DOWN		(XINPUT_GAMEPAD_DPAD_DOWN)	// ↓         : 十字[ ↓ ]ボタン
#define CNT_RIGHT		(XINPUT_GAMEPAD_DPAD_RIGHT)	// →         : 十字[ → ]ボタン
#define CNT_LEFT		(XINPUT_GAMEPAD_DPAD_LEFT)	// ←         : 十字[ ← ]ボタン

// 選択肢
#define GAMESTART	( 0 )
#define OPTION		( 1 )
#define GAMEEND		( 2 )

// 変数宣言
RenderUI  *TitleUI;
RenderUI  *SelectUI;
VERTEXDATA TitleUIDATA[MAX_UI];
Controller TitleControl;

// 選択管理
short Selecter = 0;

void TitleUIInit(void)
{
	short Selecter = 0;

	// テクスチャ入力
	CreateMeshBoard(&TitleUIDATA[0], TITLEUI1);
	CreateMeshBoard(&TitleUIDATA[1], TITLEUI2);

	// メモリ確保
	TitleUI = new RenderUI[MAX_TITLE_LOGO_UI];
	TitleUI[0].SetRendData(&TitleUIDATA[0]);

	SelectUI = new RenderUI[MAX_TITLE_SELECT_UI];
	SelectUI[0].SetRendData(&TitleUIDATA[1]);
	SelectUI[1].SetRendData(&TitleUIDATA[1]);
	SelectUI[2].SetRendData(&TitleUIDATA[1]);

	// タイトルロゴ
	TitleUI[0].SetMtXPos(D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, NULL));
	TitleUI[0].SetMtXScale(D3DXVECTOR3(TITLELOGO_SCALE_X, TITLELOGO_SCALE_Y, NULL));
	// ゲームスタート--------------------------------------
	SelectUI[0].SetMtXPos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y + SELECTER_POS_DIFF, NULL));
	SelectUI[0].SetMtXScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	//オプション------------------------------------------
	SelectUI[1].SetMtXPos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y, NULL));
	SelectUI[1].SetMtXScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	//ゲーム終了------------------------------------------
	SelectUI[2].SetMtXPos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y - SELECTER_POS_DIFF, NULL));
	SelectUI[2].SetMtXScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
}
void TitleUIUninit(void)
{
	delete[] TitleUI;
	delete[] SelectUI;
	TitleUIDATA[0].Destroy();
	TitleUIDATA[1].Destroy();
}
void TitleUIUpdate(void)
{
	// 操作 : キーボード===============================================================
	{
		// 選択
		if (GetKeyboardTrigger(KEY_UP) || TitleControl.GetTriggerButton(CNT_UP))
		{
			Selecter--;
			if (Selecter < 0)Selecter = 2;
		}
		if (GetKeyboardTrigger(KEY_DOWN) || TitleControl.GetTriggerButton(CNT_DOWN))
		{
			Selecter++;
			if (Selecter > 2)Selecter = 0;
		}

		// 決定
		if (GetKeyboardTrigger(KEY_OK) || TitleControl.GetTriggerButton(CNT_OK))
		{
			if (Selecter == GAMESTART) 
			{
				Fade(FADE_IN, D3DCOLOR_RGBA(0,0,0,0));
				SetKeyboardActive(KEYBOARDOFF);
			}		// 選択画面へ
			if (Selecter == OPTION) 
			{
				//ChangeScene(SCENE_RESULT);	// オプション画面へ
				//シーンせず直接オプションメニューを開く
			}
			if (Selecter == GAMEEND)
			{
				PostQuitMessage(WM_QUIT);
			}
		}
		if (GetKeyboardTrigger(KEY_DOWN))
		{

		}
	}
	//================================================================================

	// タイトルロゴ
	TitleUI[0].SetColor(TITLELOGO_COLOR);

	// 選択画面
	if (Selecter == 0)
	{
		SelectUI[0].SetMovePos(D3DXVECTOR3(SELECTER_POS_X, SELECTER_NONEPOS_Y + SELECTER_POS_DIFF, NULL));
		SelectUI[0].SetMoveScale(D3DXVECTOR3(SELECTER_SCALE_X, SELECTER_SCALE_Y, NULL));
		SelectUI[0].SetColor(SELECTER_COLOR);
	}
	else
	{
		SelectUI[0].SetMovePos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y + SELECTER_POS_DIFF, NULL));
		SelectUI[0].SetMoveScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	}
	//  オプション画面
	if (Selecter == 1)
	{
		SelectUI[1].SetMovePos(D3DXVECTOR3(SELECTER_POS_X, SELECTER_NONEPOS_Y, NULL));
		SelectUI[1].SetMoveScale(D3DXVECTOR3(SELECTER_SCALE_X, SELECTER_SCALE_Y, NULL));
		SelectUI[1].SetColor(SELECTER_COLOR);
	}
	else
	{
		SelectUI[1].SetMovePos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y, NULL));
		SelectUI[1].SetMoveScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	}
	// 終了
	if (Selecter == 2)
	{
		SelectUI[2].SetMovePos(D3DXVECTOR3(SELECTER_POS_X, SELECTER_NONEPOS_Y - SELECTER_POS_DIFF, NULL));
		SelectUI[2].SetMoveScale(D3DXVECTOR3(SELECTER_SCALE_X, SELECTER_SCALE_Y, NULL));
		SelectUI[2].SetColor(SELECTER_COLOR);
	}
	else
	{
		SelectUI[2].SetMovePos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y - SELECTER_POS_DIFF, NULL));
		SelectUI[2].SetMoveScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	}
	//----------------------------------------------------

	//UI移動
	for (size_t i = 0; i < MAX_TITLE_SELECT_UI; i++)
	{
		SelectUI[i].Move(SELECT_SPEED);
	}
}
void TitleUIDraw(void)
{
	for (size_t i = 0; i < MAX_TITLE_LOGO_UI; i++)
	{
		TitleUI[i].Draw();
	}
	for (size_t i = 0; i < MAX_TITLE_SELECT_UI; i++)
	{
		SelectUI[i].Draw();
	}
}
