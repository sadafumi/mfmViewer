#include "HitBox.h"

bool JudgeSphere(SPHERE *ObjA, SPHERE *ObjB)
{
	D3DXVECTOR3 VecLen;
	VecLen.x = ObjA->pPosition->x - ObjB->pPosition->x;
	VecLen.y = ObjA->pPosition->y - ObjB->pPosition->y;
	VecLen.z = ObjA->pPosition->z - ObjB->pPosition->z;
	float fLen = D3DXVec3Length(&VecLen);
	if (fLen <= ObjA->Radius + ObjB->Radius )
	{
		return true;
	}
	return false;
}
//bool RayIntersect(float* Distance,  )
//{
	//BOOL boHit = FALSE;
	//D3DXMATRIX matWorld, matRotation;
	//D3DXVECTOR3 vecStart, vecEnd, vecDirection;

	//vecStart = pThingA->vecPosition;
	//vecEnd = D3DXVECTOR3(0, 0, 1);
	//D3DXMatrixRotationY(&matRotation, pThingA->fYaw);
	//D3DXVec3TransformCoord(&vecEnd, &vecEnd, &matRotation);
	//vecEnd += vecStart;
	//// �Ώۂ������Ă���ꍇ�ł��Ώۂ̃��[���h�s��̋t�s���p����ΐ��������C��������
	//D3DXMatrixTranslation(&matWorld, pThingB->vecPosition.x, pThingB->vecPosition.y, pThingB->vecPosition.z);
	//D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	//D3DXVec3TransformCoord(&vecStart, &vecStart, &matWorld);
	//D3DXVec3TransformCoord(&vecEnd, &vecEnd, &matWorld);

	//vecDirection = vecEnd - vecStart;
	//D3DXIntersect(pThingB->pMesh, &vecStart, &vecDirection, &boHit, NULL, NULL, NULL, pfDistance, NULL, NULL);
	//if (boHit)
	//{
	//	return TRUE;
	//}
	//return FALSE;

//}
