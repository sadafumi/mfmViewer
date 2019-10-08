/*------------------------------*/
/* テクスチャアニメーション処理 */
/* AT12A242 宗貞史樹　2017/6/05 */
/*------------------------------*/

/*-------------------------------*/
/*           ヘッダ～　　  　　  */
/*-------------------------------*/
#include "Include.h"

/*-------------------------------*/
/*          マグロ定義           */
/*-------------------------------*/
#define CLASS_NAME			"simple"//クラスの名前
#define WINDOW_NAME			"sinmle"//Windowの名前
#define ID_TIMER			(100001)
#define SCREENSTYLE			(WS_OVERLAPPEDWINDOW &~(WS_THICKFRAME | WS_MAXIMIZEBOX))
#define DISPLAYMODE			(true)

/*-------------------------------*/
/*           構造体定義          */
/*-------------------------------*/



/*-------------------------------*/
/*       プロトタイプ宣言        */
/*-------------------------------*/

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ); //ウィンドウプロシージャ
BOOL Init(HINSTANCE hInstance, HWND hWnd , BOOL bWindow); //初期化
void Uninit(void);	//終了処理
void Update(void);	//更新
void Draw(void);	//描画

/*-------------------------------*/
/*       グローバル変数　        */
/*-------------------------------*/

LPDIRECT3D9			g_pD3D = NULL;			//ダイレクト3Dインターフェース
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//ダイレクト3Dデバイス
HIERARCHYDERIVED	Hierarchy;
LPDIRECTINPUT8      g_pDInput = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	lpCmdLine = lpCmdLine;
	hPrevInstance = hPrevInstance;
	int nScreenWidth, nScreenHiegth, WindowSizeWidth, WindowSizeHiegth;
	RECT wr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HIEGTH }, dr;

	//*ウィンドウを登録*//
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//サイズ
		CS_VREDRAW | CS_HREDRAW,		//スタイル
		WndProc,						//プロシージャ
		0,								//いらないから０
		0,								//いらないから０
		hInstance,						//インスタンス
		NULL,							//アイコン
		LoadCursor(NULL,IDC_ARROW),	//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),	//初期背景色
		NULL,							//メニュー
		CLASS_NAME,						//クラスの名前
		NULL,							//ミニアイコン
	};
	RegisterClassEx(&wcex);

	GetWindowRect(GetDesktopWindow(), &dr);
	AdjustWindowRect(&wr, SCREENSTYLE, false);
	nScreenWidth = wr.right - wr.left;
	nScreenHiegth = wr.bottom - wr.top;
	WindowSizeWidth = (dr.right - nScreenWidth) / 2;
	WindowSizeHiegth = (dr.bottom - nScreenHiegth) / 2;
	dr.right < WindowSizeWidth ? WindowSizeWidth = 0 : WindowSizeWidth;
	dr.bottom < WindowSizeHiegth ? WindowSizeHiegth = 0 : WindowSizeHiegth;
	//デスクトップサイズ＜ウィンドウサイズ？０：ウィンドウ
	//*ウィンドウを設定*//
	HWND hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		SCREENSTYLE,
		WindowSizeWidth,
		WindowSizeHiegth,
		nScreenWidth,
		nScreenHiegth,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hWnd, nCmdShow);		//ウィンドウ呼び出し
	UpdateWindow(hWnd);				//ウィンドウの更新

	//初期化
	if (!Init(hInstance, hWnd, DISPLAYMODE))
	{
		MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_OK);
		return -1;
	}

	MSG msg;							//メッセージ変数

	DWORD nNowTime = 0, nOldTime = 0;
	timeBeginPeriod(1);

	for (;;) 
	{
		//*メッセージループ*//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//メッセージ処理
			if ( msg.message == WM_QUIT )
			{
				Uninit();//終了位置
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//ゲーム処理
			nNowTime = timeGetTime();//今の時間
			if ( (nNowTime - nOldTime ) * 60 >=  1000 )
			{
				//更新
				Update();
				//描画
				Draw();
				//前フレームの時間を保存
				nOldTime = nNowTime;
			}
			//break;
		}
	}
	timeEndPeriod(1);

	return (int)msg.wParam;
}
//初期化
BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) 
{
	hInstance = hInstance;
	//LPDIRECT3D9			g_pD3D = NULL;			//ダイレクト3Dインターフェース
	//LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//ダイレクト3Dデバイス

	//ディスプレイモードの取得
	D3DDISPLAYMODE d3ddm;

	//デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS d3dpp;

	//ダイレクト3Dインタフェースの所得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//エンドユーザランタイムがないともらえない
	if(g_pD3D == NULL)
	{
		return false;
	}

	if( FAILED( g_pD3D -> GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm )))
	{
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));		//中身空にする
	d3dpp.BackBufferWidth				= SCREEN_WIDTH;					//幅
	d3dpp.BackBufferHeight				= SCREEN_HIEGTH;				//高さ
	d3dpp.BackBufferFormat				= d3ddm.Format;					//色
	d3dpp.BackBufferCount				= 1;							//	
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;		//
	d3dpp.EnableAutoDepthStencil		= TRUE;							//
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D16;					//D24_S8
	d3dpp.Windowed						= bWindow;						//
	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;		//
	d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;	//

	//デバイスの生成
	//[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		MessageBox(hWnd, "デバイスの作成に失敗しました", "デバイス作成", MB_OK); 
		return false;
	}
	//キーボード初期化
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		MessageBox(hWnd, "キーボード所得に失敗しました", "キーボード所得", MB_OK);
		return false;
	}

	//テクスチャの読み込み
	//αブレンドを行う
	//SRC　今書くもの。つまり
	//SRC_RGB * SRC_α + DEST_RGB * ( 1 - SRC_α )
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステート
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	
	InitScene();
	InitFade();
	BackgroundInit();
	InitDebugText();
	
	return true;
} 
//終了処理
void Uninit(void)
{
	UninitFade();
	UnInitDebugText();
	UninitKeyboard();
	if(g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D != NULL) 
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	UninitScene();
	BackgroundUninit();
}
//更新
void Update(void)
{
	UpdateScene();
}
//描画
void Draw(void)
{
	g_pD3DDevice->Clear( 0, NULL,	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(19,122,127,255), 1.0f,0);//1.0fZバッファ19/122/127

	if (SUCCEEDED(g_pD3DDevice->BeginScene())) 
	{
		BackgroundDraw();
		DrawScene();
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}
//デバッグFPS
void DrawFPS(void)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //ウィンドウプロシージャ//コールバック
{
	int nID;

	switch (uMsg) 
	{
		case WM_DESTROY:	//WM_CLOSE,WM_QUIT
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE://[ESC]キーが押された [ESC]は終了ボタン
				nID = MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_YESNO | MB_DEFBUTTON2);
				if (nID == IDYES)
				{
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		case WM_CLOSE://[X]は終了ボタン
			nID = MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		default:
			break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}
HIERARCHYDERIVED* GetHierearchy(void)
{
	return &Hierarchy;
}