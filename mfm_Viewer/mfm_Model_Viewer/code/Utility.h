#pragma once
#include "DrawData.h"
class Utility
{
public:
	Utility();
	~Utility();
	static int Gen_to_intPos(D3DXVECTOR2 Pos);
	static int Gen_to_intPos(D3DXVECTOR3 Pos);
};
