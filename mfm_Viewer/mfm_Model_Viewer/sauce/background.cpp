#include "background.H"


#define defaultPath (SUNSET)

BACKGROUNDMODELNUM NowModel;
static ModelPath filePath[] = 
{
	{ "resource\\model\\skydome\\CloudOcean.x"},
	{ "resource\\model\\skydome\\AngelHierarchy.x"},
	{ "resource\\model\\skydome\\Before the Storm.x"},
	{ "resource\\model\\skydome\\CloudCover.x"},
	{ "resource\\model\\skydome\\CloudyWeather.x"},
	{ "resource\\model\\skydome\\CrownTreeTop.x"},
	{ "resource\\model\\skydome\\darkNight.x"},
	{ "resource\\model\\skydome\\DayMoon&Mountain.x"},
	{ "resource\\model\\skydome\\DyaMoon.x"},
	{ "resource\\model\\skydome\\ForestIN.x"},
	{ "resource\\model\\skydome\\ForestIn2.x"},
	{ "resource\\model\\skydome\\ForestSky.x"},
	{ "resource\\model\\skydome\\FullMoonNight&Mountain.x"},
	{ "resource\\model\\skydome\\FullMoonNight&Mountain2.x"},
	{ "resource\\model\\skydome\\FullMoonNight.x"},
	{ "resource\\model\\skydome\\FullMoonNight2.x"},
	{ "resource\\model\\skydome\\lake.x"},
	{ "resource\\model\\skydome\\Moon.x" },
	{ "resource\\model\\skydome\\NeedleMoon.x" },
	{ "resource\\model\\skydome\\Prairie.x" },
	{ "resource\\model\\skydome\\RedMoon.x" },
	{ "resource\\model\\skydome\\RedSunset&Mountain.x" },
	{ "resource\\model\\skydome\\RedSunset.x" },
	{ "resource\\model\\skydome\\Sky&Mountain.x" },
	{ "resource\\model\\skydome\\SnowMountain.x" },
	{ "resource\\model\\skydome\\Sunset&Mountain.x" },
	{ "resource\\model\\skydome\\Sunset.x" },
	{ "resource\\model\\skydome\\SunsetMoon.x" },
	{ "resource\\model\\skydome\\TwilightSunset&Mountain.x" },
	{ "resource\\model\\skydome\\TwilightSunset.x" },
	{ "resource\\model\\skydome\\TyphoonEye.x" },
	{ "resource\\model\\skydome\\TyphoonEye2.x" },
	{ "resource\\model\\skydome\\UnknownPlanet.x" },
	{ "resource\\model\\skydome\\UnknownPlanet2.x" },
	{ "resource\\model\\skydome\\watwood.x" },
	{ "resource\\model\\skydome\\wonders.x" }
};

MESHDATA SkyDomeData;
RenderMesh *SkyDomeRender = NULL;
Camera TestCam;
D3DXMATRIX View;

void BackgroundInit(void)
{
	if(SkyDomeRender == NULL)
	{
		SkyDomeRender = new RenderMesh;
		CreateMesh(&SkyDomeData, filePath[defaultPath].fileName);
		SkyDomeRender->SetRendData(&SkyDomeData);
	}
}
void BackgroundUninit(void)
{
	if (SkyDomeRender != NULL)
	{
		SkyDomeData.Destroy();
		delete SkyDomeRender;
	}
}
void BackgroundUpdate(void)
{
	D3DXMATRIX mtxScaling;
	D3DXMatrixIdentity(&mtxScaling);
	D3DXMatrixScaling(&mtxScaling,8,8,8);
	SkyDomeRender->SetMtXView(View);
	SkyDomeRender->SetMtXWorld(mtxScaling);
}
void BackgroundDraw(void)
{
	SkyDomeRender->Draw();
}
void SetBackgroundView(D3DXMATRIX In)
{
	View = In;
}
BACKGROUNDMODELNUM BackgroundChange(BACKGROUNDMODELNUM Next)
{
	BACKGROUNDMODELNUM OldModel = Next;
	NowModel = Next;
	SkyDomeData.Destroy();
	CreateMesh(&SkyDomeData, filePath[NowModel].fileName);
	SkyDomeRender->SetRendData(&SkyDomeData);
	return OldModel;
}
