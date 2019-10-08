//-----------------------------------------------------------------------------
// AT12A242 �@��j���@2017/6/27 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ���C���w�b�_			�@�@
//-----------------------------------------------------------------------------
#ifndef __DRAWDATA_H__
#define __DRAWDATA_H__

#include <Windows.h> //�E�B���h�E�YAPI
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <vector>
#include <dinput.h>
#include <Xinput.h>
#include <XAudio2.h>
#include <math.h>
#include <string>


typedef struct
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;

}VERTEX3D;

typedef struct
{
	const char fileName[256];
	int widht;
	int heght;
}TEXTURE;

typedef struct
{
	float U0;
	float V0;
	float U1;
	float V1;
}TEXUV;

struct vertexbuff {
	std::vector< VERTEX3D > Vertex;
};

struct Mesh_DirectX9
{
	int MaterialIndex;
	int PrimitiveNum;
	std::string TexName;
};

class VERTEXDATA
{
public:
	int IndeXsize;							//�C���f�b�N�X��
	int vtXsize;							//���_��
	int TexSizeX;							//�e�N�X�`���T�C�YX
	int TexSizeY;							//�e�N�X�`���T�C�YY
	LPDIRECT3DVERTEXBUFFER9 pVetTexBuffer;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9  pIndexBuffer;	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9      pTexture;		//�e�N�X�`��
	void Destroy();
};
class MFMMESHDATA
{
public:
	std::vector< Mesh_DirectX9 > matchData;
	std::vector< D3DMATERIAL9 >  Material;
	std::vector< LPDIRECT3DVERTEXBUFFER9 > VertexBuffer;
	std::vector< LPDIRECT3DTEXTURE9 >      Texture;
	void Destroy();
};
class MESHDATA
{
public:
	D3DMATERIAL9		*pMeshMaterials;		//�}�e���A�����̃|�C���^
	LPDIRECT3DTEXTURE9	*pMeshTextures;		//�e�N�X�`�����̃|�C���^
	DWORD				 dwNumMaterials;		//�}�e���A����
	LPD3DXMESH		     pMesh;				//���b�V�����
	void Destroy();
};
class FRAMEDATA
{
public:
	LPD3DXMESH					 pMesh;
	LPD3DXFRAME					 pFrameRoot;
	LPD3DXANIMATIONCONTROLLER	 pAnimController;
	D3DMATERIAL9				*pMeshMaterials;
	LPDIRECT3DTEXTURE9			*pMeshTextures;
	DWORD						 dwNumMaterials;
	void Destroy();
};


#endif //__DRAWDATA_H__
