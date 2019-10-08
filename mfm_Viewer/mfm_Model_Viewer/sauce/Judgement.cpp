#include "Include.h"


//----------------------------------------------------------------------------------------------------------------------------------------------------------
//関数名　bool HitCircle(float x0, float y0, float r0, float x1, float y1, float r1)
//　ヒットボックス　円形
//	引数　float x0		ポイントAのX　
//	引数　float y0　	ポイントAのY
//	引数　float r0　	ポイントAのr
//	引数　float x1　	ポイントBのX
//	引数　float y1　	ポイントBのY
//	引数　float r1　	ポイントBのr
//
//	返り値　ポイントA＋ポイントBの半径＞ポイントAとポイントBの距離
//			小さい場合はTrue
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------
bool HitCircle(float x0, float y0, float r0, float x1, float y1, float r1)
{
	// x0 - x0 , y0 - y0 起点になるため０になった
	float x = x1 - x0;
	float y = y1 - y0;

	float l = x * x + y * y;

	return l < (r0 + r1) * (r0 + r1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//関数名　bool HItBox(float PosX0, float PosY0, int BoxWid0, int BoxHei0, float PosX1, float Posy1, int BoxWid1, int BoxHei1)
//　ヒットボックス　矩形
//　引数　float PosX0    
//  引数　float PosY0
//  引数　int   BoxWid0
//  引数　int   BoxHei0
//  引数　float PosX1
//  引数　float Posy1
//  引数　int   BoxWid1
//  引数　int   BoxHei1
//
//	返り値　ポイントA＋ポイントBの半径＞ポイントAとポイントBの距離
//			小さい場合はTrue
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------
bool HitBox(float PosX0, float PosY0, int BoxWid0, int BoxHei0, float PosX1, float PosY1, int BoxWid1, int BoxHei1)
{

	bool Judg1 = PosX0 < PosX1 + BoxWid1;
	bool Judg2 = PosY0 < PosY1 + BoxHei1;
	bool Judg3 = PosX0 + BoxWid0 > PosX1;
	bool Judg4 = PosY0 + BoxHei0 > PosY1;
	if(Judg4 && Judg3 && Judg2 && Judg1){return true;}
	return false;
}
