/*------------------------------*/
/* テクスチャアニメーション処理 */
/* AT12A242 宗貞史樹　2017/6/05 */
/*------------------------------*/

/*-------------------------------*/
/*           ヘッダ～　　  　　  */
/*-------------------------------*/
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