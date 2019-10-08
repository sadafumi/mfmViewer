#include "main.h"
#include <Windows.h> //ウィンドウズAPI
#include <stdio.h>
#include "Window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window wind; //ウィンド関数
	MSG msg; //メッセージ変数
	HWND hWnd = NULL;
	hInstance = hInstance;
	hPrevInstance = hPrevInstance;
	lpCmdLine = lpCmdLine;
	nCmdShow = nCmdShow;
	wind.Create(hWnd, hInstance, nCmdShow);

	wind.Init();
	DWORD nNowTime = 0, nOldTime = 0;
	timeBeginPeriod(1);
	
	for (;;)
	{
		//*メッセージループ*//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//メッセージ処理
			if (msg.message == WM_QUIT)
			{
				wind.Uninit();//終了位置
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
			if ((nNowTime - nOldTime) * 60 >= 1000)
			{
				if (wind.ChangeDisplay(hInstance, hWnd))
				{
					break;
				}
				//更新
				wind.Update();
				//描画
				wind.Draw();
				//前フレームの時間を保存
				nOldTime = nNowTime;
			}
			//break;
		}
	}
	timeEndPeriod(1);

	wind.Delete();
	return (int)msg.wParam;
}

/*-------------------------------*/
/*          マグロ定義           */
/*-------------------------------*/

