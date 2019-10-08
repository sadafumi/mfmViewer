#include "Grid.h"
#include "Camera.h"
#include "CreateData.h"

void Grid::Init()
{
	std::vector<VERTEX3D> vertex;
	int Max_Grid_Line = 22;
	int Grid_Size = 10;
	vertex.resize(Max_Grid_Line + Max_Grid_Line);

	for (int i = 0; i < Max_Grid_Line / 2; i++)
	{
		vertex[i + i].Pos = D3DXVECTOR3((float)(-(Grid_Size / 2)), 0.0f, (float)(i - (Grid_Size / 2)));
		vertex[i + i + 1].Pos = D3DXVECTOR3((float)(Grid_Size / 2), 0.0f,(float)(i - (Grid_Size / 2)));
		vertex[Max_Grid_Line + i + i].Pos = D3DXVECTOR3((float)(i - (Grid_Size / 2)), 0.0f, (float)(-(Grid_Size / 2)));
		vertex[Max_Grid_Line + i + i + 1].Pos = D3DXVECTOR3((float)(i - (Grid_Size / 2)), 0.0f,  (float)((Grid_Size / 2)));

	}
	vertex[10].Pos = D3DXVECTOR3(-(Grid_Size / 2), 0.0f,0);
	vertex[11].Pos = D3DXVECTOR3((Grid_Size / 2), 0.0f,0);
	vertex[Max_Grid_Line + 10].Pos = D3DXVECTOR3(0, 0.0f, -(Grid_Size / 2));
	vertex[Max_Grid_Line + 11].Pos = D3DXVECTOR3(0, 0.0f,  (Grid_Size / 2));

	Create::VerTex(&Grid_Vertex,NULL,&vertex);
	Render.SetRendData(&Grid_Vertex);
	Render.SetColor(D3DXVECTOR4(255.0f, 255.0f, 255.0f, 255.0f));
}

void Grid::Uninit()
{
	Grid_Vertex.Destroy();
}

void Grid::Update()
{
	Render.SetMtXView(Camera::GetViewMtx());
}

void Grid::Draw()
{
	Render.Draw();
}
