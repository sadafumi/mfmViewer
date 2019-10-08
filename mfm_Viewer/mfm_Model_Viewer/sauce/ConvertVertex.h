//================================================================================
//
//    頂点データ変換
//    Author : Araki Kai                                作成日 : 2018/01/15
//
//================================================================================

#ifndef	_CONVERT_VERTEX_H_
#define _CONVERT_VERTEX_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "Include.h"


//**********************************************************************
//
// 構造体宣言
//
//**********************************************************************

struct VERTEX_3D
{
	D3DXVECTOR3  position_;		// 座標
	D3DXVECTOR3  normal_;		// 法線
	D3DCOLOR     color_;		// カラー
	D3DXVECTOR2  texcoord_;		// テクスチャ座標
};



struct Mesh_DirectX9
{
	std::vector< VERTEX_3D > vertex_;
	int material_index_;
	int primitive_num_;
	std::string tex_name_;
};

struct Model_DirectX9
{
	std::vector< Mesh_DirectX9 > mesh_;
	std::vector< D3DMATERIAL9 >  material_;

	std::vector< LPDIRECT3DVERTEXBUFFER9 > vertex_buffer_;
	std::vector< LPDIRECT3DTEXTURE9 >      texture_;
};


//**********************************************************************
//
// プロトタイプ宣言
//
//**********************************************************************

//================================================================================
//
// [ ダイレクトX9頂点データ変換関数 ]
//
//================================================================================

void ConvertVertexDirectX9( Model_DirectX9* model, Model* fbx_model );
void ConvertMesh(Model_DirectX9* model, Model* fbx_model);
void ConvertMaterial(
	
	
	
	_DirectX9* model, Model* fbx_model);
void CreateVertexBuffer_DirectX9(Model_DirectX9* model);
void ReleaseVertexBuffer_DirectX9(Model_DirectX9* model);
void DrawModel_DirectX9(Model_DirectX9* model);


#endif