#include "Include.h"

// UI�E�e�N�X�`��
#define TITLEUI1 ("resource\\frame.png")
#define TITLEUI2 ("resource\\frame.png")

#define MAX_TITLE_LOGO_UI	(1)	// �^�C�g�����S
#define MAX_TITLE_SELECT_UI	(3)	// �I���q
#define MAX_TITLE_HELP_UI	(1)	// �w���v

#define MAX_UI		(MAX_TITLE_LOGO_UI + MAX_TITLE_SELECT_UI + MAX_TITLE_HELP_UI)

// �I���E��I�����̐F
#define SELECT    D3DCOLOR_ARGB(200, 0, 150, 255)
#define DEFAULT    D3DCOLOR_ARGB(255, 255, 255, 255)

// ���̓}�N�� �e���v���[�g
// �L�[�{�[�h����
#define KEY_OK			(DIK_RETURN)
#define KEY_CANCEL		(DIK_BACKSPACE)
#define KEY_UP			(DIK_W)
#define KEY_DOWN		(DIK_S)
#define KEY_RIGHT		(DIK_D)
#define KEY_LEFT		(DIK_A)
// �R���g���[���[����
#define CNT_OK			(DIK_RETURN)
#define CNT_CANCEL		(DIK_BACKSPACE)
#define CNT_UP			(XINPUT_GAMEPAD_DPAD_UP)
#define CNT_DOWN		(XINPUT_GAMEPAD_DPAD_DOWN)
#define CNT_RIGHT		(XINPUT_GAMEPAD_DPAD_RIGHT)
#define CNT_LEFT		(XINPUT_GAMEPAD_DPAD_LEFT)

// �ϐ��錾
RenderUI  *TitleUI;
RenderUI  *SelectUI;
VERTEXDATA TitleUIDATA[MAX_UI];
Controller TitleControl;

// �I���Ǘ�
short Selecter = 0;

void TitleUIInit(void)
{
	// �e�N�X�`������
	CreateMeshBoard(&TitleUIDATA[0], TITLEUI1);
	CreateMeshBoard(&TitleUIDATA[1], TITLEUI2);

	// �������m��
	TitleUI  = new RenderUI[MAX_TITLE_LOGO_UI];
	TitleUI[0].SetRendData(&TitleUIDATA[0]);

	SelectUI = new RenderUI[MAX_TITLE_SELECT_UI];
	SelectUI[0].SetRendData(&TitleUIDATA[1]);
	SelectUI[1].SetRendData(&TitleUIDATA[1]);
	SelectUI[2].SetRendData(&TitleUIDATA[1]);
}
void TitleUIUninit(void)
{
	delete[] TitleUI;
	delete[] SelectUI;
	TitleUIDATA[0].Destroy();
	TitleUIDATA[1].Destroy();
}
void TitleUIUpdate(void)
{
	// ���� : �L�[�{�[�h==========================================
	TitleControl.Updata();
	if (GetKeyboardTrigger(KEY_UP) || TitleControl.GetPressButton(CNT_UP))
	{
		Selecter--;
		if (Selecter < 0)Selecter = 2;
	}
	if (GetKeyboardTrigger(KEY_DOWN) || TitleControl.GetTriggerButton(CNT_DOWN))
	{
		Selecter++;
		if (Selecter > 2)Selecter = 0;
	}
	//============================================================

	// �^�C�g�����S
	D3DCOLOR color = D3DCOLOR_ARGB(123, 255, 0, 0);
	TitleUI[0].SetMtXPos(-0.4f, 0.45f, 0.0f);
	TitleUI[0].SetMtXScale(1.2, 0.35, 0);
	TitleUI[0].SetColor(color);

	// �Z���N�gUI
	//----------------------------------------------------
	SelectUI[0].SetMtXPos(-0.6f, 0.1f, 0.0f);
	SelectUI[0].SetMtXScale(0.8, 0.15, 0);
	if (Selecter == 0)
		SelectUI[0].SetColor(SELECT);
	else
		SelectUI[0].SetColor(DEFAULT);
	//----------------------------------------------------
	SelectUI[1].SetMtXPos(-0.6f, -0.1f, 0.0f);
	SelectUI[1].SetMtXScale(0.8, 0.15, 0);
	if (Selecter == 1)
		SelectUI[1].SetColor(SELECT);
	else
		SelectUI[1].SetColor(DEFAULT);
	//----------------------------------------------------
	SelectUI[2].SetMtXPos(-0.6f, -0.3f, 0.0f);
	SelectUI[2].SetMtXScale(0.8, 0.15, 0);
	if (Selecter == 2)
		SelectUI[2].SetColor(SELECT);
	else
		SelectUI[2].SetColor(DEFAULT);
	//----------------------------------------------------
}
void TitleUIDraw(void)
{
	for (size_t i = 0; i < MAX_TITLE_LOGO_UI; i++)
	{
		TitleUI[i].Draw();
	}
	for (size_t i = 0; i < MAX_TITLE_SELECT_UI; i++)
	{
		SelectUI[i].Draw();
	}
}
