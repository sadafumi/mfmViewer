#include "InputKeyboard.h"

LPDIRECTINPUT8	Input::g_pInput;
LPDIRECTINPUTDEVICE8 InputKeyboard::g_pDevKeyboard;				// 入力デバイス(キーボード)へのポインタ	
BYTE InputKeyboard::g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
BYTE InputKeyboard::g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
BYTE InputKeyboard::g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
BYTE InputKeyboard::g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
int InputKeyboard::g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
bool InputKeyboard::KeyActive;

HRESULT InputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}
	// デバイスの作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがない", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}
	// 協調モードを設定（フォアグラウンド＆非排他モード）すごく大事
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}
	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();
	KeyActive = true;
	return S_OK;
}

void InputKeyboard::Uninit()
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

void InputKeyboard::Updata()
{
	BYTE aKeyState[NUM_KEY_MAX];
	// デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & ~aKeyState[nCnKey];

			// キーリピート情報を生成
			if (aKeyState[nCnKey])
			{
				if (g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if (g_aKeyStateRepeatCnt[nCnKey] == 1
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

bool InputKeyboard::GetKeyboardPress(int nKey)
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
bool InputKeyboard::GetKeyboardTrigger(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
	}
	else
	{
		return false;
	}
}
bool InputKeyboard::GetKeyboardRepeat(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
	}
	else
	{
		return false;
	}
}
bool InputKeyboard::GetKeyboardRelease(int nKey)
{
	if (KeyActive)
	{
		return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
	}
	else
	{
		return false;
	}
}
void InputKeyboard::SetKeyboardActive(bool Active)
{
	KeyActive = Active;
}
