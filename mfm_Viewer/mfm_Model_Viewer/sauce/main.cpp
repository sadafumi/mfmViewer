/*------------------------------*/
/* �e�N�X�`���A�j���[�V�������� */
/* AT12A242 �@��j���@2017/6/05 */
/*------------------------------*/

/*-------------------------------*/
/*           �w�b�_�`�@�@  �@�@  */
/*-------------------------------*/
#include "Include.h"

/*-------------------------------*/
/*          �}�O����`           */
/*-------------------------------*/
#define CLASS_NAME			"simple"//�N���X�̖��O
#define WINDOW_NAME			"sinmle"//Window�̖��O
#define ID_TIMER			(100001)
#define SCREENSTYLE			(WS_OVERLAPPEDWINDOW &~(WS_THICKFRAME | WS_MAXIMIZEBOX))
#define DISPLAYMODE			(true)

/*-------------------------------*/
/*           �\���̒�`          */
/*-------------------------------*/



/*-------------------------------*/
/*       �v���g�^�C�v�錾        */
/*-------------------------------*/

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ); //�E�B���h�E�v���V�[�W��
BOOL Init(HINSTANCE hInstance, HWND hWnd , BOOL bWindow); //������
void Uninit(void);	//�I������
void Update(void);	//�X�V
void Draw(void);	//�`��

/*-------------------------------*/
/*       �O���[�o���ϐ��@        */
/*-------------------------------*/

LPDIRECT3D9			g_pD3D = NULL;			//�_�C���N�g3D�C���^�[�t�F�[�X
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//�_�C���N�g3D�f�o�C�X
HIERARCHYDERIVED	Hierarchy;
LPDIRECTINPUT8      g_pDInput = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	lpCmdLine = lpCmdLine;
	hPrevInstance = hPrevInstance;
	int nScreenWidth, nScreenHiegth, WindowSizeWidth, WindowSizeHiegth;
	RECT wr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HIEGTH }, dr;

	//*�E�B���h�E��o�^*//
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//�T�C�Y
		CS_VREDRAW | CS_HREDRAW,		//�X�^�C��
		WndProc,						//�v���V�[�W��
		0,								//����Ȃ�����O
		0,								//����Ȃ�����O
		hInstance,						//�C���X�^���X
		NULL,							//�A�C�R��
		LoadCursor(NULL,IDC_ARROW),	//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),	//�����w�i�F
		NULL,							//���j���[
		CLASS_NAME,						//�N���X�̖��O
		NULL,							//�~�j�A�C�R��
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
	//�f�X�N�g�b�v�T�C�Y���E�B���h�E�T�C�Y�H�O�F�E�B���h�E
	//*�E�B���h�E��ݒ�*//
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
	ShowWindow(hWnd, nCmdShow);		//�E�B���h�E�Ăяo��
	UpdateWindow(hWnd);				//�E�B���h�E�̍X�V

	//������
	if (!Init(hInstance, hWnd, DISPLAYMODE))
	{
		MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_OK);
		return -1;
	}

	MSG msg;							//���b�Z�[�W�ϐ�

	DWORD nNowTime = 0, nOldTime = 0;
	timeBeginPeriod(1);

	for (;;) 
	{
		//*���b�Z�[�W���[�v*//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//���b�Z�[�W����
			if ( msg.message == WM_QUIT )
			{
				Uninit();//�I���ʒu
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
			if ( (nNowTime - nOldTime ) * 60 >=  1000 )
			{
				//�X�V
				Update();
				//�`��
				Draw();
				//�O�t���[���̎��Ԃ�ۑ�
				nOldTime = nNowTime;
			}
			//break;
		}
	}
	timeEndPeriod(1);

	return (int)msg.wParam;
}
//������
BOOL Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow) 
{
	hInstance = hInstance;
	//LPDIRECT3D9			g_pD3D = NULL;			//�_�C���N�g3D�C���^�[�t�F�[�X
	//LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//�_�C���N�g3D�f�o�C�X

	//�f�B�X�v���C���[�h�̎擾
	D3DDISPLAYMODE d3ddm;

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS d3dpp;

	//�_�C���N�g3D�C���^�t�F�[�X�̏���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//�G���h���[�U�����^�C�����Ȃ��Ƃ��炦�Ȃ�
	if(g_pD3D == NULL)
	{
		return false;
	}

	if( FAILED( g_pD3D -> GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm )))
	{
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));		//���g��ɂ���
	d3dpp.BackBufferWidth				= SCREEN_WIDTH;					//��
	d3dpp.BackBufferHeight				= SCREEN_HIEGTH;				//����
	d3dpp.BackBufferFormat				= d3ddm.Format;					//�F
	d3dpp.BackBufferCount				= 1;							//	
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;		//
	d3dpp.EnableAutoDepthStencil		= TRUE;							//
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D16;					//D24_S8
	d3dpp.Windowed						= bWindow;						//
	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;		//
	d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;	//

	//�f�o�C�X�̐���
	//[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		MessageBox(hWnd, "�f�o�C�X�̍쐬�Ɏ��s���܂���", "�f�o�C�X�쐬", MB_OK); 
		return false;
	}
	//�L�[�{�[�h������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�����Ɏ��s���܂���", "�L�[�{�[�h����", MB_OK);
		return false;
	}

	//�e�N�X�`���̓ǂݍ���
	//���u�����h���s��
	//SRC�@���������́B�܂�
	//SRC_RGB * SRC_�� + DEST_RGB * ( 1 - SRC_�� )
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);

	//�T���v���[�X�e�[�g�̐ݒ�
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
//�I������
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
//�X�V
void Update(void)
{
	UpdateScene();
}
//�`��
void Draw(void)
{
	g_pD3DDevice->Clear( 0, NULL,	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(19,122,127,255), 1.0f,0);//1.0fZ�o�b�t�@19/122/127

	if (SUCCEEDED(g_pD3DDevice->BeginScene())) 
	{
		BackgroundDraw();
		DrawScene();
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}
//�f�o�b�OFPS
void DrawFPS(void)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //�E�B���h�E�v���V�[�W��//�R�[���o�b�N
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
			case VK_ESCAPE://[ESC]�L�[�������ꂽ [ESC]�͏I���{�^��
				nID = MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
				if (nID == IDYES)
				{
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		case WM_CLOSE://[X]�͏I���{�^��
			nID = MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
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