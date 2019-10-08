/*------------------------------*/
/* �e�N�X�`���A�j���[�V�������� */
/* AT12A242 �@��j���@2017/6/05 */
/*------------------------------*/

/*-------------------------------*/
/*           �w�b�_�`�@�@  �@�@  */
/*-------------------------------*/
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