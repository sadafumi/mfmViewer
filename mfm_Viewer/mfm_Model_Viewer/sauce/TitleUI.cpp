#include "Include.h"

// UI�E�e�N�X�`��
#define TITLEUI1 ("resource\\Title\\titleUI_1.png")
#define TITLEUI2 ("resource\\Title\\titleUI_2.png")

#define MAX_TITLE_LOGO_UI	(1)	// �^�C�g�����S
#define MAX_TITLE_SELECT_UI	(3)	// �I���q
#define MAX_TITLE_HELP_UI	(1)	// �w���v

#define MAX_UI		(MAX_TITLE_LOGO_UI + MAX_TITLE_SELECT_UI + MAX_TITLE_HELP_UI)

// UI�ꊇ�ݒ�////////////////////////////////////////////////////////////////////////////////////
#define SELECT_SPEED		( 0.4f ) // �I�����ꂽ���̕ω����x

// ���S����
#define TITLELOGO_COLOR   D3DCOLOR_ARGB(255, 255, 0, 0)
#define TITLELOGO_SCALE_X (  1.2f)
#define TITLELOGO_SCALE_Y ( 0.25f)
#define TITLELOGO_POS_X   ( -0.4f)
#define TITLELOGO_POS_Y   ( 0.45f)

// �I��������
#define SELECTER_NONECOLOR   D3DCOLOR_RGBA(255, 255, 255, 255)	// ��I�����̐F
#define SELECTER_NONESCALE_X ( 0.65f)						// ��I�����̑傫��
#define SELECTER_NONESCALE_Y ( 0.12f)						// ��I�����̑傫��
#define SELECTER_NONEPOS_X   ( -0.60f)
#define SELECTER_NONEPOS_Y   (  0.0f)
#define SELECTER_COLOR       D3DCOLOR_RGBA(255, 0, 0, 255)	// �I�����̐F
#define SELECTER_SCALE_X     (  0.8f)						// �I�����̑傫��
#define SELECTER_SCALE_Y     ( 0.15f)						// �I�����̑傫��
#define SELECTER_POS_X       ( -0.45f)
#define SELECTER_POS_Y       ( -0.1f)
#define SELECTER_POS_DIFF    (  0.2f)	// �I�������Ƃ̊Ԋu

// �w���v����
#define HELP_COLOR   D3DCOLOR_ARGB(255, 255, 0, 0)
#define HELP_SCALE_X (  0.8f)
#define HELP_SCALE_Y ( 0.15f)
#define HELP_POS_X   ( -0.4f)
#define HELP_POS_Y   ( 0.45f)
/////////////////////////////////////////////////////////////////////////////////////////////////

// ���̓}�N�� �e���v���[�g
// �L�[�{�[�h����
#define KEY_OK			(DIK_RETURN)		// ����       : [ ENTER ]�L�[
#define KEY_CANCEL		(DIK_BACKSPACE)		// �L�����Z�� : [ BACKSPACE ]�L�[
#define KEY_UP			(DIK_W)				// ��         : [ UP ]�L�[
#define KEY_DOWN		(DIK_S)				// ��         : [ DOWN ]�L�[
#define KEY_RIGHT		(DIK_D)				// ��         : [ RIGHT ]�L�[
#define KEY_LEFT		(DIK_A)				// ��         : [ LEFT ]�L�[
// �R���g���[���[����
#define CNT_OK			(XINPUT_GAMEPAD_B)			// ����       : [ B ]�{�^��
#define CNT_CANCEL		(XINPUT_GAMEPAD_A)			// �L�����Z�� : [ A ]�{�^��
#define CNT_UP			(XINPUT_GAMEPAD_DPAD_UP)	// ��         : �\��[ �� ]�{�^��
#define CNT_DOWN		(XINPUT_GAMEPAD_DPAD_DOWN)	// ��         : �\��[ �� ]�{�^��
#define CNT_RIGHT		(XINPUT_GAMEPAD_DPAD_RIGHT)	// ��         : �\��[ �� ]�{�^��
#define CNT_LEFT		(XINPUT_GAMEPAD_DPAD_LEFT)	// ��         : �\��[ �� ]�{�^��

// �I����
#define GAMESTART	( 0 )
#define OPTION		( 1 )
#define GAMEEND		( 2 )

// �ϐ��錾
RenderUI  *TitleUI;
RenderUI  *SelectUI;
VERTEXDATA TitleUIDATA[MAX_UI];
Controller TitleControl;

// �I���Ǘ�
short Selecter = 0;

