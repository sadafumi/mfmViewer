#include "Graphics.h"
#include <direct.h>
#include <string>

LPDIRECT3DDEVICE9 DeviceHider::pDevice;
bool DirectX::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	hInstance = hInstance;
	//LPDIRECT3D9			g_pD3D = NULL;			//ダイレクト3Dインターフェース
	//LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//ダイレクト3Dデバイス

	//ディスプレイモードの取得
	D3DDISPLAYMODE d3ddm;

	//デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS d3dpp;

	//ダイレクト3Dインタフェースの所得
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);//エンドユーザランタイムがないともらえない
	if (pD3D == NULL)
	{
		return false;
	}

	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));		//中身空にする
	d3dpp.BackBufferWidth = SCREEN_WIDTH;					//幅
	d3dpp.BackBufferHeight = SCREEN_HIEGTH;				//高さ
	d3dpp.BackBufferFormat = d3ddm.Format;					//色
	d3dpp.BackBufferCount = 1;							//	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//
	d3dpp.EnableAutoDepthStencil = TRUE;							//
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//D24_S8
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		//D24_S8
	d3dpp.Windowed = bWindow;						//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//

																//デバイスの生成
																//[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
	{
		MessageBox(hWnd, "デバイスの作成に失敗しました", "デバイス作成", MB_OK);
		return false;
	}

	//テクスチャの読み込み
	//αブレンドを行う
	//SRC　今書くもの。つまり
	//SRC_RGB * SRC_α + DEST_RGB * ( 1 - SRC_α )
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステート
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//サンプラーステートの設定
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	DeviceHider::SetDevice(this->pD3DDevice);
	return true;
}

void DirectX::UnInit()
{	
	if (pD3DDevice != NULL)
	{
		pD3DDevice->Release();
		pD3DDevice = NULL;
	}
	if (pD3D != NULL)
	{
		pD3D->Release();
		pD3D = NULL;
	}
}

void DirectX::Clear()
{
	//g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(19, 122, 127, 255), 1.0f, 0);//1.0fZバッファ19/122/127
	pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);//1.0fZバッファ19/122/127
}

void DirectX::Present()
{
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

bool DirectX::DrawBigin()
{
	return SUCCEEDED(pD3DDevice->BeginScene());
}

void DirectX::DrawEnd()
{
	pD3DDevice->EndScene();	
}

bool DeviceHider::CreateTexture(const char * Path, LPDIRECT3DTEXTURE9 * out)
{
	return FAILED(D3DXCreateTextureFromFile(pDevice, Path, out));
}
bool DeviceHider::CreateTexture(LPDIRECT3DTEXTURE9 * out, int x, int y)
{
	return FAILED(D3DXCreateTexture(pDevice, x, y, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, out));
}
void DeviceHider::CreateVerTex(UINT Size, LPDIRECT3DVERTEXBUFFER9 * out)
{
	pDevice->CreateVertexBuffer(Size, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, out, NULL);
}
void DeviceHider::CreateIndex(UINT Size, LPDIRECT3DINDEXBUFFER9 * out)
{
	pDevice->CreateIndexBuffer(Size, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, out, NULL);
}
HRESULT DeviceHider::CreateVertexDeclaration(D3DVERTEXELEMENT9 * pVertexElements, LPDIRECT3DVERTEXDECLARATION9 * pDecl)
{
	return pDevice->CreateVertexDeclaration(pVertexElements, pDecl);
}
HRESULT DeviceHider::CreateEffect(const char* Path, LPD3DXEFFECT effect, LPD3DXBUFFER pCompilationErrors)
{
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(pDevice, Path, NULL, NULL, D3DXSHADER_DEBUG, NULL, &effect, &pCompilationErrors);
	if (pCompilationErrors)
	{
		MessageBox(NULL, (char*)pCompilationErrors->GetBufferPointer(),
			"D3DXCreateEffectFromFile", 0);
		pCompilationErrors->Release();
	}
	if (FAILED(hr))
	{
		char err[124];
		sprintf(&err[0], "Shaderの取得「%s」に失敗しました", Path);
		MessageBox(NULL, &err[0], "Shaderの読み込みに失敗しました", MB_OK);
		return true;
	}
	//テクニックの妥当性テスト
	D3DXHANDLE hTech = effect->GetTechniqueByName("TextureTech");

	hr = effect->ValidateTechnique(hTech);

	if (FAILED(hr))
	{
		return true;
	}

	hTech = effect->GetTechniqueByName("NoTextureTech");

	hr = effect->ValidateTechnique(hTech);

	if (FAILED(hr))
	{
		return true;
	}
	return false;
}

void DeviceHider::CreateTextureBuffer(const char* Path, IDirect3DTexture9* texbuf)
{
	FILE *fp = NULL;

	int Height;
	int Widht;
	if ((fp = fopen(Path, "rb")) == NULL)//ファイルが開けるか検証
	{
		MessageBox(NULL, "LOADファイルを開けませんでした", "ロードエラー", MB_OK);
		return;//開けなかったら帰る
	}
	fread(&Height, sizeof(int), 1, fp);//高さを読み込み
	fread(&Widht, sizeof(int), 1, fp);//幅を読み込み
	D3DXCreateTexture(pDevice,Height, Widht, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texbuf);
	//texbuf->LockRect(0,);
	texbuf->UnlockRect(0);
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Widht; j++)
		{
			texbuf;
			//fread(&this->Data[i][j], sizeof(Color), 1, fp);//Color(Uchar4)を読み込む
		}
	}
	fclose(fp);//ファイルを閉じる
}

