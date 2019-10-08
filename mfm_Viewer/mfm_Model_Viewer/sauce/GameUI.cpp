#include "Include.h"


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

Controller GameControl;


void InitGameUI()
{
}
void UnInitGameUI()
{
}
void UpdateGameUI()
{
	// 決定
	if (GetKeyboardTrigger(KEY_OK) || GameControl.GetTriggerButton(CNT_OK))
	{
		Fade(FADE_IN, D3DCOLOR_RGBA(0, 0, 0, 0));
		SetKeyboardActive(KEYBOARDOFF);
	}
}
void DrawGameUI()
{
}
