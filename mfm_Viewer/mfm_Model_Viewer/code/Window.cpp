#include "Window.h"
#include <Windows.h>
#include <stdio.h>
#include "Graphics.h"
#include "InputKeyboard.h"
#include "InputMouse.h"
#include "CreateData.h"
#include "Camera.h"


DATA_TYPE::MFMMESHDATA Window::model;
bool Window::Model_Change = false;
bool Window::DisplayMode = true;
bool Window::Press = false;
bool Window::Blur = false;

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
	main_grid.Init();
	Render_Draw.Init(NULL);
}

void Window::Uninit()
{
	Render_Draw.Uninit();
	main_grid.Uninit();
	Create::Destroy();
	Device->UnInit();	
}

void Window::Update()
{
	InputKeyboard::Updata();
	Camera::Updata();
	main_grid.Update();
	Render_Draw.Update();
	if (Model_Change)
	{
		Render_Draw.Reset(&model);
		Model_Change = false;
	}
}
void Window::Draw()
{
	Device->Clear();
	Device->DrawBigin();

	main_grid.Draw();
	Render_Draw.Draw();

	Device->DrawEnd();
	Device->Present();
}


void Window::KeyBoardDown(WPARAM in_wParam, HWND in_hWnd)
{
	int nID;
	if (in_wParam == VK_ESCAPE)
	{
		nID = MessageBox(in_hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(in_hWnd);
		}
	}
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
	HDROP hDrop;
	UINT uFileNo;

	LOWORD(lParam);
	HIWORD(lParam);
	switch (uMsg)
	{
	case WM_CREATE: 
	{
		DragAcceptFiles(in_hWnd,true);
	}
	break;
	case WM_DESTROY:	//WM_CLOSE,WM_QUIT
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
		KeyBoardDown(wParam, in_hWnd);
	}
	break;
	case WM_DROPFILES: 
	{
		char path[MAX_PATH];
		DragQueryFile((HDROP)wParam,0, path, MAX_PATH);
		
		model.Destroy();
		Create::MFMMesh(&model,path);
		Model_Change = true;
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
