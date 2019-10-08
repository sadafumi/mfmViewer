#ifndef __RENDER_H__
#define __RENDER_H__

#include "DrawData.h"
#include "main.h"
#include "Animation.h"

#define COLORMASK  (00000011)
#define ALPHAMASK  (11111100)
#define ALLPASMASK (00000000)


//�������璸�_
class BaseData
{
public:
	void init();
	void SetLight(D3DLIGHT9 in);		//Light���Z�b�g
	void SetMtXWorld(D3DXMATRIX World);
		//���[���h�s����Z�b�g
	void SetMtXView(D3DXMATRIX View);		//�r���[�s����Z�b�g
	void SetMtXWProj(D3DXMATRIX Proj);		//�v���W�F�N�V�����s����Z�b�g
protected:
	D3DXMATRIX g_mtxWorld;			//���[���h�s��
	D3DXMATRIX g_mtxView;			//�r���[�s��
	D3DXMATRIX g_mtxProj;			//�v���W�F�N�V�����s��
	D3DLIGHT9 Light;
};
class RenderVtx:public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);	//�f�[�^���Z�b�g��������
	void Draw();							//�`��
	
private:
	VERTEXDATA *VerTexData;			//���_�f�[�^
};
//�����܂Ń��b�V��
//�������烁�b�V��
class RenderMesh :public BaseData
{
public:
	void SetRendData(MESHDATA *MeshData);	//�f�[�^���Z�b�g��������
	void Draw();							//�`��
private:
	MESHDATA *MeshData;				//���b�V���f�[�^
	
};
//�����܂Ń��b�V��
//��������t���[�����b�V��
class RenderFrameMesh :public BaseData
{
public:
	void SetRendData(FRAMEDATA *FrameMeshData);	//�f�[�^���Z�b�g��������
	void Draw();							//�`��
private:
	void Updata(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void Convert(LPD3DXFRAME pFrameBase);
	void Render(MESHCONTAINERDERIVED* pMeshContainer, FRAMEDERIVED* pFrame);
	FRAMEDATA *FrameMeshData;				//���b�V���f�[�^

};
//�����܂Ńt���[�����b�V��
//�������璸�_�X�g���[��
class RenderVtxStrip :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);	//�f�[�^���Z�b�g��������
	void Draw();							//�`��
private:
	VERTEXDATA *VerTexData;			//���_�f�[�^	
};
//�����܂Œ��_�X�g���[��
//��������r���{�[�h
class RenderBillBoard :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);			//�f�[�^���Z�b�g��������
	void Draw();									//�`��
	void SetMtXScale(float x, float y, float z);	//�X�P�[���Z�b�g
	void SetMtXPos(float x, float y, float z);		//�ړ��Z�b�g
	void SetMtXRotation(float x, float y, float z);	//��]�Z�b�g
private:
	VERTEXDATA *VerTexData;			//���_�f�[�^
	D3DXMATRIX g_mtxPos;			//�ړ��s��
	D3DXMATRIX g_mtxScale;			//�g��s��
	D3DXMATRIX g_mtxRotation;		//��]�s��
};
//�����܂Ńr���{�[�h
//��������r���{�[�h�A�j���[�V����
class RenderBillAnimation :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData, int aniIndex, int X, int Y);			//�f�[�^���Z�b�g��������
	void Draw();									//�`��
	void SetAnimationSpeed(float Speed);			//�A�j���[�V�����X�s�[�h
	void SetMtXScale(float x, float y, float z);	//�X�P�[���Z�b�g
	void SetMtXPos(float x, float y, float z);		//�ړ��Z�b�g
	void SetMtXRotation(float x, float y, float z);	//��]�Z�b�g
	void SetMtXView(D3DXMATRIX View);				//�r���[�s����Z�b�g
	void SetMtXWProj(D3DXMATRIX Proj);				//�v���W�F�N�V�����s����Z�b�g
private:
	VERTEXDATA *VerTexData;			//���_�f�[�^
	float      AniSpeed;			//�A�j���[�V����
	int		   AniCount;			//�A�j���[�V�����J�E���g
	int		   AniIndex;			//�A�j���[�V�����ő吔
	int		   AniCountX;
	int		   AniCountY;
	D3DXMATRIX g_mtxPos;			//�ړ��s��
	D3DXMATRIX g_mtxScale;			//�g��s��
	D3DXMATRIX g_mtxRotation;		//��]�s��
};
//�����܂Ńr���{�[�h�A�j���[�V����
//��������UI
class RenderUI:public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);			//�f�[�^���Z�b�g��������
	void Draw();									//�`��
	void SetMoveScale(D3DXVECTOR3 pos);				// �g�k��Z�b�g
	void SetMovePos(D3DXVECTOR3 scale);				// �ړ���Z�b�g
	void Move(float MoveSpeed);						// ���A���^�C������
	void SetMtXScale(D3DXVECTOR3 pos);				// ���ۂ̃X�P�[���Z�b�g
	void SetMtXPos(D3DXVECTOR3 scale);				// ���ۂ̈ړ��Z�b�g
	void SetMtXRotation(D3DXVECTOR3 rot);			// ��]�Z�b�g
	void SetColor(D3DCOLOR InColor);				//�J���[�R�[�h���Z�b�g
	void SetMtXView(D3DXMATRIX View);				//�r���[�s����Z�b�g
	void SetMtXWProj(D3DXMATRIX Proj);				//�v���W�F�N�V�����s����Z�b�g
private:
	D3DXVECTOR3 ScalingPos;			// ���ۂ̊g�k���
	D3DXVECTOR3 ScalingSet;			// �ړI�g�k���
	D3DXVECTOR3 TranslationPos;		// ���ۂ̕��s�ړ�
	D3DXVECTOR3 TranslationSet;		// �ړI�ʒu

	VERTEXDATA *VerTexData;			//���_�f�[�^
	D3DXMATRIX g_mtxPos;			//�ړ��s��
	D3DXMATRIX g_mtxScale;			//�g��s��
	D3DXMATRIX g_mtxRotation;		//��]�s��
	D3DCOLOR   d3dColor;			//��b�̃J���[
};
//�����܂�UI
//�������猸�Z����
class RenderSubsyn :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);	//�f�[�^���Z�b�g��������
	void Draw();							//�`��
private:
	VERTEXDATA *VerTexData;			//���_�f�[�^

};
class Rendermfm :public BaseData
{
public:
	void SetRendData(MFMMESHDATA *inData);	//�f�[�^���Z�b�g��������
	void Draw();							//�`��
private:
	MFMMESHDATA *pmfmData;			//���_�f�[�^

};

//�����܂Ō��Z����

#endif//__RENDER_H__

