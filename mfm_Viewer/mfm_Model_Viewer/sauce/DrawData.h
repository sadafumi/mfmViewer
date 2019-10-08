//-----------------------------------------------------------------------------
// AT12A242 宗貞史樹　2017/6/27 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// メインヘッダ			　　
//-----------------------------------------------------------------------------
#ifndef __DRAWDATA_H__
#define __DRAWDATA_H__

#include <Windows.h> //ウィンドウズAPI
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
	int IndeXsize;							//インデックス数
	int vtXsize;							//頂点数
	int TexSizeX;							//テクスチャサイズX
	int TexSizeY;							//テクスチャサイズY
	LPDIRECT3DVERTEXBUFFER9 pVetTexBuffer;	//頂点バッファ
	LPDIRECT3DINDEXBUFFER9  pIndexBuffer;	//インデックスバッファ
	LPDIRECT3DTEXTURE9      pTexture;		//テクスチャ
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
	D3DMATERIAL9		*pMeshMaterials;		//マテリアル情報のポインタ
	LPDIRECT3DTEXTURE9	*pMeshTextures;		//テクスチャ情報のポインタ
	DWORD				 dwNumMaterials;		//マテリアル数
	LPD3DXMESH		     pMesh;				//メッシュ情報
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
