#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "NonCopy.h"
#include "DrawData.h"

struct Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

//Deviceを隠蔽するためのクラス
class DeviceHider
{
public:
	static void SetDevice(LPDIRECT3DDEVICE9 in) { pDevice = in; };
	static void CreateScreenShots();
	static void DrawPrimitiveUp(D3DPRIMITIVETYPE type, int size, const void *pVertexStreamZeroData, int PrimitiveNum);
	static void DrawIndexedPrimitive(D3DPRIMITIVETYPE type, int VertexSize, int PrimitiveNum) ;
	static void DrawPrimitive(D3DPRIMITIVETYPE type, int PrimitiveNum) ;
	static void SetIndices(IDirect3DIndexBuffer9* pIndexData) ;
	static void SetStreamSource(IDirect3DVertexBuffer9* pStreamData, UINT Stride);
	static void SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) ;
	static void SetFVF(DWORD inFVF) ;
	static void SetMaterial(D3DMATERIAL9* Material) ;
	static void SetTexture(int index,IDirect3DBaseTexture9* pTexture) ;
	static void SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix) ;
	static void SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl);
	static void SetLight(DWORD index, D3DLIGHT9 light) ;
	static void LightEnable(DWORD index, BOOL Active) ;
	static bool CreateTexture(const char* Path, LPDIRECT3DTEXTURE9* out);
	static bool CreateTexture(LPDIRECT3DTEXTURE9* out,int x,int y);
	static void CreateVerTex(UINT Size, LPDIRECT3DVERTEXBUFFER9* out);
	static void CreateIndex(UINT Size, LPDIRECT3DINDEXBUFFER9* out);
	static HRESULT CreateVertexDeclaration(D3DVERTEXELEMENT9* pVertexElements, LPDIRECT3DVERTEXDECLARATION9* pDecl ) ;
	static HRESULT CreateEffect(const char* Path, LPD3DXEFFECT effect, LPD3DXBUFFER pCompilationErrors);
	static void CreateTextureBuffer(const char* Path, IDirect3DTexture9* texbuf);
	static D3DXVECTOR3* ChangeScreenToWorld( D3DXVECTOR3* out, IDirect3DDevice9* pDev,int sx,	int sy,	float z, D3DXMATRIX* view, D3DXMATRIX* proj);
	static HRESULT CreateVertexShader(DWORD* pD, IDirect3DVertexShader9** ppvsDh);
	static HRESULT CreatePixelShader(DWORD* pD, IDirect3DPixelShader9** pppsSh) ;
	static void SetVertexShader(DATA_TYPE::VERTEXSHADERDATA in);
	static void SetPixelShader(DATA_TYPE::PIXELSHADERDATA in) ;
	static void SetVertexShaderFloat(int RegisterNum,float* in ,int Count);
	static void SetPixelShaderFloat (int RegisterNum,float* in ,int Count);
	static void SetVertexShaderBool (int RegisterNum, bool* in ,int Count);
	static void SetPixelShaderBool  (int RegisterNum, bool* in ,int Count);
	static void SetVertexShaderInt  (int RegisterNum,  int* in ,int Count);
	static void SetPixelShaderInt   (int RegisterNum,  int* in, int Count);
	static void SetRenderTarget(int Index, IDirect3DSurface9 * Surface) ;
	static void GetRenderTarget(int Index, IDirect3DSurface9 ** Surface) ;
private:
	static LPDIRECT3DDEVICE9 pDevice;	//ダイレクト3Dデバイス
	
};

class  DirectX :NonCopy
{
public:
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void UnInit();
	void Clear();
	void Present();
	bool DrawBigin();
	void DrawEnd();
protected:
	LPDIRECT3D9			pD3D;			//ダイレクト3Dインターフェース
	LPDIRECT3DDEVICE9	pD3DDevice;	//ダイレクト3Dデバイス
};

#endif//__RENDERER_H__

