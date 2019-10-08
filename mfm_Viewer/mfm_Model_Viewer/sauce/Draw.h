#include "Include.h"

typedef struct
{
	VERTEX3D XY; //XにX　YにY
	VERTEX3D WH; //XにW　YにH
}POS;

typedef struct
{
	POS Pos;
	POS Color[4];//xyに赤とグリーン　whに青とα
	int Tex
}DRAW;



