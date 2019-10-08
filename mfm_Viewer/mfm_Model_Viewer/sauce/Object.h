#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <d3dx9.h>  

struct SPHERE
{
	D3DXVECTOR3	    *pPosition;
	float			Radius;
};
struct CAPSULE
{
	D3DXVECTOR3	    *pPosition;
};
struct BOX
{
	D3DXVECTOR3	    *pPosition;
	float			High;
	float			Widht;
	float			Depth;
};
struct Vecter3
{
	D3DXVECTOR3 Vec;
};


//class Position
//{
//public:
//	D3DXVECTOR3 GetPos();
//protected:
//	D3DXVECTOR3 Pos;
//};
//
//class Moving
//{
//public:
//	D3DXVECTOR3 GetMov();
//protected:
//	D3DXVECTOR3 Mov;
//};
//class FrontVec
//{
//public:
//	D3DXVECTOR3 GetFrontVec();
//protected:
//	D3DXVECTOR3 Front;
//};
//class Scaleing
//{
//public:
//	D3DXVECTOR3 GetScaleing();
//protected:
//	D3DXVECTOR3 Scale;
//};


class Object
{
public:
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetMoving();
	D3DXVECTOR3 GetFrontVec();
	D3DXVECTOR3 GetScaleing();
	D3DXVECTOR3 GetRoto();
	SPHERE GetSphereHitBox();
protected:
	Vecter3 Pos;
	Vecter3 Moving;
	Vecter3 FrontVec;
	Vecter3 Scaleing;
	Vecter3 Roto;
	SPHERE spHitbox;
};
#endif//__OBJECT_H__
