#include "Include.h"

typedef struct
{
	VERTEX3D XY; //X��X�@Y��Y
	VERTEX3D WH; //X��W�@Y��H
}POS;

typedef struct
{
	POS Pos;
	POS Color[4];//xy�ɐԂƃO���[���@wh�ɐƃ�
	int Tex
}DRAW;



