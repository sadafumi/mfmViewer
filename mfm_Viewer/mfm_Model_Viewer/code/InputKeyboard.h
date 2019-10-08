#pragma once
#ifndef __INPUTKEYBOARD_H__
#define __INPUTKEYBOARD_H__

#include "DrawData.h"

class Input
{
public:
	static HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
	{
		UNREFERENCED_PARAMETER(hWnd);
		if (g_pInput == NULL)
		{
			// DirectInputオブジェクトの作成
			if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
			{
				return E_FAIL;
			}
		}
		return S_OK;
	};
	static void UninitInput(void)
	{
		if (g_pInput != NULL)
		{// DirectInputオブジェクトの開放
			g_pInput->Release();
			g_pInput = NULL;
		}
	};
protected:
	static LPDIRECTINPUT8	g_pInput;					// DirectInputオブジェクトへのポインタ
};

class InputKeyboard : public Input
{
public:
	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	static void Uninit();
	static void Updata();
	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);
	static bool GetKeyboardRepeat(int nKey);
	static bool GetKeyboardRelease(int nKey);
	static void SetKeyboardActive(bool Active);
private:
	static const int NUM_KEY_MAX = 256;
	static const int LIMIT_COUNT_REPEAT = 20;
	static LPDIRECTINPUTDEVICE8	g_pDevKeyboard;				// 入力デバイス(キーボード)へのポインタ	
	static BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
	static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
	static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
	static BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	static int					g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
	static bool KeyActive;

};

#endif//__INPUTKEYBOARD_H__