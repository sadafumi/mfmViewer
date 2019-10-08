#pragma once

//-----------------------------------------------------------------------------
// 制御系(ヘッダ)			　　
//-----------------------------------------------------------------------------
#ifndef _JUDGEMEANT_H_
#define _JUDGEMEANT_H_

//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
#include "Include.h"

//ぶつかったか
bool HitCircle(float x0, float y0, float r0, float x1, float y1, float r1);
bool HitBox(float PosX0,float PosY0,int BoxWid0,int BoxHei0, float PosX1, float Posy1, int BoxWid1, int BoxHei1);

#endif //_JUDGEMEANT_H_
