
#ifndef _GAMECAMERA_H_
#define _GAMECAMERA_H_

#include "DrawData.h"

void InitGameCamera();
void UnInitGameCamera();
void UpdateGameCamera();
void DrawGameCamera();
D3DXMATRIX GetGameCamera();
D3DXVECTOR3 GetCameraVec();


#endif//_GAMECAMERA_H_
