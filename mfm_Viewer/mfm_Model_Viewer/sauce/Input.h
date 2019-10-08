#pragma once

//-----------------------------------------------------------------------------
// 入力処理ヘッダ
//-----------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#define KEYBOARDON  (true)
#define KEYBOARDOFF (false)

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "Include.h"

//キーボードの初期化
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

//キーボードの開放
void UninitKeyboard(void);

//キーボードの更新
void UpdateKeyboard(void);

//キーボードが押されたか
bool GetKeyboardPress(int nKey);

//キーボードを押した瞬間
bool GetKeyboardTrigger(int nKey);

//キーボードが押され続けてる
bool GetKeyboardRepeat(int nKey);

//キーボードが離された
bool GetKeyboardRelease(int nKey);

//キーボードのON＆OFF
void SetKeyboardActive(bool);

#endif //_INPUT_H_
