
//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "Include.h"


//**********************************************************************
//
// �萔��`
//
//**********************************************************************





//**********************************************************************
//
// �v���g�^�C�v�錾
//
//**********************************************************************



static D3DXMATRIX g_mtxWorld, g_mtxProj, g_mtxView;



//================================================================================
//
// [ �_�C���N�gX9���_�f�[�^�ϊ��֐� ]
//
//================================================================================

void ConvertVertexDirectX9( Model_DirectX9* model, Model* fbx_model )
{
	ConvertMaterial(model, fbx_model);
	ConvertMesh( model, fbx_model );
	D3DXMatrixIdentity(&g_mtxWorld);					//���[���h�s���������
	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);					//�J�������W
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);					//�����_
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);					//�J�����̌���
	D3DXMatrixLookAtLH(&g_mtxView, &eye, &at, &up);     //�r���[�s��̏�����
	D3DXMatrixPerspectiveFovLH(&g_mtxProj,				//�v���W�F�N�V�����s��̏�����
		D3DXToRadian((120) / 2),
		(float)SCREEN_WIDTH / SCREEN_HIEGTH,
		0.1f,
		1000);

}



//================================================================================
//
// [ �_�C���N�gX9���_�f�[�^�ϊ��֐� ]
//
//================================================================================

void ConvertMesh( Model_DirectX9* model, Model* fbx_model )
{
	// ���b�V�����̊m��
	model -> mesh_.resize( fbx_model -> MeshNum.GetNum() );

	// ���b�V��������
	for( int i = 0; i < ( int )model -> mesh_.size(); i++ )
	{
		// �C���f�b�N�X������
		
		model -> mesh_[ i ].vertex_.resize(fbx_model->MeshData[i].Index.Num.GetNum());
		
		int temp_material_index = fbx_model->MeshData[i].MaterialIndex.GetNum();
		// ���b�V���C���f�b�N�X�ԍ��擾
		model->mesh_[i].material_index_ = temp_material_index;


		for ( int j = 0; j <( int ) model -> mesh_[ i ].vertex_.size(); j++ )
		{
			// ���_
			int temp_index_num = fbx_model->MeshData[i].Index.Data[j];
			model -> mesh_[ i ].vertex_[ j ].position_.x = fbx_model->MeshData[i].Vertex.Data[ temp_index_num ].x;
			model -> mesh_[ i ].vertex_[ j ].position_.y = fbx_model->MeshData[i].Vertex.Data[ temp_index_num ].y;
			model -> mesh_[ i ].vertex_[ j ].position_.z = fbx_model->MeshData[i].Vertex.Data[ temp_index_num ].z;

			// �@��
			model -> mesh_[ i ].vertex_[ j ].normal_.x = fbx_model->MeshData[i].Normals.Data[j].x;
			model -> mesh_[ i ].vertex_[ j ].normal_.y = fbx_model->MeshData[i].Normals.Data[j].y;
			model -> mesh_[ i ].vertex_[ j ].normal_.z = fbx_model->MeshData[i].Normals.Data[j].z;

			// UV
			model -> mesh_[ i ].vertex_[ j ].texcoord_.x = fbx_model->MeshData[i].TexUV.Data[j].U ;
			model -> mesh_[ i ].vertex_[ j ].texcoord_.y = fbx_model->MeshData[i].TexUV.Data[j].V ;

			//model->mesh_[i].vertex_[j].texcoord_.x = 1.0f;
			//model->mesh_[i].vertex_[j].texcoord_.y = 1.0f;
			
			// �J���[
			D3DXCOLOR temp_color;
			temp_color.r = fbx_model->MaterialData[temp_material_index].Color.Diffuse.x;
			temp_color.g = fbx_model->MaterialData[temp_material_index].Color.Diffuse.y;
			temp_color.b = fbx_model->MaterialData[temp_material_index].Color.Diffuse.z;
			temp_color.a = fbx_model->MaterialData[temp_material_index].Color.Transparency;
			
			model -> mesh_[ i ].vertex_[ j ].color_ = (D3DCOLOR)temp_color;
		}

			// �e�N�X�`�����̓ǂݍ���
	
		if (fbx_model->MaterialData[temp_material_index].TexName.Get() != "")
		{
			model->mesh_[i].tex_name_ = fbx_model->MaterialData[temp_material_index].TexName.Get();
		}



		// �v���~�e�B�u���̎擾
		model -> mesh_[ i ].primitive_num_ = fbx_model->MeshData[i].PrimitiveIndex.GetNum();
	}
}



//================================================================================
//
// [ �_�C���N�gX9�}�e���A���f�[�^�ϊ��֐� ]
//
//================================================================================

