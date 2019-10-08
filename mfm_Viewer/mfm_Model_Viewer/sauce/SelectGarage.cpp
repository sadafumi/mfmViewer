#include "SelectGarage.h"
#include "SelectCamera.h"

#define SELECTBACK1	"resource\\model\\garage_body.x"
#define SELECTBACK2	"resource\\model\\garage_door_left.x"
#define SELECTBACK3	"resource\\model\\garage_door_right.x"
#define BACKGROUND	(3)

D3DXMATRIX  mtxWorld;
MESHDATA    SelectData[BACKGROUND];
RenderMesh* SelectBackground;

void SelectGarageInit() 
{
	CreateMesh(&SelectData[0], SELECTBACK1);
	CreateMesh(&SelectData[1], SELECTBACK2);
	CreateMesh(&SelectData[2], SELECTBACK3);

	//==========================================================================
	// ライトの設定
	//==========================================================================
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDir(-1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	// ディレクショナルライト設定
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	// アンビエントライト設定
	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;
	GetD3DDevice()->SetLight(0, &light); // ライト番号0~3
	GetD3DDevice()->LightEnable(0, TRUE);   // 0番ライトオン

	SelectBackground = new RenderMesh[BACKGROUND];
	SelectBackground[0].SetRendData(&SelectData[0]);
	SelectBackground[0].SetLight(light);
	SelectBackground[1].SetRendData(&SelectData[1]);
	SelectBackground[1].SetLight(light);
	SelectBackground[2].SetRendData(&SelectData[2]);
	SelectBackground[2].SetLight(light);
}

void SelectGarageUninit()
{
	delete[] SelectBackground;
	SelectData->Destroy(); 
}

void SelectGarageUpadate()
{
	D3DXMatrixTranslation(&mtxWorld, 20, 20, 20);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorld);
	SelectBackground[0].SetMtXWorld(mtxWorld);
	SelectBackground[0].SetMtXView(GatSelectCamera());
	D3DXMatrixTranslation(&mtxWorld, 20, 20, 20);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorld);
	SelectBackground[1].SetMtXView(GatSelectCamera());
	SelectBackground[1].SetMtXWorld(mtxWorld);
	D3DXMatrixTranslation(&mtxWorld, 20, 20, 20);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorld);
	SelectBackground[2].SetMtXView(GatSelectCamera());
	SelectBackground[2].SetMtXWorld(mtxWorld);
}

void SelectGarageDraw()
{
	for (int i = 0; i < BACKGROUND; i++)
	{
		SelectBackground[i].Draw();
	}
}
