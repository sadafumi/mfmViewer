#include "Include.h"


void QuaternionRotation(D3DXQUATERNION *KeepRota , D3DXMATRIX *KeepMove, D3DXVECTOR3 In)
{
	D3DXQUATERNION qtYaw;
	D3DXQUATERNION qtPitch;
	D3DXQUATERNION qtRoll;
	D3DXQuaternionRotationAxis(&qtYaw, &D3DXVECTOR3(KeepMove->_21, KeepMove->_22, KeepMove->_23), In.y);
	D3DXQuaternionRotationAxis(&qtPitch, &D3DXVECTOR3(KeepMove->_11, KeepMove->_12, KeepMove->_13),In.x);
	D3DXQuaternionRotationAxis(&qtRoll, &D3DXVECTOR3(KeepMove->_31, KeepMove->_32, KeepMove->_33), In.z);
	D3DXQuaternionMultiply(KeepRota, KeepRota, &qtYaw);
	D3DXQuaternionMultiply(KeepRota, KeepRota, &qtPitch);
	D3DXQuaternionMultiply(KeepRota, KeepRota, &qtRoll);
	D3DXMatrixRotationQuaternion(KeepMove, KeepRota);
}