//=============================================================================
//
// 入力処理 [input.cpp]
//
//=============================================================================

#include "DrawData.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	NUM_BOTTON_MAX			(8)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター
//#define DIRECTINPUT_VERSION (0x0800)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8			g_pInput = NULL;					// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ
LPDIRECTINPUTDEVICE8	g_pDevMouse = NULL;					// 入力デバイス(マウス)へのポインタ
LPDIRECTINPUTDEVICE8	g_pDevJoystick = NULL;					// 入力デバイス(マウス)へのポインタ
BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

D3DXVECTOR3				g_aMouseStatePostion;
BYTE					g_aMouseState[NUM_BOTTON_MAX];
BYTE					g_aMouseStateTrigger[NUM_BOTTON_MAX];
BYTE					g_aMouseStateRelease[NUM_BOTTON_MAX];
BYTE					g_aMouseStateRepeat[NUM_BOTTON_MAX];
int						g_aMouseStateRepeatCnt[NUM_BOTTON_MAX];	// キーボードのリピートカウンタ

static XINPUT_STATE		state;
static bool KeyActive = true;

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance,HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);
	if(g_pInput == NULL)
	{
		// DirectInputオブジェクトの作成
		if(FAILED( DirectInput8Create( hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	
	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	if(g_pInput != NULL)
	{// DirectInputオブジェクトの開放
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if(FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがない", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）すごく大事
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//=============================================================================
// マウスの初期化
//=============================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "マウスがない", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）すごく大事
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	g_pDevMouse->Acquire();

	return S_OK;
}

//=============================================================================
// マウスの終了処理
//=============================================================================
void UninitMouse(void)
{
	if(g_pDevMouse != NULL)
	{// 入力デバイス(マウス)の開放
		// マウスへのアクセス権を開放(入力制御終了)
		g_pDevMouse->Unacquire();

		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	// 入力処理の終了処理
	UninitInput();
}
//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{// 入力デバイス(キーボード)の開放
	 // キーボードへのアクセス権を開放(入力制御終了)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// 入力処理の終了処理
	UninitInput();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
		// デバイスからデータを取得
	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & ~aKeyState[nCnKey];

			// キーリピート情報を生成
			if(aKeyState[nCnKey])
			{
				if(g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if(g_aKeyStateRepeatCnt[nCnKey] == 1
					|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						g_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						g_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCnKey] = 0;
				g_aKeyStateRepeat[nCnKey] = 0;
			}

			// キープレス情報を保存
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevKeyboard->Acquire();
	}

}
//=============================================================================
// キーボードの更新処理
//=============================================================================
void UpdateMouse(void)
{
	DIMOUSESTATE2 aMouseState;
	int i;
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &aMouseState)))
	{
		g_aMouseStatePostion.x = (float)aMouseState.lX;
		g_aMouseStatePostion.y = (float)aMouseState.lY;
		g_aMouseStatePostion.z = (float)aMouseState.lZ;

		for( i = 0 ; i < NUM_BOTTON_MAX ; i++ )
		{
			aMouseState.rgbButtons[i];
			
			g_aMouseStateTrigger[i] = (g_aMouseState[i] ^ aMouseState.rgbButtons[i]) & aMouseState.rgbButtons[i];
			g_aMouseStateRelease[i] = (g_aMouseState[i] ^ aMouseState.rgbButtons[i]) & ~aMouseState.rgbButtons[i];
			if(g_aMouseState[i])
			{
				if(g_aMouseStateRepeatCnt[i] < LIMIT_COUNT_REPEAT )
				{
					g_aMouseStateRepeatCnt[i]++;
					if(g_aMouseStateRepeatCnt[i] == 1|| g_aMouseStateRepeatCnt[i] >= LIMIT_COUNT_REPEAT )
					{
						g_aMouseStateRepeat[i] = aMouseState.rgbButtons[i];
					}
					else
					{
						g_aMouseStateRepeat[i] = 0;
					}
				}
			}
			else
			{
				g_aMouseStateRepeatCnt[i] = 0;

			}
			g_aMouseState[i];
			g_aMouseStateRepeat[NUM_BOTTON_MAX];
		}
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyState[nKey] & 0x80) ? true : false;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyStateRepeat[nKey] & 0x80) ? true: false;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;	
	}
	else
	{
		return false;
	}

}
//=============================================================================
// キーボードのON＆OFF
//=============================================================================
void SetKeyboardActive(bool active)
{
	KeyActive = active;
}