D3DXVECTOR3 * DeviceHider::ChangeScreenToWorld(D3DXVECTOR3 * out, IDirect3DDevice9 * pDev, int sx, int sy, float z, D3DXMATRIX * view, D3DXMATRIX * proj)
{
	// ビューポート行列を作成
	D3DXMATRIX vpMat;
	D3DXMatrixIdentity(&vpMat);

	D3DVIEWPORT9 vp;
	pDev->GetViewport(&vp);

	vpMat._11 = (float)vp.Width / 2;
	vpMat._22 = -1.0f * (float)(vp.Height / 2);
	vpMat._33 = (float)vp.MaxZ - vp.MinZ;
	vpMat._41 = (float)(vp.X + vp.Width / 2);
	vpMat._42 = (float)(vp.Y + vp.Height / 2);
	vpMat._43 = vp.MinZ;

	// スクリーン位置をワールドへ
	out->x = (float)sx;
	out->y = (float)sy;
	out->z = z;

	D3DXMATRIX invMat, inv_proj, inv_view;
	D3DXMatrixInverse(&invMat, 0, &vpMat);
	D3DXMatrixInverse(&inv_proj, 0, proj);
	D3DXMatrixInverse(&inv_view, 0, view);

	invMat *= inv_proj * inv_view;

	return D3DXVec3TransformCoord(out, out, &invMat);
}

