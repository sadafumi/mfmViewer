
//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "Include.h"


//**********************************************************************
//
// 定数定義
//
//**********************************************************************





//**********************************************************************
//
// プロトタイプ宣言
//
//**********************************************************************



static D3DXMATRIX g_mtxWorld, g_mtxProj, g_mtxView;



//================================================================================
//
// [ ダイレクトX9頂点データ変換関数 ]
//
//================================================================================

void ConvertVertexDirectX9( Model_DirectX9* model, Model* fbx_model )
{
	ConvertMaterial(model, fbx_model);
	ConvertMesh( model, fbx_model );
	D3DXMatrixIdentity(&g_mtxWorld);					//ワールド行列を初期化
	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);					//カメラ座標
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);					//注視点
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);					//カメラの向き
	D3DXMatrixLookAtLH(&g_mtxView, &eye, &at, &up);     //ビュー行列の初期化
	D3DXMatrixPerspectiveFovLH(&g_mtxProj,				//プロジェクション行列の初期化
		D3DXToRadian((120) / 2),
		(float)SCREEN_WIDTH / SCREEN_HIEGTH,
		0.1f,
		1000);

}



//================================================================================
//
// [ ダイレクトX9頂点データ変換関数 ]
//
//================================================================================

void ConvertMesh( Model_DirectX9* model, Model* fbx_model )
{
	// メッシュ数の確定
	model -> mesh_.resize( fbx_model -> MeshNum.GetNum() );

	// メッシュ数分回す
	for( int i = 0; i < ( int )model -> mesh_.size(); i++ )
	{
		// インデックス数分回す
		
		model -> mesh_[ i ].vertex_.resize(fbx_model->MeshData[i].Index.Num.GetNum());
		
		int temp_material_index = fbx_model->MeshData[i].MaterialIndex.GetNum();
		// メッシュインデックス番号取得
		model->mesh_[i].material_index_ = temp_material_index;


		for ( int j = 0; j <( int ) model -> mesh_[ i ].vertex_.size(); j++ )
		{
			// 頂点
			int temp_index_num = fbx_model->MeshData[i].Index.Data[j];
			model -> mesh_[ i ].vertex_[ j ].position_.x = fbx_model->MeshData[i].Vertex.Data[ temp_index_num ].x;
			model -> mesh_[ i ].vertex_[ j ].position_.y = fbx_model->MeshData[i].Vertex.Data[ temp_index_num ].y;
			model -> mesh_[ i ].vertex_[ j ].position_.z = fbx_model->MeshData[i].Vertex.Data[ temp_index_num ].z;

			// 法線
			model -> mesh_[ i ].vertex_[ j ].normal_.x = fbx_model->MeshData[i].Normals.Data[j].x;
			model -> mesh_[ i ].vertex_[ j ].normal_.y = fbx_model->MeshData[i].Normals.Data[j].y;
			model -> mesh_[ i ].vertex_[ j ].normal_.z = fbx_model->MeshData[i].Normals.Data[j].z;

			// UV
			model -> mesh_[ i ].vertex_[ j ].texcoord_.x = fbx_model->MeshData[i].TexUV.Data[j].U ;
			model -> mesh_[ i ].vertex_[ j ].texcoord_.y = fbx_model->MeshData[i].TexUV.Data[j].V ;

			//model->mesh_[i].vertex_[j].texcoord_.x = 1.0f;
			//model->mesh_[i].vertex_[j].texcoord_.y = 1.0f;
			
			// カラー
			D3DXCOLOR temp_color;
			temp_color.r = fbx_model->MaterialData[temp_material_index].Color.Diffuse.x;
			temp_color.g = fbx_model->MaterialData[temp_material_index].Color.Diffuse.y;
			temp_color.b = fbx_model->MaterialData[temp_material_index].Color.Diffuse.z;
			temp_color.a = fbx_model->MaterialData[temp_material_index].Color.Transparency;
			
			model -> mesh_[ i ].vertex_[ j ].color_ = (D3DCOLOR)temp_color;
		}

			// テクスチャ名の読み込み
	
		if (fbx_model->MaterialData[temp_material_index].TexName.Get() != "")
		{
			model->mesh_[i].tex_name_ = fbx_model->MaterialData[temp_material_index].TexName.Get();
		}



		// プリミティブ数の取得
		model -> mesh_[ i ].primitive_num_ = fbx_model->MeshData[i].PrimitiveIndex.GetNum();
	}
}



//================================================================================
//
// [ ダイレクトX9マテリアルデータ変換関数 ]
//
//================================================================================

