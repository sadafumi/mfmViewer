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
			// DirectInput�I�u�W�F�N�g�̍쐬
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
		{// DirectInput�I�u�W�F�N�g�̊J��
			g_pInput->Release();
			g_pInput = NULL;
		}
	};
protected:
	static LPDIRECTINPUT8	g_pInput;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
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
	static LPDIRECTINPUTDEVICE8	g_pDevKeyboard;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^	
	static BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
	static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
	static BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	static int					g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
	static bool KeyActive;

};

#endif//__INPUTKEYBOARD_H__