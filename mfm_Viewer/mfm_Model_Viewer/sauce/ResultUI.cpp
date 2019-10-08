//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : 
//
//=============================================================================
#include "Include.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// UI�E�e�N�X�`��
// �^�C�g���pUI���u��
#define TITLEUI1 ("resource\\Title\\titleUI_1.png")
#define TITLEUI2 ("resource\\Title\\titleUI_2.png")

#define MAX_RESULT_RANKING_UI	(3)	// ����
#define MAX_RESULT_SELECT_UI	(1)	// �I���q
#define MAX_RESULT_HELP_UI	(1)	// �w���v

#define MAX_UI	(MAX_RESULT_RANKING_UI + MAX_RESULT_SELECT_UI + MAX_RESULT_HELP_UI)

// UI�ꊇ�ݒ�////////////////////////////////////////////////////////////////////////////////////
#define RANKING_SCALE_X	(0.8f)
#define RANKING_SCALE_Y	(0.25f)
/////////////////////////////////////////////////////////////////////////////////////////////////
#define KEY_OK			(DIK_RETURN)		// ����       : [ ENTER ]�L�[
#define KEY_CANCEL		(DIK_BACKSPACE)		// �L�����Z�� : [ BACKSPACE ]�L�[
#define KEY_UP			(DIK_W)				// ��         : [ UP ]�L�[
#define KEY_DOWN		(DIK_S)				// ��         : [ DOWN ]�L�[
#define KEY_RIGHT		(DIK_D)				// ��         : [ RIGHT ]�L�[
#define KEY_LEFT		(DIK_A)				// ��         : [ LEFT ]�L�[

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
VERTEXDATA ResultUIDATA[MAX_UI];
RenderUI* RankingUI;
RenderUI* RSelectUI;

//=============================================================================
// ����������
//=============================================================================
void InitResultUI(void)
{
	// �e�N�X�`������
	CreateMeshBoard(&ResultUIDATA[0], TITLEUI1);
	CreateMeshBoard(&ResultUIDATA[1], TITLEUI2);

	// �������m��
	RankingUI = new RenderUI[MAX_RESULT_RANKING_UI];
	RankingUI[0].SetRendData(&ResultUIDATA[0]);
	RankingUI[1].SetRendData(&ResultUIDATA[0]);
	RankingUI[2].SetRendData(&ResultUIDATA[0]);

	RSelectUI = new RenderUI[MAX_RESULT_SELECT_UI];
	RSelectUI[0].SetRendData(&ResultUIDATA[1]);
	//RSelectUI[1].SetRendData(&ResultUIDATA[1]);

	// 1��------------------------------------------
	RankingUI[0].SetMtXPos(D3DXVECTOR3(0.0f, 0.4f, NULL));
	RankingUI[0].SetMtXScale(D3DXVECTOR3(RANKING_SCALE_X, RANKING_SCALE_Y, NULL));
	// 2��------------------------------------------
	RankingUI[1].SetMtXPos(D3DXVECTOR3(-0.5f, 0.1f, NULL));
	RankingUI[1].SetMtXScale(D3DXVECTOR3(RANKING_SCALE_X, RANKING_SCALE_Y, NULL));
	// 3��------------------------------------------
	RankingUI[2].SetMtXPos(D3DXVECTOR3(0.5f, 0.1f, NULL));
	RankingUI[2].SetMtXScale(D3DXVECTOR3(RANKING_SCALE_X, RANKING_SCALE_Y, NULL));

	// �I����
	RSelectUI[0].SetMtXPos(D3DXVECTOR3(-0.65f, -0.4f, NULL));
	RSelectUI[0].SetMtXScale(D3DXVECTOR3(0.5f, 0.15f, NULL));
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultUI(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultUI(void)
{
	// ����
	if (GetKeyboardTrigger(KEY_OK))
	{
		Fade(FADE_IN, D3DCOLOR_RGBA(0, 0, 0, 0));
		SetKeyboardActive(KEYBOARDOFF);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultUI(void)
{
	for (int i = 0; i < MAX_RESULT_RANKING_UI; i++)
	{
		RankingUI[i].Draw();
	}
	for (int i = 0; i < MAX_RESULT_SELECT_UI; i++)
	{
		RSelectUI[i].Draw();
	}
}