void ConvertMaterial( Model_DirectX9* model, Model* fbx_model )
{
	// �}�e���A�����̊m��
	model -> material_.resize( fbx_model -> materialNum.GetNum() );

	// ���b�V��������
	for( int i = 0; i < ( int )model -> material_.size(); i++ )
	{
		// �A���r�G���g
		model -> material_[ i ].Ambient.r = fbx_model->MaterialData[i].Color.Ambient.x;
		model -> material_[ i ].Ambient.g = fbx_model->MaterialData[i].Color.Ambient.y;
		model -> material_[ i ].Ambient.b = fbx_model->MaterialData[i].Color.Ambient.z;
		model -> material_[ i ].Ambient.a = fbx_model->MaterialData[i].Color.Transparency;
														 
		// �f�B�t���[�Y								   
		model -> material_[ i ].Diffuse.r = fbx_model->MaterialData[i].Color.Diffuse.x;
		model -> material_[ i ].Diffuse.g = fbx_model->MaterialData[i].Color.Diffuse.y;
		model -> material_[ i ].Diffuse.b = fbx_model->MaterialData[i].Color.Diffuse.z;
		model -> material_[ i ].Diffuse.a = fbx_model->MaterialData[i].Color.Transparency;

		// �G�~�b�V�u
		model -> material_[ i ].Emissive.r = fbx_model->MaterialData[i].Color.Emissive.x;
		model -> material_[ i ].Emissive.g = fbx_model->MaterialData[i].Color.Emissive.y;
		model -> material_[ i ].Emissive.b = fbx_model->MaterialData[i].Color.Emissive.z;
		model -> material_[ i ].Emissive.a = fbx_model->MaterialData[i].Color.Transparency;

		// �X�y�L����
		model -> material_[ i ].Power = fbx_model->MaterialData[i].Color.Shininess;

		// �X�y�L�����F
		model -> material_[ i ].Specular.r = fbx_model->MaterialData[i].Color.Specular.x;
		model -> material_[ i ].Specular.g = fbx_model->MaterialData[i].Color.Specular.y;
		model -> material_[ i ].Specular.b = fbx_model->MaterialData[i].Color.Specular.z;
		model -> material_[ i ].Specular.a = fbx_model->MaterialData[i].Color.Transparency;
	}
}



//================================================================================
//
// [ �o�[�e�b�N�X�o�b�t�@�쐬�֐� ]
//
//================================================================================

void CreateVertexBuffer_DirectX9( Model_DirectX9* model )
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	VERTEX3D * pVer;
	
	if ( pDevice == NULL )
	{
		MessageBox( NULL, "D3DDevice�̎擾���ł��܂���ł���", "�G���[", MB_OK );
	}

	model -> vertex_buffer_.resize( model -> mesh_.size() );
	model->texture_.resize(model->mesh_.size());
	for ( int i = 0;  i < ( int )model -> mesh_.size(); i++ )
	{
		// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
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
			sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", model->mesh_[i].tex_name_.data());
			MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		}

		if ( FAILED( hr ) )
		{
			MessageBox( NULL, "Vertex buffer was not created.", "Error", MB_OK );
		}
	}
	
}



//================================================================================
//
// [ �o�[�e�b�N�X�o�b�t�@����֐� ]
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
// [ ���f���`��֐� ]
//
//================================================================================

void DrawModel_DirectX9( Model_DirectX9* model )
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	
	if ( pDevice == NULL )
	{
		MessageBox( NULL, "D3DDevice�̎擾���ł��܂���ł���", "�G���[", MB_OK );
	}

	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DXMatrixScaling(&g_mtxWorld, 0.5, 0.5, 0.5);
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
	
	//�r���[
	g_mtxView = GetViewMtx();
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	//�v���W�F�N�V����
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProj);
	for ( int i = 0; i < ( int )model -> vertex_buffer_.size(); i++ )
	{
		pDevice -> SetStreamSource( 0, model -> vertex_buffer_[ i ], 0, sizeof( VERTEX_3D ) );
		
		// �e�N�X�`���e�[�u���ɃZ�b�g
		if ( model -> mesh_[ i ].tex_name_ == "" )
		{
			pDevice -> SetTexture( 0, NULL );
		}
		else
		{
			pDevice -> SetTexture( 0, model -> texture_[ i ] );
		}
	
		// �}�e���A�����f�o�C�X�ɃZ�b�g
		pDevice -> SetMaterial( & model -> material_[  model -> mesh_[ i ].material_index_ ] );
		pDevice -> DrawPrimitive( D3DPT_TRIANGLELIST, 0, model -> mesh_[ i ].primitive_num_ );
	}
}