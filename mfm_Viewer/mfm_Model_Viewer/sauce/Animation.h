#ifndef __ANIMETION_H__
#define __ANIMETION_H__

#include "DrawData.h"

//�h�����b�V���R���e�i�[�\����(
//�R���e�i�[���e�N�X�`���𕡐����Ă�悤�Ƀ|�C���^�[�̃|�C���^�[��ǉ�����j
struct MESHCONTAINERDERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight;//�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
	DWORD dwBoneAmt;//�{�[���̐�
	LPD3DXBUFFER pBoneBuffer;//�{�[���E�e�[�u��
	D3DXMATRIX** ppBoneMatrix;//�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
	D3DXMATRIX* pBoneOffsetMatrices;//�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
};

//�h���t���[���\���� (���ꂼ��̃��b�V���p�̍ŏI���[���h�s���ǉ�����j
struct FRAMEDERIVED : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};

class HIERARCHYDERIVED : public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(
		THIS_ LPCTSTR, 
		CONST D3DXMESHDATA*, 
		CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, 
		DWORD, 
		CONST DWORD *, 
		LPD3DXSKININFO, 
		LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
};

//�{�[���̗̈�m��
HRESULT AllocateBoneMatrix(FRAMEDATA* InData, LPD3DXMESHCONTAINER);
//���ׂẴ{�[���̗̈�m��
HRESULT AllocateAllBoneMatrices(FRAMEDATA* InData, LPD3DXFRAME);


#endif//__ANIMETION_H__
