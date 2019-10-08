#include "Include.h"

void VERTEXDATA::Destroy()
{
	//���_�o�b�t�@�̃����[�X
	if (this->pVetTexBuffer != NULL)
	{
		this->pVetTexBuffer->Release();
		this->pVetTexBuffer = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̃����[�X
	if (this->pIndexBuffer != NULL)
	{
		this->pIndexBuffer->Release();
		this->pIndexBuffer = NULL;
	}
	//�e�N�X�`���̃����[�X
	if (this->pTexture != NULL)
	{
		this->pTexture->Release();
		this->pTexture = NULL;
	}
};
void MFMMESHDATA::Destroy()
{
	for (int i = 0; i < (int)this->VertexBuffer.size(); i++)
	{
		if (this->VertexBuffer[i] != nullptr)
		{
			this->VertexBuffer[i]->Release();
			this->VertexBuffer[i] = nullptr;
		}
	}
	for (size_t i = 0; i < (int)this->Texture.size(); i++)
	{
		if (this->Texture[i] != nullptr)
		{		  
			this->Texture[i]->Release();
			this->Texture[i] = nullptr;
		}
	}
}
void MESHDATA::Destroy()
{
	//���b�V���̃����[�X
	if (this->pMesh != NULL)
	{
		this->pMesh->Release();
		this->pMesh = NULL;
	}
	//�e�N�X�`���������[�X
	delete this->pMeshTextures;
	//�}�e���A���������[�X
	delete this->pMeshMaterials;
};
void FRAMEDATA::Destroy()
{
	//���b�V���̃����[�X
	if (this->pMesh != NULL)
	{
		this->pMesh->Release();
		this->pMesh = NULL;
	}
	//�e�N�X�`���������[�X
	delete this->pMeshTextures;
	//�}�e���A���������[�X
	delete this->pMeshMaterials;
}
void CreateVerTex(VERTEXDATA *InOut, LPSTR TeXCFileName, std::vector<VERTEX3D> *vtx, std::vector<WORD> *index)
{
	int IndeXsize;
	int vtXsize;
	LPDIRECT3DDEVICE9			pDevice = GetD3DDevice();
	LPWORD * pIndex;
	VERTEX3D * pVer;
	
	InOut->IndeXsize =  IndeXsize = index->size();
	InOut->vtXsize = vtXsize = vtx->size();
	if (FAILED(D3DXCreateTextureFromFile(pDevice, TeXCFileName, &InOut->pTexture)))
	{
		char err[124];
		sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", TeXCFileName);
		MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
	}
	pDevice->CreateIndexBuffer(sizeof(WORD) * index->size(), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &InOut->pIndexBuffer, NULL);

	//DORAD�������ꍇ�t�H�[�}�b�g��32�ɂ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * vtx->size(), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &InOut->pVetTexBuffer, NULL);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pIndex, index->data(), sizeof(WORD) * index->size());		//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pIndexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pVer, vtx->data(), sizeof(VERTEX3D) * vtx->size());			//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pVetTexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...;

}
void CreateMesh(MESHDATA *InOut, LPSTR TeXCFileName)
{
	LPDIRECT3DDEVICE9			pDevice = GetD3DDevice();

	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	LPD3DXBUFFER pD3DXAdjacencyBuffer = NULL;
	if (FAILED(D3DXLoadMeshFromX(TeXCFileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pD3DXMtrlBuffer, NULL, &InOut->dwNumMaterials, &InOut->pMesh)))
	{
		char err[124];
		sprintf(&err[0], "X�t�@�C���̎擾�u%s�v�Ɏ��s���܂���", TeXCFileName);
		MessageBox(NULL, &err[0], "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		return;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	InOut->pMeshMaterials = new D3DMATERIAL9[InOut->dwNumMaterials];
	InOut->pMeshTextures = new LPDIRECT3DTEXTURE9[InOut->dwNumMaterials];

	for (DWORD i = 0; i<InOut->dwNumMaterials; i++)
	{

		InOut->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		InOut->pMeshMaterials[i].Ambient = InOut->pMeshMaterials[i].Diffuse;
		InOut->pMeshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			TCHAR Buff[MAX_PATH];
			EditPath(Buff, d3dxMaterials[i].pTextureFilename, TeXCFileName);
			if (FAILED(D3DXCreateTextureFromFile(pDevice, Buff, &InOut->pMeshTextures[i])))
			{
				char err[124];
				sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", Buff);
				MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	
} 
void CreateMFMMesh(MFMMESHDATA *InOut, LPSTR TeXCFileName)
{
	Model inMFMmodel;
	std::vector< vertexbuff > mesh_;

	inMFMmodel.FileLoadData(TeXCFileName);
	mesh_.resize(inMFMmodel.MeshNum.GetNum());

	// ���b�V��������
	for (int i = 0; i < (int)mesh_.size(); i++)
	{
		// �C���f�b�N�X������

		mesh_[i].Vertex.resize(inMFMmodel.MeshData[i].Index.Num.GetNum());
		InOut->matchData.resize(inMFMmodel.MeshData[i].Index.Num.GetNum());

		int temp_material_index = inMFMmodel.MeshData[i].MaterialIndex.GetNum();
		// ���b�V���C���f�b�N�X�ԍ��擾
		InOut->matchData[i].MaterialIndex = temp_material_index;


		for (int j = 0; j <(int)mesh_[i].Vertex.size(); j++)
		{
			// ���_
			int temp_index_num = inMFMmodel.MeshData[i].Index.Data[j];
			mesh_[i].Vertex[j].Pos.x = inMFMmodel.MeshData[i].Vertex.Data[temp_index_num].x;
			mesh_[i].Vertex[j].Pos.y = inMFMmodel.MeshData[i].Vertex.Data[temp_index_num].y;
			mesh_[i].Vertex[j].Pos.z = inMFMmodel.MeshData[i].Vertex.Data[temp_index_num].z;

			// �@��
			mesh_[i].Vertex[j].Normal.x = inMFMmodel.MeshData[i].Normals.Data[j].x;
			mesh_[i].Vertex[j].Normal.y = inMFMmodel.MeshData[i].Normals.Data[j].y;
			mesh_[i].Vertex[j].Normal.z = inMFMmodel.MeshData[i].Normals.Data[j].z;

			// UV
			mesh_[i].Vertex[j].texcoord.x = inMFMmodel.MeshData[i].TexUV.Data[j].U;
			mesh_[i].Vertex[j].texcoord.y = inMFMmodel.MeshData[i].TexUV.Data[j].V;

			// �J���[
			D3DXCOLOR temp_color;
			temp_color.r = inMFMmodel.MaterialData[temp_material_index].Color.Diffuse.x;
			temp_color.g = inMFMmodel.MaterialData[temp_material_index].Color.Diffuse.y;
			temp_color.b = inMFMmodel.MaterialData[temp_material_index].Color.Diffuse.z;
			temp_color.a = inMFMmodel.MaterialData[temp_material_index].Color.Transparency;

			mesh_[i].Vertex[j].color = (D3DCOLOR)temp_color;
		}

		// �e�N�X�`�����̓ǂݍ���

		if (inMFMmodel.MaterialData[temp_material_index].TexName.Get() != "")
		{
			InOut->matchData[i].TexName = inMFMmodel.MaterialData[temp_material_index].TexName.Get();
		}
		// �v���~�e�B�u���̎擾
		InOut->matchData[i].PrimitiveNum = inMFMmodel.MeshData[i].PrimitiveIndex.GetNum();
	}
	// �}�e���A�����̊m��
	InOut->Material.resize(inMFMmodel.materialNum.GetNum());

	// ���b�V��������
	for (int i = 0; i < (int)InOut->Material.size(); i++)
	{
		// �A���r�G���g
		InOut->Material[i].Ambient.r = inMFMmodel.MaterialData[i].Color.Ambient.x;
		InOut->Material[i].Ambient.g = inMFMmodel.MaterialData[i].Color.Ambient.y;
		InOut->Material[i].Ambient.b = inMFMmodel.MaterialData[i].Color.Ambient.z;
		InOut->Material[i].Ambient.a = inMFMmodel.MaterialData[i].Color.Transparency;

		// �f�B�t���[�Y								   
		InOut->Material[i].Diffuse.r = inMFMmodel.MaterialData[i].Color.Diffuse.x;
		InOut->Material[i].Diffuse.g = inMFMmodel.MaterialData[i].Color.Diffuse.y;
		InOut->Material[i].Diffuse.b = inMFMmodel.MaterialData[i].Color.Diffuse.z;
		InOut->Material[i].Diffuse.a = inMFMmodel.MaterialData[i].Color.Transparency;

		// �G�~�b�V�u
		InOut->Material[i].Emissive.r = inMFMmodel.MaterialData[i].Color.Emissive.x;
		InOut->Material[i].Emissive.g = inMFMmodel.MaterialData[i].Color.Emissive.y;
		InOut->Material[i].Emissive.b = inMFMmodel.MaterialData[i].Color.Emissive.z;
		InOut->Material[i].Emissive.a = inMFMmodel.MaterialData[i].Color.Transparency;

		// �X�y�L����
		InOut->Material[i].Power = inMFMmodel.MaterialData[i].Color.Shininess;

		// �X�y�L�����F
		InOut->Material[i].Specular.r = inMFMmodel.MaterialData[i].Color.Specular.x;
		InOut->Material[i].Specular.g = inMFMmodel.MaterialData[i].Color.Specular.y;
		InOut->Material[i].Specular.b = inMFMmodel.MaterialData[i].Color.Specular.z;
		InOut->Material[i].Specular.a = inMFMmodel.MaterialData[i].Color.Transparency;
	}
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	VERTEX3D * pVer;

	if (pDevice == NULL)
	{
		MessageBox(NULL, "D3DDevice�̎擾���ł��܂���ł���", "�G���[", MB_OK);
	}

	InOut->VertexBuffer.resize(mesh_.size());
	InOut->Texture.resize(mesh_.size());
	for (int i = 0; i < (int)mesh_.size(); i++)
	{
		// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
		HRESULT  hr = pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * mesh_[i].Vertex.size(),
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&InOut->VertexBuffer[i],
			NULL);

		InOut->VertexBuffer[i]->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);
		memcpy(pVer, mesh_[i].Vertex.data(), sizeof(VERTEX3D) * mesh_[i].Vertex.size());
		InOut->VertexBuffer[i]->Unlock();

		TCHAR Buff[MAX_PATH];
		EditPath(Buff, (TCHAR*)InOut->matchData[i].TexName.data(), TeXCFileName);
		if (FAILED(D3DXCreateTextureFromFile(pDevice, Buff, &InOut->Texture[i])))
		{
			char err[124];
			sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", InOut->matchData[i].TexName.data());
			MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
		}

		if (FAILED(hr))
		{
			MessageBox(NULL, "Vertex buffer was not created.", "Error", MB_OK);
		}
	}

}
void CreateMeshField(VERTEXDATA *InOut, LPSTR TeXCFileName, int w, int h)
{
	LPDIRECT3DDEVICE9			pDevice = GetD3DDevice();
	std::vector<VERTEX3D>		vtx;
	std::vector<WORD>			index;
	LPWORD * pIndex;
	VERTEX3D * pVer;

	int X = 0, Y = 0;
	float Xof = h * 0.5f, Yof = w * 0.5f;
	h++;
	w++;
	for (X = 0; X < h; X++)
	{
		for (Y = 0; Y < w; Y++)
		{
			vtx.push_back({ D3DXVECTOR3((float)X - Xof,(float) 0, (float)Y - Yof),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2( (float)X ,(float)Y) });//0
			index.push_back((unsigned short)((w + Y) + (X * w)));
			if (X < h - 1)
			{
				index.push_back((unsigned short)(Y + (X * w)));
			}
		}
		if (X < h - 1)
		{
			index.push_back((unsigned short)((Y - 1) + (X * w)));
			index.push_back((unsigned short)((X + 2) * w));
		}

	}

	InOut->IndeXsize = index.size();
	InOut->vtXsize = vtx.size();
	if (FAILED(D3DXCreateTextureFromFile(pDevice, TeXCFileName, &InOut->pTexture)))
	{
		char err[124];
		sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", TeXCFileName);
		MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
	}
	pDevice->CreateIndexBuffer(sizeof(WORD) * index.size(), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &InOut->pIndexBuffer, NULL);

	//DORAD�������ꍇ�t�H�[�}�b�g��32�ɂ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * vtx.size(), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &InOut->pVetTexBuffer, NULL);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pIndex, index.data(), sizeof(WORD) * index.size());		//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pIndexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pVetTexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...;

																		// �}�e���A�����̊m��

}
void CreateMeshBoard(VERTEXDATA *InOut, LPSTR TeXCFileName)
{
	std::vector<VERTEX3D> vtx;
	std::vector<WORD> index;


	int nCantate = 0;
	int nCanyoko = 0;
	int nCan = 0;
	vtx.push_back({ D3DXVECTOR3(-0.5, -0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//0
	vtx.push_back({ D3DXVECTOR3(0.5, -0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//1
	vtx.push_back({ D3DXVECTOR3(-0.5,  0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//2
	vtx.push_back({ D3DXVECTOR3(0.5,  0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//3

	index.push_back(0);
	index.push_back(2);
	index.push_back(1);
	index.push_back(3);


	//index.push_back(1);
	//index.push_back(3);
	//index.push_back(3);



	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	LPWORD * pIndex;
	VERTEX3D * pVer;
	InOut->IndeXsize = index.size();
	InOut->vtXsize = vtx.size();
	if (FAILED(D3DXCreateTextureFromFile(pDevice, TeXCFileName, &InOut->pTexture)))
	{
		char err[124];
		sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", TeXCFileName);
		MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
	}
	pDevice->CreateIndexBuffer(sizeof(WORD) * index.size(), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &InOut->pIndexBuffer, NULL);

	//DORAD�������ꍇ�t�H�[�}�b�g��32�ɂ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * vtx.size(), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &InOut->pVetTexBuffer, NULL);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pIndex, index.data(), sizeof(WORD) * index.size());		//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pIndexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pVetTexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...;
}
void CreateMeshAnimationBoard(VERTEXDATA *InOut, LPSTR TeXCFileName)
{
	std::vector<VERTEX3D> vtx;
	std::vector<WORD> index;
	D3DXIMAGE_INFO dil;

	D3DXGetImageInfoFromFile(TeXCFileName, &dil);					//�e�N�X�`���̏��擾
	InOut->TexSizeX = (int)dil.Width;		//�e�N�X�`����XY��n��
	InOut->TexSizeY = (int)dil.Height;


	int nCantate = 0;
	int nCanyoko = 0;
	int nCan = 0;
	vtx.push_back({ D3DXVECTOR3(-0.5, -0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//0
	vtx.push_back({ D3DXVECTOR3(0.5, -0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//1
	vtx.push_back({ D3DXVECTOR3(-0.5,  0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//2
	vtx.push_back({ D3DXVECTOR3(0.5,  0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//3

	index.push_back(1);
	index.push_back(0);
	index.push_back(3);
	index.push_back(2);

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	LPWORD * pIndex;
	VERTEX3D * pVer;
	InOut->IndeXsize = index.size();
	InOut->vtXsize = vtx.size();
	if (FAILED(D3DXCreateTextureFromFile(pDevice, TeXCFileName, &InOut->pTexture)))
	{
		char err[124];
		sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", TeXCFileName);
		MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
	}
	pDevice->CreateIndexBuffer(sizeof(WORD) * index.size(), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &InOut->pIndexBuffer, NULL);

	//DORAD�������ꍇ�t�H�[�}�b�g��32�ɂ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX3D) * vtx.size(), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &InOut->pVetTexBuffer, NULL);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pIndex, index.data(), sizeof(WORD) * index.size());		//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pIndexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//�������炱���܂ŉ��̃��[��( �L�́M)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//���̗̒n�ɏ�𗧂Ă�(�M�E�ցE�L)�����
	InOut->pVetTexBuffer->Unlock();										//����ϖ����y�n�����(�L�E��:;.:...;
}
void CreateFramDataMesh(FRAMEDATA *InOut, LPSTR TeXCFileName)
{
	LPDIRECT3DDEVICE9			pDevice = GetD3DDevice(); 
	HIERARCHYDERIVED*			Hierarchy = GetHierearchy();
	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����						
	if (FAILED(	D3DXLoadMeshHierarchyFromX(TeXCFileName, D3DXMESH_MANAGED, pDevice, Hierarchy, NULL, &InOut->pFrameRoot, &InOut->pAnimController)))
	{
		char err[124];
		sprintf(&err[0], "�e�N�X�`���̎擾�u%s�v�Ɏ��s���܂���", TeXCFileName);
		MessageBox(NULL, &err[0], "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", MB_OK);
	}

	AllocateAllBoneMatrices(InOut, InOut->pFrameRoot);

}
int EditPath(TCHAR *OutPath, TCHAR *InPath, TCHAR *AddPath)
{
	TCHAR Buff[MAX_PATH];
	ZeroMemory(Buff, sizeof(Buff[MAX_PATH]));
	ZeroMemory(OutPath, sizeof(Buff[MAX_PATH]));
	int LastPoint = 0;
	LastPoint = CutPath(Buff, AddPath);
	int inPathsize = strlen(InPath);

	for (size_t i = 0; i < (size_t)inPathsize; i++)
	{
		Buff[LastPoint + i] = InPath[i];
	}

	Buff[LastPoint + inPathsize] = '\0';
	strcpy(OutPath, Buff);
	return LastPoint + inPathsize + 1;
}
int CutPath(TCHAR *Out, TCHAR *In)
{
	int inStrsize;
	int CutPoint = 0;
	TCHAR Buff[MAX_PATH];
	ZeroMemory(Buff, sizeof(Buff[MAX_PATH]));
	inStrsize = strlen(In);

	for (int i = inStrsize;  i > 0;  i--)
	{
		if(In[i] == '\\')
		{
			CutPoint = i + 1;
			i = 0;
		}
	}

	for (size_t i = 0; i < (size_t)CutPoint; i++)
	{
		Out[i] = In[i];
	}
	return CutPoint;
}