#include "Object.h"

D3DXVECTOR3 Object::GetPos()
{
	return this->Pos.Vec;
}
D3DXVECTOR3 Object::GetMoving()
{
	return this->Moving.Vec;
}
D3DXVECTOR3 Object::GetFrontVec()
{
	return this->FrontVec.Vec;
}
D3DXVECTOR3 Object::GetScaleing()
{
	return this->Scaleing.Vec;
}
D3DXVECTOR3 Object::GetRoto()
{
	return this->Roto.Vec;
}
SPHERE Object::GetSphereHitBox()
{
	return this->spHitbox;
}
