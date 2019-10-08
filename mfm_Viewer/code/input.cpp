//=============================================================================
//
// ���͏��� [input.cpp]
//
//=============================================================================

#include "DrawData.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	NUM_BOTTON_MAX			(8)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[
//#define DIRECTINPUT_VERSION (0x0800)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8			g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevMouse = NULL;					// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevJoystick = NULL;					// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

D3DXVECTOR3				g_aMouseStatePostion;
BYTE					g_aMouseState[NUM_BOTTON_MAX];
BYTE					g_aMouseStateTrigger[NUM_BOTTON_MAX];
BYTE					g_aMouseStateRelease[NUM_BOTTON_MAX];
BYTE					g_aMouseStateRepeat[NUM_BOTTON_MAX];
int						g_aMouseStateRepeatCnt[NUM_BOTTON_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

static XINPUT_STATE		state;
static bool KeyActive = true;

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance,HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);
	if(g_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if(FAILED( DirectInput8Create( hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	
	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	if(g_pInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if(FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���Ȃ�", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j�������厖
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//=============================================================================
// �}�E�X�̏�����
//=============================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "�}�E�X���Ȃ�", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j�������厖
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevMouse->Acquire();

	return S_OK;
}

//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void UninitMouse(void)
{
	if(g_pDevMouse != NULL)
	{// ���̓f�o�C�X(�}�E�X)�̊J��
		// �}�E�X�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevMouse->Unacquire();

		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	// ���͏����̏I������
	UninitInput();
}
//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	 // �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	UninitInput();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
		// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & ~aKeyState[nCnKey];

			// �L�[���s�[�g���𐶐�
			if(aKeyState[nCnKey])
			{
				if(g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if(g_aKeyStateRepeatCnt[nCnKey] == 1
					|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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

			// �L�[�v���X����ۑ�
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDevKeyboard->Acquire();
	}

}
//=============================================================================
// �L�[�{�[�h�̍X�V����
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
// �L�[�{�[�h�̃v���X��Ԃ��擾
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
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
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
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
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
// �L�[�{�[�h�̃����|�X��Ԃ��擾
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
// �L�[�{�[�h��ON��OFF
//=============================================================================
void SetKeyboardActive(bool active)
{
	KeyActive = active;
}