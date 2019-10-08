//-----------------------------------------------------------------------------
// �f�o�b�O�֐�
// AT12A242 �@��j���@
//-----------------------------------------------------------------------------
#include "debug.h"
#include "DrawData.h"
#include "main.h"


#define FVF_DEBUG ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )
#if defined(_DEBUG) || defined(DEBUG)
static LPD3DXFONT g_pFont = NULL;
typedef struct 
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
}DEBUG_VERTEX;

#endif


void InitDebugText()
{
#if defined(_DEBUG) || defined(DEBUG)
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL) { return; }
//	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,"Terminal",&g_pFont);
	D3DXCreateFont(
		pDevice,
		18, 1, 0, 0, FALSE,		//�����A���A�d���A�C�^���b�N(bool)
		SHIFTJIS_CHARSET,		//�����Z�b�g	�FSHIFT-JIS
		OUT_DEFAULT_PRECIS,		//�o�͂̏ꏊ	�F�f�t�H���g(���)
		DEFAULT_QUALITY,		//�N�I���e�B	�F�f�t�H���g
		DEFAULT_PITCH,			//�s�b�`		�F�f�t�H���g
		"Terminal",				//�t�H���g		�FTerminal
		&g_pFont);				//�Ǘ��|�C���^	�FDirectFont(�f�o�b�O�p)

#endif

}
void UnInitDebugText()
{
#if defined(_DEBUG) || defined(DEBUG)
	if(!g_pFont == NULL)
	{
		g_pFont->Release();
		g_pFont = 0;
	}
#endif

}

void DebugText(int x, int y, const char* pFormat, ...)
{
	x = x;
	y = y;
	pFormat = pFormat;
#if defined(_DEBUG) || defined(DEBUG)

	va_list argp;
	char strBuf[512];
	va_start(argp, pFormat);
	vsprintf_s(strBuf,512,pFormat,argp);
	va_end(argp);

	RECT rect =
	{
		x,y,
		SCREEN_WIDTH,
		SCREEN_HIEGTH
	};
	g_pFont->DrawText(NULL, strBuf,-1,&rect,DT_LEFT,0xffffffff);
#endif

}
void DebugPolgon(int n, float x, float y, float r)
{
	n = n;
	x = x;
	y = y;
	r = r;
#if defined(_DEBUG) || defined(DEBUG)
	const float C_R = D3DX_PI * 2 / n;
	int i;
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	DEBUG_VERTEX* pV = (DEBUG_VERTEX*)malloc(sizeof(DEBUG_VERTEX) * (n + 1));

	for(i = 0; i < (n  + 1); i++ )
	{
		pV[i].pos.x = x + cosf(C_R + i) * r;
		pV[i].pos.y = y + sinf(C_R + i) * r;
		pV[i].pos.z = 1.0f;
		pV[i].pos.w = 1.0f;
		pV[i].color = D3DCOLOR_ARGB(128,255,32,255);
	}

	pDevice->SetTexture(0,NULL);
	pDevice->SetFVF(FVF_DEBUG);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, n, pV, sizeof(DEBUG_VERTEX));
	free(pV);
#endif
}
