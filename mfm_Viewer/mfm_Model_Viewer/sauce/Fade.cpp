#include "Include.h"


#define FADECOLORMASK (11111100)
#define FADERESOURCE ("resource\\fade.png")

static bool bFade = false;
static FADE_MODE g_nID = FADE_NONE;
static int i, g_nConut = 0;
static DWORD Val1, result;
static D3DCOLOR g_Color;
static VERTEXDATA FadeData;
static RenderUI *FadeRender;

void InitFade()
{
	CreateMeshBoard(&FadeData, FADERESOURCE);
	FadeRender = new RenderUI;
	FadeRender->SetRendData(&FadeData);
}
void UninitFade()
{
	delete FadeRender;
	FadeData.Destroy();
}
void UpdateFade()
{
	if(g_nID != FADE_NONE)
	{	
		if (g_nID == FADE_IN)
		{
			g_nConut += 1;
			if (g_nConut >= 255)
			{
				bFade = true;
				g_nConut = 255;
			}
		}
		if (g_nID == FADE_OUT)
		{
			g_nConut += -1;
			if (g_nConut <= 0)
			{
				bFade = true;
				g_nConut = 0;
			}
		}
		result = (Val1 & FADECOLORMASK) + (g_nConut << 6 * 4);
		g_Color = result;
		FadeRender->SetColor(g_Color);
	}
}
void DrawFade()
{
	if(g_nID != FADE_NONE)
	{
		//FadePolygon->SetPolygonMode(ANIMETION_FADE);
		//FadePolygon->SetPolygonColor(D3DCOLOR_RGBA((int)Red, (int)Green, (int)Blue, g_nConut));
		//FadePolygon->SetPolygonFadeColor(&g_ColorFade[0]);
		//FadePolygon->DrawPolygon(TEXTURE_FADE, 0, 0, SCREEN_WIDTH, SCREEN_HIEGTH);
		D3DXVECTOR3 Scale = D3DXVECTOR3(100,100,100);
		FadeRender->SetMtXScale(Scale);
		FadeRender->Draw();
	}
}
void Fade(FADE_MODE id, D3DCOLOR color)
{
	if (g_nID == FADE_NONE)
	{
		g_nID = id;
		Val1 = color;

		if (g_nID == FADE_IN)
		{
			g_nConut = 0;
		}
		if (g_nID == FADE_OUT)
		{
			g_nConut = 255;
		}
	}
}
bool IsFadeIN()
{
	if (bFade == true)
	{
		if(g_nID == FADE_IN)
		{
			g_nID = FADE_NONE;
			bFade = false;
			return true;
		}
	}
	return false;
}
bool IsFadeOUT()
{
	if (bFade == true)
	{
		if (g_nID == FADE_OUT)
		{
			g_nID = FADE_NONE;
			bFade = false;
			return true;
		}
	}
	return false;
}