void ConvertMaterial( Model_DirectX9* model, Model* fbx_model )
{
	// マテリアル数の確定
	model -> material_.resize( fbx_model -> materialNum.GetNum() );

	// メッシュ数分回す
	for( int i = 0; i < ( int )model -> material_.size(); i++ )
	{
		// アンビエント
		model -> material_[ i ].Ambient.r = fbx_model->MaterialData[i].Color.Ambient.x;
		model -> material_[ i ].Ambient.g = fbx_model->MaterialData[i].Color.Ambient.y;
		model -> material_[ i ].Ambient.b = fbx_model->MaterialData[i].Color.Ambient.z;
		model -> material_[ i ].Ambient.a = fbx_model->MaterialData[i].Color.Transparency;
														 
		// ディフューズ								   
		model -> material_[ i ].Diffuse.r = fbx_model->MaterialData[i].Color.Diffuse.x;
		model -> material_[ i ].Diffuse.g = fbx_model->MaterialData[i].Color.Diffuse.y;
		model -> material_[ i ].Diffuse.b = fbx_model->MaterialData[i].Color.Diffuse.z;
		model -> material_[ i ].Diffuse.a = fbx_model->MaterialData[i].Color.Transparency;

		// エミッシブ
		model -> material_[ i ].Emissive.r = fbx_model->MaterialData[i].Color.Emissive.x;
		model -> material_[ i ].Emissive.g = fbx_model->MaterialData[i].Color.Emissive.y;
		model -> material_[ i ].Emissive.b = fbx_model->MaterialData[i].Color.Emissive.z;
		model -> material_[ i ].Emissive.a = fbx_model->MaterialData[i].Color.Transparency;

		// スペキュラ
		model -> material_[ i ].Power = fbx_model->MaterialData[i].Color.Shininess;

		// スペキュラ色
		model -> material_[ i ].Specular.r = fbx_model->MaterialData[i].Color.Specular.x;
		model -> material_[ i ].Specular.g = fbx_model->MaterialData[i].Color.Specular.y;
		model -> material_[ i ].Specular.b = fbx_model->MaterialData[i].Color.Specular.z;
		model -> material_[ i ].Specular.a = fbx_model->MaterialData[i].Color.Transparency;
	}
}



//================================================================================
//
// [ バーテックスバッファ作成関数 ]
//
//================================================================================

void CreateVertexBuffer_DirectX9( Model_DirectX9* model )
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	VERTEX3D * pVer;
	
	if ( pDevice == NULL )
	{
		MessageBox( NULL, "D3DDeviceの取得ができませんでした", "エラー", MB_OK );
	}

	model -> vertex_buffer_.resize( model -> mesh_.size() );
	model->texture_.resize(model->mesh_.size());
	for ( int i = 0;  i < ( int )model -> mesh_.size(); i++ )
	{
		// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
		HRESULT  hr = pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * model -> mesh_[ i ].vertex_.size(),
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				
													 D3DPOOL_MANAGED,			
													 &model -> vertex_buffer_[ i ],	
													 NULL );				

		model->vertex_buffer_[i]->Lock(0, 0,(void**)&pVer, D3DLOCK_DISCARD);
		memcpy(pVer, model->mesh_[i].vertex_.data(),sizeof(VERTEX_3D) * model->mesh_[i].vertex_.size());
		model->vertex_buffer_[i]->Unlock();
		
		if (FAILED(D3DXCreateTextureFromFile(pDevice, model->mesh_[i].tex_name_.data(), &model->texture_[i])))
		{
			char err[124];
			sprintf(&err[0], "テクスチャの取得「%s」に失敗しました", model->mesh_[i].tex_name_.data());
			MessageBox(NULL, &err[0], "テクスチャの読み込みに失敗しました", MB_OK);
		}

		if ( FAILED( hr ) )
		{
			MessageBox( NULL, "Vertex buffer was not created.", "Error", MB_OK );
		}
	}
	
}



//================================================================================
//
// [ バーテックスバッファ解放関数 ]
//
//================================================================================

void ReleaseVertexBuffer_DirectX9( Model_DirectX9* model )
{
	for ( int i = 0; i < ( int )model -> vertex_buffer_.size(); i++ )
	{
		if ( model -> vertex_buffer_[ i ] != nullptr )
		{
			model -> vertex_buffer_[ i ] -> Release();
			model -> vertex_buffer_[ i ]  = nullptr;
		}
		
	}

}



//================================================================================
//
// [ モデル描画関数 ]
//
//================================================================================

void DrawModel_DirectX9( Model_DirectX9* model )
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	
	if ( pDevice == NULL )
	{
		MessageBox( NULL, "D3DDeviceの取得ができませんでした", "エラー", MB_OK );
	}

	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DXMatrixScaling(&g_mtxWorld, 0.5, 0.5, 0.5);
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
	
	//ビュー
	g_mtxView = GetViewMtx();
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	//プロジェクション
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProj);
	for ( int i = 0; i < ( int )model -> vertex_buffer_.size(); i++ )
	{
		pDevice -> SetStreamSource( 0, model -> vertex_buffer_[ i ], 0, sizeof( VERTEX_3D ) );
		
		// テクスチャテーブルにセット
		if ( model -> mesh_[ i ].tex_name_ == "" )
		{
			pDevice -> SetTexture( 0, NULL );
		}
		else
		{
			pDevice -> SetTexture( 0, model -> texture_[ i ] );
		}
	
		// マテリアルをデバイスにセット
		pDevice -> SetMaterial( & model -> material_[  model -> mesh_[ i ].material_index_ ] );
		pDevice -> DrawPrimitive( D3DPT_TRIANGLELIST, 0, model -> mesh_[ i ].primitive_num_ );
	}
}