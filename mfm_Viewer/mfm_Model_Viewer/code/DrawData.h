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
#include "main.h"

#define MAX_BONE (4)

struct Bone
{
	std::vector<D3DXMATRIX> MatAry;
};
struct Impact
{
	float weight[MAX_BONE];
	int matrixIndex[MAX_BONE];
};

struct VERTEX2D
{
	D3DXVECTOR4 Pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
};

struct VERTEX3D
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;

};

struct VERTEXANI
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
	Impact ImpactMap;
};

struct TEXTURE
{
	const char fileName[256];
	int widht;
	int heght;
};

struct TEXUV
{
	float U0;
	float V0;
	float U1;
	float V1;
};

struct vertexbuff
{
	std::vector< VERTEX3D > Vertex;
};

struct Shaderbuff
{
	std::vector< VERTEXANI > Vertex;
};

struct Mesh_DirectX9
{
	int MaterialIndex;
	int PrimitiveNum;
	std::string TexName;
};
namespace DATA_TYPE
{
	class VERTEXSHADERDATA
	{
	public:
		IDirect3DVertexShader9* pVertexShader;
	};
	class PIXELSHADERDATA
	{
	public:
		IDirect3DPixelShader9* pPixelShader;

	};
	class DECLARATIONDATA
	{
	public:
		IDirect3DVertexDeclaration9 *pDeclaration;
	};

	class SURFACEDATA
	{
	public:
		LPDIRECT3DSURFACE9		Surface;
		void Destroy();
	};

	class TEXTUREDATA
	{
	public:
		int TexSizeX;							//テクスチャサイズX
		int TexSizeY;							//テクスチャサイズY
		LPDIRECT3DTEXTURE9      pTexture;		//テクスチャ
		void Destroy();
	};

	class RENDERTARGETTEXTUREDATA
	{
	public:
		TEXTUREDATA Texture;		//テクスチャ
		SURFACEDATA Surface;
		void Destroy();
	};

	class VERTEX2DDATA
	{
	public:
		int TexSizeX;							//テクスチャサイズX
		int TexSizeY;							//テクスチャサイズY
		LPDIRECT3DVERTEXBUFFER9 pVetTexBuffer;	//頂点バッファ
		LPDIRECT3DTEXTURE9      pTexture;		//テクスチャ
		void Destroy();
	};

	class VERTEXDATA
	{
	public:
		int IndeXsize;							//インデックス数
		int vtXsize;							//頂点数
		int TexSizeX;							//テクスチャサイズX
		int TexSizeY;							//テクスチャサイズY
		std::vector<WORD>		index;
		std::vector<VERTEX3D>	vtx;
		LPDIRECT3DVERTEXBUFFER9 pVetTexBuffer;	//頂点バッファ
		LPDIRECT3DINDEXBUFFER9  pIndexBuffer;	//インデックスバッファ
		LPDIRECT3DTEXTURE9      pTexture;		//テクスチャ
		LPDIRECT3DTEXTURE9      pBump_Map;		//テクスチャ
		void Destroy();
	};
	class MFMMESHDATA
	{
	public:
		std::vector< Mesh_DirectX9 > MeshData;
		std::vector< D3DMATERIAL9 >  Material;
		std::vector< LPDIRECT3DVERTEXBUFFER9 > VertexBuffer;
		std::vector< LPDIRECT3DTEXTURE9 >      Texture;
		void Destroy();
	};
	class MFMANIMEDATA
	{
	public:
		std::vector< Mesh_DirectX9 > MeshData;
		std::vector< D3DMATERIAL9 >  Material;
		std::vector< LPDIRECT3DVERTEXBUFFER9 > VertexBuffer;
		std::vector< LPDIRECT3DTEXTURE9 >      Texture;
		std::vector< std::vector< Bone > > bone;
		int nAnimFrame = 1;
		void Destroy();
	};

}
namespace FVF_DEF
{
#define FVF_VERTEX_3D	 ( D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_DIFFUSE | D3DFVF_TEX1 )//D3DFVF_XYZRHWがいらない//3D用のFVF
	//#define FVF_VERTEX_3D	 ( D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2 | D3DFVF_TEX3 )//D3DFVF_XYZRHWがいらない//3D用のFVF
#define FVF_VERTEX_ANIME ( D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_LASTBETA_D3DCOLOR )//D3DFVF_XYZRHWがいらない//3D用のFVF
#define FVF_VERTEX_2D	 ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
}
#endif //__DRAWDATA_H__
