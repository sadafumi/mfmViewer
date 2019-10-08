#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "Include.h"


void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void CreateExplosion(D3DXVECTOR3 Pos);
bool IsExplosion(int);
void DestroyExplosion(int);

#endif //_EXPLOSION_H_
