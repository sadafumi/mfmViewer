#include "main.h"
#include <Windows.h> //�E�B���h�E�YAPI
#include <stdio.h>
#include "Window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window wind; //�E�B���h�֐�
	MSG msg; //���b�Z�[�W�ϐ�
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
		//*���b�Z�[�W���[�v*//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//���b�Z�[�W����
			if (msg.message == WM_QUIT)
			{
				wind.Uninit();//�I���ʒu
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
			//�Q�[������
			nNowTime = timeGetTime();//���̎���
			if ((nNowTime - nOldTime) * 60 >= 1000)
			{
				if (wind.ChangeDisplay(hInstance, hWnd))
				{
					break;
				}
				//�X�V
				wind.Update();
				//�`��
				wind.Draw();
				//�O�t���[���̎��Ԃ�ۑ�
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
/*          �}�O����`           */
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
//#define CLASS_NAME			"simple"//�N���X�̖��O
//#define WINDOW_NAME			"sinmle"//Window�̖��O
//#define ID_TIMER			(100001)
//#define SCREENSTYLE			(WS_OVERLAPPEDWINDOW &~(WS_THICKFRAME | WS_MAXIMIZEBOX))
//#define DISPLAYMODE			(true)
//
//
///*-------------------------------*/
///*       �v���g�^�C�v�錾        */
///*-------------------------------*/
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //�E�B���h�E�v���V�[�W��
//HWND WindInit(HINSTANCE hInstance, int nCmdShow);
//void Init();
//void Uninit(void);	//�I������
//void Update(void);	//�X�V
//void Draw(void);	//�`��
//bool ChangeScreen(HINSTANCE hInstance, HWND hWnd,bool);
//
///*-------------------------------*/
///*       �O���[�o���ϐ��@        */
///*-------------------------------*/
//
//LPDIRECT3D9			g_pD3D = NULL;			//�_�C���N�g3D�C���^�[�t�F�[�X
//LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//�_�C���N�g3D�f�o�C�X
//
//SceneManager *Mane;
//
//DirectX* Device = NULL;
//static LPDIRECT3DDEVICE9 pDevice;	//�_�C���N�g3D�f�o�C�X
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
//									//������
//	if (!Device->Init(hInstance, hWnd, DisplayMode))
//	{
//		MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_OK);
//		return -1;
//	}
//
//	
//	InputKeyboard::Init(hInstance, hWnd);
//	MSG msg;							//���b�Z�[�W�ϐ�
//	InputMouse::Init(&hWnd);
//
//	Init();
//	DWORD nNowTime = 0, nOldTime = 0;
//	timeBeginPeriod(1);
//
//	for (;;)
//	{
//		//*���b�Z�[�W���[�v*//
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			//���b�Z�[�W����
//			if (msg.message == WM_QUIT)
//			{
//				Uninit();//�I���ʒu
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
//			//�Q�[������
//			nNowTime = timeGetTime();//���̎���
//			if ((nNowTime - nOldTime) * 60 >= 1000)
//			{
//				//�X�V
//				if(Press)
//				{
//					if(ChangeScreen(hInstance, hWnd, DisplayMode))
//					{
//						break;
//					}
//				}
//				Update();
//				//�`��
//				Draw();
//				//�O�t���[���̎��Ԃ�ۑ�
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
//	//*�E�B���h�E��o�^*//
//	WNDCLASSEX wcex =
//	{
//		sizeof(WNDCLASSEX),				//�T�C�Y
//		CS_VREDRAW | CS_HREDRAW,		//�X�^�C��
//		WndProc,						//�v���V�[�W��
//		0,								//����Ȃ�����O
//		0,								//����Ȃ�����O
//		hInstance,						//�C���X�^���X
//		NULL,							//�A�C�R��
//		LoadCursor(NULL,IDC_ARROW),	//�}�E�X�J�[�\��
//		(HBRUSH)(COLOR_WINDOW + 1),	//�����w�i�F
//		NULL,							//���j���[
//		CLASS_NAME,						//�N���X�̖��O
//		NULL,							//�~�j�A�C�R��
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
//	//�f�X�N�g�b�v�T�C�Y���E�B���h�E�T�C�Y�H�O�F�E�B���h�E
//	//*�E�B���h�E��ݒ�*//
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
//	ShowWindow(hWnd, nCmdShow);		//�E�B���h�E�Ăяo��
//	UpdateWindow(hWnd);				//�E�B���h�E�̍X�V
//
//	return hWnd;
//}
////������
//void Init()
//{
//	Mane = new SceneManager;
//	Mane->Init();
//}
////�I������
//void Uninit(void)
//{
//	InputKeyboard::Uninit();
//	Mane->Uninit();
//	delete Mane;
//	Device->UnInit();
//}
////�X�V
//void Update(void)
//{
//	Mane->Updata();
//}
////�`��
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
////�f�o�b�OFPS
//void DrawFPS(void)
//{
//
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //�E�B���h�E�v���V�[�W��//�R�[���o�b�N
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
//		case VK_ESCAPE://[ESC]�L�[�������ꂽ [ESC]�͏I���{�^��
//			nID = MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
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
//	case WM_CLOSE://[X]�͏I���{�^��
//		nID = MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
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
//			MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_OK);
//			return true;
//		}
//	}
//	Init();
//	return false;
//}