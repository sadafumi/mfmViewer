#ifndef _BULLET_H_
#define _BULLET_H_

#include "Include.h"

#define BULLET_MAX (2000)

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void CreateBullet(D3DXVECTOR3 Pos, D3DXVECTOR3 Mae);
bool IsBullet(int);
void DestroyBullet(int);

#endif //_BULLET_H_
