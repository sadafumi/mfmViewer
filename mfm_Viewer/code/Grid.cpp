#include "main.h"
#include "Grid.h"
#include "Input.h"
#include "Camera.h"
#include "CreateData.h"

//#define DEFAULTVIVE 　(120)
//#define DEFAULTNEAR 　(0.1)
//#define DEFAULTFUR　　(1000)
#define MAXGRIDLINE  (22) 
#define GRIDXCOLOR D3DCOLOR_RGBA(255, 0, 0, 255)
#define GRIDCENCOLOR D3DCOLOR_RGBA(255, 255, 0, 255)
#define GRIDYCOLOR D3DCOLOR_RGBA(0, 0, 255, 255)
#define GRIDSIZE (10)

static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX g_mtxProj;
static LPDIRECT3DVERTEXBUFFER9 g_pVetTexBuffer = NULL;

void Grid::Init()
{
	int i; 
	std::vector<VERTEXD> vtx;
	vtx.resize(MAXGRIDLINE + MAXGRIDLINE);
	for (i = 0; i < MAXGRIDLINE / 2; i++)
	{
		vtx[i + i] = { D3DXVECTOR4((float)(-(GRIDSIZE / 2)), 0.0f,(float)(i - (GRIDSIZE / 2)),0), GRIDXCOLOR };
		vtx[i + i + 1] = { D3DXVECTOR4((float)(GRIDSIZE / 2), 0.0f,(float)(i - (GRIDSIZE / 2)),0), GRIDXCOLOR };
		vtx[MAXGRIDLINE + i + i] = { D3DXVECTOR4((float)(i - (GRIDSIZE / 2)), 0.0f, (float)(-(GRIDSIZE / 2)),0),     GRIDYCOLOR };
		vtx[MAXGRIDLINE + i + i + 1] = { D3DXVECTOR4((float)(i - (GRIDSIZE / 2)), 0.0f,  (float)((GRIDSIZE / 2)),0), GRIDYCOLOR };

	}
	vtx[10] = { D3DXVECTOR4(-(GRIDSIZE / 2), 0.0f,0,0), GRIDCENCOLOR };
	vtx[11] = { D3DXVECTOR4((GRIDSIZE / 2), 0.0f,0,0), GRIDCENCOLOR };
	vtx[MAXGRIDLINE + 10] = { D3DXVECTOR4(0, 0.0f, -(GRIDSIZE / 2),0), GRIDCENCOLOR };
	vtx[MAXGRIDLINE + 11] = { D3DXVECTOR4(0, 0.0f,  (GRIDSIZE / 2),0), GRIDCENCOLOR };
	Create::VerTex_Line(&data,&vtx);
	Render.SetRendData(&data, MAXGRIDLINE);
}

void Grid::Uninit()
{
}

void Grid::Updata()
{
	Render.SetMtXView(Camera::GetViewMtx());
}

void Grid::Draw()
{
	Render.Draw();
}
