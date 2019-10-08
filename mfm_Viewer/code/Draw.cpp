#include "Draw.h"
#include "Camera.h"
#include "CreateData.h"
#include "Render.h"
#include "Grid.h"
#define ModelPath "test.mfm"

MFMMESHDATA ModelData;
Rendermfm *Render;

void DrawInit()
{
	GridInit();
	CreateMFMMesh(&ModelData, ModelPath);
	Render = new Rendermfm;
	Render->SetRendData(&ModelData);
}
void DrawUninit()
{
	GridUninit();
	delete Render;
}
void DrawUpdata()
{
	CameraUpdate();
	GridUpdate();
	Render->SetMtXView(GetViewMtx());
}
void DrawDraw()
{
	GridDraw();
	Render->Draw();
}
