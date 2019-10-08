#include "Utility.h"



Utility::Utility()
{
}


Utility::~Utility()
{
}

int Utility::Gen_to_intPos(D3DXVECTOR2 Pos)
{
	int ReturnKey;
	char buf[255];

	sprintf(buf, "%d%d", int(Pos.x + 1), int(Pos.y + 1));
	sscanf(buf, "%d", &ReturnKey);

	return ReturnKey;
}

int Utility::Gen_to_intPos(D3DXVECTOR3 Pos)
{
	int ReturnKey;
	char buf[255];

	sprintf(buf, "%d%d%d", int(Pos.x + 1), int(Pos.y + 1), int(Pos.z + 1));
	sscanf(buf, "%d", &ReturnKey);

	return ReturnKey;
}
