#include "Include.h"


// ���̓}�N�� �e���v���[�g
// �L�[�{�[�h����
#define KEY_OK			(DIK_RETURN)		// ����       : [ ENTER ]�L�[
#define KEY_CANCEL		(DIK_BACKSPACE)		// �L�����Z�� : [ BACKSPACE ]�L�[
#define KEY_UP			(DIK_W)				// ��         : [ UP ]�L�[
#define KEY_DOWN		(DIK_S)				// ��         : [ DOWN ]�L�[
#define KEY_RIGHT		(DIK_D)				// ��         : [ RIGHT ]�L�[
#define KEY_LEFT		(DIK_A)				// ��         : [ LEFT ]�L�[
// �R���g���[���[����
#define CNT_OK			(XINPUT_GAMEPAD_B)			// ����       : [ B ]�{�^��
#define CNT_CANCEL		(XINPUT_GAMEPAD_A)			// �L�����Z�� : [ A ]�{�^��
#define CNT_UP			(XINPUT_GAMEPAD_DPAD_UP)	// ��         : �\��[ �� ]�{�^��
#define CNT_DOWN		(XINPUT_GAMEPAD_DPAD_DOWN)	// ��         : �\��[ �� ]�{�^��
#define CNT_RIGHT		(XINPUT_GAMEPAD_DPAD_RIGHT)	// ��         : �\��[ �� ]�{�^��
#define CNT_LEFT		(XINPUT_GAMEPAD_DPAD_LEFT)	// ��         : �\��[ �� ]�{�^��

Controller GameControl;


void InitGameUI()
{
}
void UnInitGameUI()
{
}
void UpdateGameUI()
{
	// ����
	if (GetKeyboardTrigger(KEY_OK) || GameControl.GetTriggerButton(CNT_OK))
	{
		Fade(FADE_IN, D3DCOLOR_RGBA(0, 0, 0, 0));
		SetKeyboardActive(KEYBOARDOFF);
	}
}
void DrawGameUI()
{
}