HRESULT DeviceHider::CreateVertexShader(DWORD * pD, IDirect3DVertexShader9 ** ppvsDh)
{
	return pDevice->CreateVertexShader(pD, ppvsDh);
}
HRESULT DeviceHider::CreatePixelShader(DWORD * pD, IDirect3DPixelShader9 ** pppsSh)
{
	return pDevice->CreatePixelShader(pD, pppsSh);
}
void DeviceHider::SetVertexShader(DATA_TYPE::VERTEXSHADERDATA in)
{
	pDevice->SetVertexShader(in.pVertexShader);
}
void DeviceHider::SetPixelShader(DATA_TYPE::PIXELSHADERDATA in)
{
	pDevice->SetPixelShader(in.pPixelShader);
}
void DeviceHider::SetVertexShaderFloat(int RegisterNum, float * in, int Count)
{
	pDevice->SetVertexShaderConstantF(RegisterNum, in, Count);
}
void DeviceHider::SetPixelShaderFloat(int RegisterNum, float * in, int Count)
{
	pDevice->SetPixelShaderConstantF(RegisterNum, in, Count);
}
void DeviceHider::SetVertexShaderBool(int RegisterNum, bool * in, int Count)
{
	pDevice->SetVertexShaderConstantB(RegisterNum, (const BOOL*)in, Count);
}
void DeviceHider::SetPixelShaderBool(int RegisterNum, bool * in, int Count)
{
	pDevice->SetPixelShaderConstantB(RegisterNum, (const BOOL*)in, Count);
}
void DeviceHider::SetVertexShaderInt(int RegisterNum, int * in, int Count)
{
	pDevice->SetVertexShaderConstantI(RegisterNum, in, Count);
}
void DeviceHider::SetPixelShaderInt(int RegisterNum, int * in, int Count)
{
	pDevice->SetPixelShaderConstantI(RegisterNum, in, Count);
}
void DeviceHider::SetRenderTarget(int Index, IDirect3DSurface9 * Surface)
{
	pDevice->SetRenderTarget(Index, Surface);
}
void DeviceHider::GetRenderTarget(int Index, IDirect3DSurface9 ** Surface)
{
	pDevice->GetRenderTarget(Index, Surface);
}
void DeviceHider::CreateScreenShots()
{
	// バックバファの取得
	FILE *fp;
	LPDIRECT3DSURFACE9 pBackBuf;
	pDevice->GetRenderTarget(0, &pBackBuf);
	std::string Folder_Name("ScreenShots");
	fopen_s(&fp, Folder_Name.data(), "r");
	if (fp == NULL)
	{
		_mkdir(Folder_Name.data());
	}
	else 
	{
		fclose(fp);
	}
	std::string File_Extension(".png");

	std::string File_Name("ScreenShots\\screenshot");
	
	std::string Set_Name = File_Name + File_Extension;
	fopen_s(&fp, Set_Name.data() , "r");

	int count = 0;
	for (; fp != NULL;)
	{
		fclose(fp);
		count++;
		
		char buff[32];
		sprintf(buff, "(%d)", count);
		std::string Add(buff);

		Set_Name = File_Name + Add + File_Extension;
		fopen_s(&fp, Set_Name.data(), "r");
	}
	// スクショ出力
	D3DXSaveSurfaceToFile(Set_Name.data(), D3DXIFF_PNG, pBackBuf, NULL, NULL);

	// Get系で取得したサーフェイスはAddRefが呼ばれているので忘れずに解放する
	pBackBuf->Release();
}

void DeviceHider::DrawIndexedPrimitive(D3DPRIMITIVETYPE type, int VertexSize, int PrimitiveNum)
{
	pDevice->DrawIndexedPrimitive(type, 0, 0, VertexSize, 0, PrimitiveNum);
}

void DeviceHider::DrawPrimitiveUp(D3DPRIMITIVETYPE type,int size, const void *pVertexStreamZeroData, int PrimitiveNum)
{
	pDevice->DrawPrimitiveUP(type, size, pVertexStreamZeroData, PrimitiveNum);
}

void DeviceHider::DrawPrimitive(D3DPRIMITIVETYPE type, int PrimitiveNum)
{
	pDevice->DrawPrimitive(type, 0, PrimitiveNum);
}

void DeviceHider::SetIndices(IDirect3DIndexBuffer9 * pIndexData)
{
	pDevice->SetIndices(pIndexData);
}

void DeviceHider::SetStreamSource(IDirect3DVertexBuffer9 * pStreamData, UINT Stride)
{
	pDevice->SetStreamSource(0, pStreamData, 0, Stride);
}

void DeviceHider::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	pDevice->SetRenderState(State, Value);
}

void DeviceHider::SetFVF(DWORD inFVF)
{
	pDevice->SetFVF(inFVF);
}

void DeviceHider::SetMaterial(D3DMATERIAL9 * Material)
{
	pDevice->SetMaterial(Material);
}

void DeviceHider::SetTexture(int index, IDirect3DBaseTexture9 * pTexture)
{
	pDevice->SetTexture(index, pTexture);
}

void DeviceHider::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX * pMatrix)
{
	pDevice->SetTransform(State, pMatrix);
}

void DeviceHider::SetVertexDeclaration(IDirect3DVertexDeclaration9 * pDecl)
{
	pDevice->SetVertexDeclaration(pDecl);
}

void DeviceHider::SetLight(DWORD index, D3DLIGHT9 light)
{
	pDevice->SetLight(index, &light);
}

void DeviceHider::LightEnable(DWORD index, BOOL Active)
{
	pDevice->LightEnable(index, Active);
}