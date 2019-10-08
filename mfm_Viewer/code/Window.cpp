#include "Window.h"
#include <Windows.h>
#include <stdio.h>
#include "Graphics.h"

#include "InputKeyboard.h"
#include "InputMouse.h"
#include "CreateData.h"


bool Window::DisplayMode = true;
bool Window::Press = false;
bool Window::Blur = false;
Model Window::model;

Window::Window()
{
}
Window::~Window()
{
}
HWND Window::Create(HWND in_hWnd, HINSTANCE hInstance, int nCmdShow)
{
	int nScreenWidth, nScreenHiegth, WindowSizeWidth, WindowSizeHiegth;
	RECT wr = { 0 , 0 , Screen_Width_Size , Screen_Hiegth_Size }, dr;

	//*�E�B���h�E��o�^*//
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//�T�C�Y
		CS_VREDRAW | CS_HREDRAW,		//�X�^�C��
		this->WndProc,						//�v���V�[�W��
		0,								//����Ȃ�����O
		0,								//����Ȃ�����O
		hInstance,						//�C���X�^���X
		NULL,							//�A�C�R��
		LoadCursor(NULL,IDC_ARROW),	//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),	//�����w�i�F
		NULL,							//���j���[
		this->Class_Name,						//�N���X�̖��O
		NULL,							//�~�j�A�C�R��
	};
	RegisterClassEx(&wcex);

	GetWindowRect(GetDesktopWindow(), &dr);
	AdjustWindowRect(&wr, (WS_OVERLAPPEDWINDOW &~(WS_THICKFRAME | WS_MAXIMIZEBOX)), false);
	nScreenWidth = wr.right - wr.left;
	nScreenHiegth = wr.bottom - wr.top;
	WindowSizeWidth = (dr.right - nScreenWidth) / 2;
	WindowSizeHiegth = (dr.bottom - nScreenHiegth) / 2;
	dr.right < WindowSizeWidth ? WindowSizeWidth = 0 : WindowSizeWidth;
	dr.bottom < WindowSizeHiegth ? WindowSizeHiegth = 0 : WindowSizeHiegth;


	//*�E�B���h�E��ݒ�*//
	in_hWnd = CreateWindowEx(
		0,
		this->Class_Name,
		this->Window_Name,
		WS_OVERLAPPEDWINDOW,
		WindowSizeWidth,
		WindowSizeHiegth,
		nScreenWidth,
		nScreenHiegth,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(in_hWnd, nCmdShow);		//�E�B���h�E�Ăяo��
	UpdateWindow(in_hWnd);				//�E�B���h�E�̍X�V

	Device = new DirectX;
	if (!Device->Init(hInstance, in_hWnd, DisplayMode))
	{
		MessageBox(in_hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_OK);
		return in_hWnd;
	}
	InputKeyboard::Init(hInstance, in_hWnd);
	InputMouse::Init(&in_hWnd);
	
	return in_hWnd;
}
void Window::Delete()
{
	InputMouse::Uninit();
	InputKeyboard::Uninit();
	delete Device;
	PostQuitMessage(0);
}

void Window::Init()
{
	grid.Init();
}

void Window::Uninit()
{
	model.Uninit();
	grid.Uninit();
	Device->UnInit();	
}

void Window::Update()
{
	grid.Updata();
}
void Window::Draw()
{
	Device->Clear();
	Device->DrawBigin();

	grid.Draw();
	model.Draw();

	Device->DrawEnd();
	Device->Present();
}


void Window::KeyBoardDown(WPARAM in_wParam, HWND in_hWnd)
{
	int nID;
	Press = false;
	if (in_wParam == VK_ESCAPE)
	{
		nID = MessageBox(in_hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(in_hWnd);
		}
	}
	if (in_wParam == VK_NUMPAD0)
	{
		//Blur = !Blur;
		Blur = true;
	}
	//if (in_wParam == VK_F11)
	//{
	//	DisplayMode = !DisplayMode;
	//	Press = true;
	//}
	if (in_wParam == VK_F9)
	{
		DeviceHider::CreateScreenShots();
	}
}
bool Window::ChangeDevice(HINSTANCE hInstance, HWND hWnd, bool NewScreen)
{
	Uninit();
	if (!Device->Init(hInstance, hWnd, NewScreen))
	{
		if (!Device->Init(hInstance, hWnd, !NewScreen))
		{
			Init();
			MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_OK);
			return true;
		}
	}
	Init();
	return false;
}
bool Window::ChangeDisplay(HINSTANCE hInstance, HWND hWnd)
{
	if (Press)
	{
		if (this->ChangeDevice(hInstance, hWnd, DisplayMode))
		{
			return true;
		}
	}
	return false;
}
LRESULT Window::WndProc(HWND in_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	LOWORD(lParam);
	HIWORD(lParam);
	switch (uMsg)
	{
	case WM_CREATE:
		DragAcceptFiles(in_hWnd, TRUE);
		break;
	case WM_DROPFILES:
		int id, i;
		HDROP hDrop;
		UINT uFileNo;
		char szFileName[256];
		hDrop = (HDROP)wParam;
		uFileNo = DragQueryFile((HDROP)wp, 0xFFFFFFFF, NULL, 0);
		for (i = 0; i < (int)uFileNo; i++) {
			DragQueryFile(hDrop, i, szFileName, sizeof(szFileName));
			if (ShellExecute(in_hWnd, NULL, szFileName, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32)
				MessageBox(in_hWnd, "�t�@�C�����J���܂���ł���", "���s", MB_OK);
		}
		DragFinish(hDrop);
		break;
	//case WM_DROPFILES:
	//{
	//	HDROP hDrop = (HDROP)wParam;
	//	TCHAR tchName[MAX_PATH];
	//	//tchName�Ƀh���b�v���ꂽ�t�@�C�����������Ă���
	//	DragQueryFile(hDrop, 0, tchName, sizeof(tchName));

	//	if (model.Active)
	//	{
	//		model.Uninit();
	//	}
	//	model.Init(tchName);
	//	//�I��
	//	DragFinish(hDrop);
	//}
	case WM_DESTROY:	//WM_CLOSE,WM_QUIT
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
		KeyBoardDown(wParam, in_hWnd);
	}
	break;
	case WM_CLOSE://[X]�͏I���{�^��
		nID = MessageBox(in_hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(in_hWnd);
		}
		else
		{
			return 0;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(in_hWnd, uMsg, wParam, lParam);
}