//
//#include <Windows.h>
//#include <stdio.h>
//#include <vector>
//#include <d3d9.h>
//#include <d3dx9.h>
//#include "main.h"
//#include "DrawData.h"
//#include "Render.h"
//#include "CreateData.h"
//#include "Graphics.h"
//#include "Scene.h"
//#include "InputKeyboard.h"
//#include "InputMouse.h"
//
//
//#define CLASS_NAME			"simple"//クラスの名前
//#define WINDOW_NAME			"sinmle"//Windowの名前
//#define ID_TIMER			(100001)
//#define SCREENSTYLE			(WS_OVERLAPPEDWINDOW &~(WS_THICKFRAME | WS_MAXIMIZEBOX))
//#define DISPLAYMODE			(true)
//
//
///*-------------------------------*/
///*       プロトタイプ宣言        */
///*-------------------------------*/
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //ウィンドウプロシージャ
//HWND WindInit(HINSTANCE hInstance, int nCmdShow);
//void Init();
//void Uninit(void);	//終了処理
//void Update(void);	//更新
//void Draw(void);	//描画
//bool ChangeScreen(HINSTANCE hInstance, HWND hWnd,bool);
//
///*-------------------------------*/
///*       グローバル変数　        */
///*-------------------------------*/
//
//LPDIRECT3D9			g_pD3D = NULL;			//ダイレクト3Dインターフェース
//LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//ダイレクト3Dデバイス
//
//SceneManager *Mane;
//
//DirectX* Device = NULL;
//static LPDIRECT3DDEVICE9 pDevice;	//ダイレクト3Dデバイス
//LPDIRECT3DDEVICE9 DeviceHider::pDevice;
//bool DisplayMode = true;
//bool Press = false;
//bool Blur = false;
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	
//	lpCmdLine = lpCmdLine;
//	hPrevInstance = hPrevInstance;
//
//	HWND hWnd = WindInit(hInstance, nCmdShow);
//
//	Device = new DirectX;
//									//初期化
//	if (!Device->Init(hInstance, hWnd, DisplayMode))
//	{
//		MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_OK);
//		return -1;
//	}
//
//	
//	InputKeyboard::Init(hInstance, hWnd);
//	MSG msg;							//メッセージ変数
//	InputMouse::Init(&hWnd);
//
//	Init();
//	DWORD nNowTime = 0, nOldTime = 0;
//	timeBeginPeriod(1);
//
//	for (;;)
//	{
//		//*メッセージループ*//
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			//メッセージ処理
//			if (msg.message == WM_QUIT)
//			{
//				Uninit();//終了位置
//				break;
//			}
//			else
//			{
//				TranslateMessage(&msg);
//				DispatchMessage(&msg);
//			}
//		}
//		else
//		{
//			//ゲーム処理
//			nNowTime = timeGetTime();//今の時間
//			if ((nNowTime - nOldTime) * 60 >= 1000)
//			{
//				//更新
//				if(Press)
//				{
//					if(ChangeScreen(hInstance, hWnd, DisplayMode))
//					{
//						break;
//					}
//				}
//				Update();
//				//描画
//				Draw();
//				//前フレームの時間を保存
//				nOldTime = nNowTime;
//				Press = false;
//			}
//			//break;
//		}
//	}
//	timeEndPeriod(1);
//
//	return (int)msg.wParam;
//}
//HWND WindInit(HINSTANCE hInstance, int nCmdShow)
//{
//	int nScreenWidth, nScreenHiegth, WindowSizeWidth, WindowSizeHiegth;
//	RECT wr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HIEGTH }, dr;
//
//	//*ウィンドウを登録*//
//	WNDCLASSEX wcex =
//	{
//		sizeof(WNDCLASSEX),				//サイズ
//		CS_VREDRAW | CS_HREDRAW,		//スタイル
//		WndProc,						//プロシージャ
//		0,								//いらないから０
//		0,								//いらないから０
//		hInstance,						//インスタンス
//		NULL,							//アイコン
//		LoadCursor(NULL,IDC_ARROW),	//マウスカーソル
//		(HBRUSH)(COLOR_WINDOW + 1),	//初期背景色
//		NULL,							//メニュー
//		CLASS_NAME,						//クラスの名前
//		NULL,							//ミニアイコン
//	};
//	RegisterClassEx(&wcex);
//
//	GetWindowRect(GetDesktopWindow(), &dr);
//	AdjustWindowRect(&wr, SCREENSTYLE, false);
//	nScreenWidth = wr.right - wr.left;
//	nScreenHiegth = wr.bottom - wr.top;
//	WindowSizeWidth = (dr.right - nScreenWidth) / 2;
//	WindowSizeHiegth = (dr.bottom - nScreenHiegth) / 2;
//	dr.right < WindowSizeWidth ? WindowSizeWidth = 0 : WindowSizeWidth;
//	dr.bottom < WindowSizeHiegth ? WindowSizeHiegth = 0 : WindowSizeHiegth;
//	//デスクトップサイズ＜ウィンドウサイズ？０：ウィンドウ
//	//*ウィンドウを設定*//
//	HWND hWnd = CreateWindowEx(
//		0,
//		CLASS_NAME,
//		WINDOW_NAME,
//		SCREENSTYLE,
//		WindowSizeWidth,
//		WindowSizeHiegth,
//		nScreenWidth,
//		nScreenHiegth,
//		NULL,
//		NULL,
//		hInstance,
//		NULL
//	);
//	ShowWindow(hWnd, nCmdShow);		//ウィンドウ呼び出し
//	UpdateWindow(hWnd);				//ウィンドウの更新
//
//	return hWnd;
//}
////初期化
//void Init()
//{
//	Mane = new SceneManager;
//	Mane->Init();
//}
////終了処理
//void Uninit(void)
//{
//	InputKeyboard::Uninit();
//	Mane->Uninit();
//	delete Mane;
//	Device->UnInit();
//}
////更新
//void Update(void)
//{
//	Mane->Updata();
//}
////描画
//void Draw(void)
//{
//	if(Blur)
//	{
//		
//	}
//	else 
//	{
//		Device->Clear();
//		Device->DrawBigin();
//
//		Mane->Draw();
//
//		Device->DrawEnd();
//		Device->Present();
//	}
//}
////デバッグFPS
//void DrawFPS(void)
//{
//
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //ウィンドウプロシージャ//コールバック
//{
//	int nID;
//
//	LOWORD(lParam);
//	HIWORD(lParam);
//	switch (uMsg)
//	{
//	case WM_DESTROY:	//WM_CLOSE,WM_QUIT
//		PostQuitMessage(0);
//		break;
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_ESCAPE://[ESC]キーが押された [ESC]は終了ボタン
//			nID = MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_YESNO | MB_DEFBUTTON2);
//			if (nID == IDYES)
//			{
//				DestroyWindow(hWnd);
//			}
//			break;
//		case VK_F11: 
//		{
//			DisplayMode = !DisplayMode;
//			Press = true;
//		}
//		case VK_F9:
//		{
//			DeviceHider::CreateScreenShots();
//		}
//		break;
//		}
//		break;
//	case WM_CLOSE://[X]は終了ボタン
//		nID = MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_YESNO | MB_DEFBUTTON2);
//		if (nID == IDYES)
//		{
//			DestroyWindow(hWnd);
//		}
//		else
//		{
//			return 0;
//		}
//		break;
//	default:
//		break;
//	}
//	return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
//bool ChangeScreen(HINSTANCE hInstance, HWND hWnd,bool NewScreen)
//{
//	Uninit();
//	if (!Device->Init(hInstance, hWnd, NewScreen))
//	{
//		if (!Device->Init(hInstance, hWnd, !NewScreen))
//		{
//			Init();
//			MessageBox(hWnd, "終了しますか？", "シャットダウンメッセージ", MB_OK);
//			return true;
//		}
//	}
//	Init();
//	return false;
//}