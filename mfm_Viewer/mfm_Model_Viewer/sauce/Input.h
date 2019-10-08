#pragma once

//-----------------------------------------------------------------------------
// ���͏����w�b�_
//-----------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#define KEYBOARDON  (true)
#define KEYBOARDOFF (false)

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "Include.h"

//�L�[�{�[�h�̏�����
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

//�L�[�{�[�h�̊J��
void UninitKeyboard(void);

//�L�[�{�[�h�̍X�V
void UpdateKeyboard(void);

//�L�[�{�[�h�������ꂽ��
bool GetKeyboardPress(int nKey);

//�L�[�{�[�h���������u��
bool GetKeyboardTrigger(int nKey);

//�L�[�{�[�h�������ꑱ���Ă�
bool GetKeyboardRepeat(int nKey);

//�L�[�{�[�h�������ꂽ
bool GetKeyboardRelease(int nKey);

//�L�[�{�[�h��ON��OFF
void SetKeyboardActive(bool);

#endif //_INPUT_H_