void TitleUIInit(void)
{
	short Selecter = 0;

	// �e�N�X�`������
	CreateMeshBoard(&TitleUIDATA[0], TITLEUI1);
	CreateMeshBoard(&TitleUIDATA[1], TITLEUI2);

	// �������m��
	TitleUI = new RenderUI[MAX_TITLE_LOGO_UI];
	TitleUI[0].SetRendData(&TitleUIDATA[0]);

	SelectUI = new RenderUI[MAX_TITLE_SELECT_UI];
	SelectUI[0].SetRendData(&TitleUIDATA[1]);
	SelectUI[1].SetRendData(&TitleUIDATA[1]);
	SelectUI[2].SetRendData(&TitleUIDATA[1]);

	// �^�C�g�����S
	TitleUI[0].SetMtXPos(D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, NULL));
	TitleUI[0].SetMtXScale(D3DXVECTOR3(TITLELOGO_SCALE_X, TITLELOGO_SCALE_Y, NULL));
	// �Q�[���X�^�[�g--------------------------------------
	SelectUI[0].SetMtXPos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y + SELECTER_POS_DIFF, NULL));
	SelectUI[0].SetMtXScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	//�I�v�V����------------------------------------------
	SelectUI[1].SetMtXPos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y, NULL));
	SelectUI[1].SetMtXScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	//�Q�[���I��------------------------------------------
	SelectUI[2].SetMtXPos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y - SELECTER_POS_DIFF, NULL));
	SelectUI[2].SetMtXScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
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
	// ���� : �L�[�{�[�h===============================================================
	{
		// �I��
		if (GetKeyboardTrigger(KEY_UP) || TitleControl.GetTriggerButton(CNT_UP))
		{
			Selecter--;
			if (Selecter < 0)Selecter = 2;
		}
		if (GetKeyboardTrigger(KEY_DOWN) || TitleControl.GetTriggerButton(CNT_DOWN))
		{
			Selecter++;
			if (Selecter > 2)Selecter = 0;
		}

		// ����
		if (GetKeyboardTrigger(KEY_OK) || TitleControl.GetTriggerButton(CNT_OK))
		{
			if (Selecter == GAMESTART) 
			{
				Fade(FADE_IN, D3DCOLOR_RGBA(0,0,0,0));
				SetKeyboardActive(KEYBOARDOFF);
			}		// �I����ʂ�
			if (Selecter == OPTION) 
			{
				//ChangeScene(SCENE_RESULT);	// �I�v�V������ʂ�
				//�V�[���������ڃI�v�V�������j���[���J��
			}
			if (Selecter == GAMEEND)
			{
				PostQuitMessage(WM_QUIT);
			}
		}
		if (GetKeyboardTrigger(KEY_DOWN))
		{

		}
	}
	//================================================================================

	// �^�C�g�����S
	TitleUI[0].SetColor(TITLELOGO_COLOR);

	// �I�����
	if (Selecter == 0)
	{
		SelectUI[0].SetMovePos(D3DXVECTOR3(SELECTER_POS_X, SELECTER_NONEPOS_Y + SELECTER_POS_DIFF, NULL));
		SelectUI[0].SetMoveScale(D3DXVECTOR3(SELECTER_SCALE_X, SELECTER_SCALE_Y, NULL));
		SelectUI[0].SetColor(SELECTER_COLOR);
	}
	else
	{
		SelectUI[0].SetMovePos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y + SELECTER_POS_DIFF, NULL));
		SelectUI[0].SetMoveScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	}
	//  �I�v�V�������
	if (Selecter == 1)
	{
		SelectUI[1].SetMovePos(D3DXVECTOR3(SELECTER_POS_X, SELECTER_NONEPOS_Y, NULL));
		SelectUI[1].SetMoveScale(D3DXVECTOR3(SELECTER_SCALE_X, SELECTER_SCALE_Y, NULL));
		SelectUI[1].SetColor(SELECTER_COLOR);
	}
	else
	{
		SelectUI[1].SetMovePos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y, NULL));
		SelectUI[1].SetMoveScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	}
	// �I��
	if (Selecter == 2)
	{
		SelectUI[2].SetMovePos(D3DXVECTOR3(SELECTER_POS_X, SELECTER_NONEPOS_Y - SELECTER_POS_DIFF, NULL));
		SelectUI[2].SetMoveScale(D3DXVECTOR3(SELECTER_SCALE_X, SELECTER_SCALE_Y, NULL));
		SelectUI[2].SetColor(SELECTER_COLOR);
	}
	else
	{
		SelectUI[2].SetMovePos(D3DXVECTOR3(SELECTER_NONEPOS_X, SELECTER_NONEPOS_Y - SELECTER_POS_DIFF, NULL));
		SelectUI[2].SetMoveScale(D3DXVECTOR3(SELECTER_NONESCALE_X, SELECTER_NONESCALE_Y, NULL));
	}
	//----------------------------------------------------

	//UI�ړ�
	for (size_t i = 0; i < MAX_TITLE_SELECT_UI; i++)
	{
		SelectUI[i].Move(SELECT_SPEED);
	}
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
