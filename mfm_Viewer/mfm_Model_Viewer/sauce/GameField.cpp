#include "Include.h"

#define MAX_FILED_MESH (5) 
#define FILEDTEXTURE ("resource\\Game\\Alloy_diamond_plate_pxr128.png")
#define WALLTEXTURE ("resource\\Game\\Standard_red_pxr128.png")


RenderVtxStrip *Field;
VERTEXDATA FILEDVertex;
VERTEXDATA WallVertex;

void InitGameField()
{
	Field = new RenderVtxStrip[MAX_FILED_MESH];
	CreateMeshField(&FILEDVertex , FILEDTEXTURE, 10, 10);
	CreateMeshField(&WallVertex , WALLTEXTURE, 10, 10);
	
	Field[0].SetRendData(&FILEDVertex);
	Field[1].SetRendData(&WallVertex);
	Field[2].SetRendData(&WallVertex);
	Field[3].SetRendData(&WallVertex);
	Field[4].SetRendData(&WallVertex);
}
void UnInitGameField()
{
	delete[] Field;
}
void UpdateGameField()
{
	static D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxScale;
	D3DXMATRIX mtxScale1;
	for (size_t i = 0; i < MAX_FILED_MESH; i++)
	{
		Field[i].SetMtXView(GetGameCamera());
	}

	D3DXMatrixScaling(&mtxScale, FieldSize, FieldSize, FieldSize);
	D3DXMatrixTranslation(&mtxWorld, FieldSizeHalf, 5, 0);
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	D3DXMatrixRotationZ(&mtxScale, D3DXToRadian(90));
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	Field[1].SetMtXWorld(mtxWorld);
	D3DXMatrixScaling(&mtxScale, FieldSize, FieldSize, FieldSize);
	D3DXMatrixTranslation(&mtxWorld, -FieldSizeHalf, 5, 0);
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	D3DXMatrixRotationZ(&mtxScale, D3DXToRadian(-90));
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	Field[2].SetMtXWorld(mtxWorld);
	D3DXMatrixScaling(&mtxScale, FieldSize, FieldSize, FieldSize);
	D3DXMatrixTranslation(&mtxWorld, 0, 5, FieldSizeHalf);
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	D3DXMatrixRotationZ(&mtxScale1, D3DXToRadian(90));
	D3DXMatrixRotationX(&mtxScale, D3DXToRadian(-90));
	D3DXMatrixMultiply(&mtxScale, &mtxScale, &mtxScale1);
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	Field[3].SetMtXWorld(mtxWorld);
	D3DXMatrixScaling(&mtxScale, FieldSize, FieldSize, FieldSize);
	D3DXMatrixTranslation(&mtxWorld, 0, 5, -FieldSizeHalf);
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	D3DXMatrixRotationZ(&mtxScale1, D3DXToRadian(90));
	D3DXMatrixRotationX(&mtxScale, D3DXToRadian(90));
	D3DXMatrixMultiply(&mtxScale, &mtxScale, &mtxScale1);
	D3DXMatrixMultiply(&mtxWorld, &mtxScale, &mtxWorld);
	Field[4].SetMtXWorld(mtxWorld);
}
void DrawGameField()
{
	//Field[0].Draw();
	for (size_t i = 0; i < MAX_FILED_MESH; i++)
	{
		Field[i].Draw();
	}
}
