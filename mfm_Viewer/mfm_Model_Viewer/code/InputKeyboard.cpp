#include "InputKeyboard.h"

LPDIRECTINPUT8	Input::g_pInput;
LPDIRECTINPUTDEVICE8 InputKeyboard::g_pDevKeyboard;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^	
BYTE InputKeyboard::g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
BYTE InputKeyboard::g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
BYTE InputKeyboard::g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
BYTE InputKeyboard::g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
int InputKeyboard::g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
bool InputKeyboard::KeyActive;

HRESULT InputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}
	// �f�o�C�X�̍쐬
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���Ȃ�", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}
	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j�������厖
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();
	KeyActive = true;
	return S_OK;
}

void InputKeyboard::Uninit()
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

void InputKeyboard::Updata()
{
	BYTE aKeyState[NUM_KEY_MAX];
	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & ~aKeyState[nCnKey];

			// �L�[���s�[�g���𐶐�
			if (aKeyState[nCnKey])
			{
				if (g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if (g_aKeyStateRepeatCnt[nCnKey] == 1
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
