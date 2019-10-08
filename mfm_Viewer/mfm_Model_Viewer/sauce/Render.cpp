#include "Render.h"


void BaseData::init()
{
	D3DXMatrixIdentity(&this->g_mtxWorld);					//���[���h�s���������
	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);					//�J�������W
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);					//�����_
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);					//�J�����̌���
	D3DXMatrixLookAtLH(&this->g_mtxView, &eye, &at, &up);     //�r���[�s��̏�����
	D3DXMatrixPerspectiveFovLH(&this->g_mtxProj,				//�v���W�F�N�V�����s��̏�����
		D3DXToRadian((120) / 2),
		(float)SCREEN_WIDTH / SCREEN_HIEGTH,
		0.1f,
		2000);
}
void BaseData::SetLight(D3DLIGHT9 in)		//Light���Z�b�g
{
	this->Light = in;
}
void BaseData::SetMtXWorld(D3DXMATRIX World)		//���[���h�s����Z�b�g
{
	this->g_mtxWorld = World;
}
void BaseData::SetMtXView(D3DXMATRIX View)		//�r���[�s����Z�b�g
{
	this->g_mtxView = View;
}
void BaseData::SetMtXWProj(D3DXMATRIX Proj)		//�v���W�F�N�V�����s����Z�b�g
{
	this->g_mtxProj = Proj;
}
	
//�������璸�_
//�f�[�^���Z�b�g
void RenderVtx::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
//�`��
void RenderVtx::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//�C���f�b�N�X�Z�b�g&���_�Z�b�g
	Device->SetIndices( this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//��������g�������Ȃ����NULL��SET������


	//���C�e�B���O�I�t
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//���[���h
	
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
}
//���[���h�s����Z�b�g
//�����܂Œ��_
//�������烁�b�V��
//�f�[�^���Z�b�g
void RenderMesh::SetRendData(MESHDATA *InData)
{
	MeshData = InData;
	this->init();
}
//�`��
void RenderMesh::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();
	//���[���h
	Device->SetTransform(D3DTS_WORLD, &g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &g_mtxProj);

	for (DWORD i = 0; i < this->MeshData->dwNumMaterials; i++)
	{
		Device->SetMaterial(&this->MeshData->pMeshMaterials[i]);
		Device->SetTexture(0, this->MeshData->pMeshTextures[i]);
		this->MeshData->pMesh->DrawSubset(i);
	}
}
//�����܂Ń��b�V��
//��������t���[�����b�V��
//�f�[�^���Z�b�g
void RenderFrameMesh::SetRendData(FRAMEDATA *InData)
{
	this->FrameMeshData = InData;
	this->init();
}
//�`��
void RenderFrameMesh::Draw()
{
	static FLOAT fAnimTime,fAnimTimeHold = fAnimTime;
	this->Updata(this->FrameMeshData->pFrameRoot, &this->g_mtxWorld);
	this->Convert(this->FrameMeshData->pFrameRoot);
	this->FrameMeshData->pAnimController->AdvanceTime(fAnimTime - fAnimTimeHold, NULL);
	fAnimTimeHold = fAnimTime;
	fAnimTime += 0.0001f;
}
//�X�V
void RenderFrameMesh::Updata(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	LPDIRECT3DDEVICE9 Device = NULL;
		Device = GetD3DDevice();
	FRAMEDERIVED *pFrame = (FRAMEDERIVED*)pFrameBase;

	if (this->g_mtxWorld != NULL)
	{
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		this->Updata(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		this->Updata(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}
//�`��
void RenderFrameMesh::Convert(LPD3DXFRAME pFrameBase)
{
	FRAMEDERIVED *pFrame = (FRAMEDERIVED*)pFrameBase;
	MESHCONTAINERDERIVED* pMeshContainer = (MESHCONTAINERDERIVED*)pFrame->pMeshContainer;

	while (pMeshContainer != NULL)
	{
		this->Render(pMeshContainer, pFrame);

		pMeshContainer = (MESHCONTAINERDERIVED*)pMeshContainer->pNextMeshContainer;
	}
	if (pFrame->pFrameSibling != NULL)
	{	
		this->Convert(pFrame->pFrameSibling);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		this->Convert(pFrame->pFrameFirstChild);
	}
}
void RenderFrameMesh::Render(MESHCONTAINERDERIVED* pMeshContainer, FRAMEDERIVED* pFrame)
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();
	DWORD i, k;
	DWORD  dwBlendMatrixAmt;
	DWORD dwPrevBoneID;
	LPD3DXBONECOMBINATION pBoneCombination;
	UINT iMatrixIndex;
	D3DXMATRIX matStack;
	//�X�L�����b�V���̏ꍇ
	if (pMeshContainer->pSkinInfo != NULL)
	{
		pBoneCombination = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneBuffer->GetBufferPointer();

		dwPrevBoneID = UINT_MAX;
		for (i = 0; i < pMeshContainer->dwBoneAmt; i++)
		{
			dwBlendMatrixAmt = 0;
			for (k = 0; k< pMeshContainer->dwWeight; k++)
			{
				if (pBoneCombination[i].BoneId[k] != UINT_MAX)
				{
					dwBlendMatrixAmt = k;
				}
			}
			Device->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixAmt);
			for (k = 0; k < pMeshContainer->dwWeight; k++)
			{
				iMatrixIndex = pBoneCombination[i].BoneId[k];
				if (iMatrixIndex != UINT_MAX)
				{
					matStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
					Device->SetTransform(D3DTS_WORLDMATRIX(k), &matStack);
				}
			}
			Device->SetMaterial(&pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D);
			Device->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
			dwPrevBoneID = pBoneCombination[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
	//�ʏ탁�b�V���̏ꍇ
	else
	{
		Device->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
		for (i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			Device->SetMaterial(&pMeshContainer->pMaterials[i].MatD3D);
			Device->SetTexture(0, pMeshContainer->ppTextures[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
//�����܂Ńt���[�����b�V��
//�������璸�_�X�g���b�v
//�f�[�^���Z�b�g
void RenderVtxStrip::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
//�`��
void RenderVtxStrip::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//�C���f�b�N�X�Z�b�g&���_�Z�b�g
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//��������g�������Ȃ����NULL��SET������

	//���C�e�B���O�I�t
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//Device->SetRenderState(D3DRS_FILLMODE, 2);
	//���[���h
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);
	//Device->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize-2);
}
//�����܂Œ��_�X�g���b�v
//��������r���{�[�h
void RenderBillBoard::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->SetMtXPos(0,0,0);
	this->SetMtXRotation(0, 0, 0);
	this->SetMtXScale(1, 1, 1);
}
void RenderBillBoard::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//�C���f�b�N�X�Z�b�g&���_�Z�b�g
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//��������g�������Ȃ����NULL��SET������
	D3DXMATRIX mtxViewInv = this->g_mtxView;
	D3DXMatrixTranspose(&mtxViewInv, &mtxViewInv);
	mtxViewInv._14 = 0;
	mtxViewInv._24 = 0;
	mtxViewInv._34 = 0;

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * mtxViewInv * this->g_mtxPos;

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 128);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	//���C�e�B���O�I�t
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//Device->SetRenderState(D3DRS_FILLMODE, 2);
	//���[���h
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);
	//Device->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize - 2);

	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
void RenderBillBoard::SetMtXScale(float x, float y, float z)
{
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, x, y, z);//�X�P�[�����O�i�g��k���j�s����쐬
	this->g_mtxScale = mtxScale;
}
void RenderBillBoard::SetMtXPos(float x, float y, float z)
{
	D3DXMATRIX mtxWorldPos;
	D3DXMatrixTranslation(&mtxWorldPos, x, y, z);//���s�ړ��s����쐬
	this->g_mtxPos = mtxWorldPos;
}
void RenderBillBoard::SetMtXRotation(float x, float y, float z)
{
	D3DXMATRIX mtxWorldRotion;
	D3DXMatrixRotationYawPitchRoll(&mtxWorldRotion, x, y, z);//��]�s����쐬
	this->g_mtxRotation = mtxWorldRotion;
}
//�����܂Ńr���{�[�h
//��������r���{�[�h�A�j���[�V����
void RenderBillAnimation::SetRendData(VERTEXDATA *VtxData, int aniIndex, int X, int Y)
{
	VerTexData = VtxData;
	this->init();
	this->AniIndex = aniIndex;
	this->AniCountX = X;
	this->AniCountY = Y;
	this->AniCount = 0;
	this->AniSpeed = 1;
	this->SetMtXPos(0, 0, 0);
	this->SetMtXRotation(0, 0, 0);
	this->SetMtXScale(1, 1, 1);
}
void RenderBillAnimation::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();
	VERTEX3D *pVt;
	Device->SetFVF(FVF_VERTEX_3D);

	this->AniCount;
	this->AniIndex;
	this->AniSpeed;
	this->AniCountX;
	this->AniCountY;
	this->VerTexData->TexSizeX;
	this->VerTexData->TexSizeY;
	int patternNUM = this->AniCount % (this->AniCountX * this->AniCountY);	//�A�j���[�V�����̃p�^�[����
	int patternH = (patternNUM % this->AniCountX);			//
	int patternV = (patternNUM / this->AniCountX);			//
	int nTexWid = (this->VerTexData->TexSizeX / this->AniCountX);	//
	int nTexHei = (this->VerTexData->TexSizeY / this->AniCountY);	//
	int tcx = patternH * nTexWid;		//
	int tcy = patternV * nTexHei;		//

	float AniTexu0 = (float)tcx / this->VerTexData->TexSizeX;
	float AniTexv0 = (float)tcy / this->VerTexData->TexSizeY;
	float AniTexu1 = ((float)tcx + (float)nTexWid) / this->VerTexData->TexSizeX;
	float AniTexv1 = ((float)tcy + (float)nTexHei) / this->VerTexData->TexSizeY;


	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	pVt[0].texcoord = { D3DXVECTOR2(AniTexu1, AniTexv1) };
	pVt[1].texcoord = { D3DXVECTOR2(AniTexu0, AniTexv1) };
	pVt[2].texcoord = { D3DXVECTOR2(AniTexu1, AniTexv0) };
	pVt[3].texcoord = { D3DXVECTOR2(AniTexu0, AniTexv0) };

	this->VerTexData->pVetTexBuffer->Unlock();

	//�C���f�b�N�X�Z�b�g&���_�Z�b�g
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));

	//��������g�������Ȃ����NULL��SET������
	D3DXMATRIX mtxViewInv = this->g_mtxView;
	D3DXMatrixTranspose(&mtxViewInv, &mtxViewInv);
	mtxViewInv._14 = 0;
	mtxViewInv._24 = 0;
	mtxViewInv._34 = 0;

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * mtxViewInv * this->g_mtxPos;

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 128);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//���C�e�B���O�I�t
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//Device->SetRenderState(D3DRS_FILLMODE, 2);
	//���[���h
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
	//Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);

	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	this->AniCount += (int)this->AniSpeed;
}
void RenderBillAnimation::SetAnimationSpeed(float Speed)			//�A�j���[�V�����X�s�[�h
{
	this->AniSpeed = Speed;
}
void RenderBillAnimation::SetMtXScale(float x, float y, float z)
{
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, x, y, z);//�X�P�[�����O�i�g��k���j�s����쐬
	this->g_mtxScale = mtxScale;
}
void RenderBillAnimation::SetMtXPos(float x, float y, float z)
{
	D3DXMATRIX mtxWorldPos;
	D3DXMatrixTranslation(&mtxWorldPos, x, y, z);//���s�ړ��s����쐬
	this->g_mtxPos = mtxWorldPos;
}
void RenderBillAnimation::SetMtXRotation(float x, float y, float z)
{
	D3DXMATRIX mtxWorldRotion;
	D3DXMatrixRotationYawPitchRoll(&mtxWorldRotion, x, y, z);//��]�s����쐬
	this->g_mtxRotation = mtxWorldRotion;
}
void RenderBillAnimation::SetMtXView(D3DXMATRIX View)
{
	this->g_mtxView = View;
}
void RenderBillAnimation::SetMtXWProj(D3DXMATRIX Proj)
{
	this->g_mtxProj = Proj;
}
//�����܂Ńr���{�[�h�A�j���[�V����
//��������UI
void RenderUI::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();


	this->TranslationPos = D3DXVECTOR3(0, 0, 0);
	this->TranslationSet = D3DXVECTOR3(0, 0, 0);
	this->ScalingPos = D3DXVECTOR3(1, 1, 1);
	this->ScalingSet = D3DXVECTOR3(1, 1, 1);

	this->SetMtXPos(this->TranslationPos);
	this->SetMtXScale(this->ScalingPos);
	this->SetMtXRotation(D3DXVECTOR3(0, 0, 0));
	this->d3dColor = D3DCOLOR_ARGB(255,255,255,255);
}
void RenderUI::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();
	VERTEX3D *pVt;
	D3DCOLOR ColorStocker;

	Device->SetFVF(FVF_VERTEX_3D);

	//�C���f�b�N�X�Z�b�g&���_�Z�b�g
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	
	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	ColorStocker = pVt[0].color;
	pVt[0].color = pVt[1].color = pVt[2].color = pVt[3].color = this->d3dColor;

	this->VerTexData->pVetTexBuffer->Unlock();

	//���_�f�[�^
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//��������g�������Ȃ����NULL��SET������

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * this->g_mtxPos;

	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	
	//���C�e�B���O�I�t
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//���[���h
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);
	
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize - 2);

	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	pVt[0].color = pVt[1].color = pVt[2].color = pVt[3].color = ColorStocker;

	this->VerTexData->pVetTexBuffer->Unlock();

	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	this->d3dColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}
void RenderUI::SetMoveScale(D3DXVECTOR3 scale)
{
	this->ScalingSet = scale;
}
void RenderUI::SetMovePos(D3DXVECTOR3 pos)
{
	this->TranslationSet = pos;
}
void RenderUI::Move(float MoveSpeed)
{
	// �Z�b�g�����ʒu���ƌ��݂̈ʒu���̍������X�s�[�h�Ŋ|���Z(1.0f = 100%)
	this->TranslationPos += (this->TranslationSet - this->TranslationPos) * MoveSpeed;
	this->ScalingPos += (this->ScalingSet - this->ScalingPos) * MoveSpeed;
	// �v�Z���������Z�b�g
	this->SetMtXPos(this->TranslationPos);
	this->SetMtXScale(this->ScalingPos);
}
void RenderUI::SetMtXScale(D3DXVECTOR3 scale)
{
	this->ScalingPos = scale;
	this->ScalingSet = scale;
	D3DXMatrixScaling(&this->g_mtxScale, scale.x, scale.y, scale.z);//�X�P�[�����O�i�g��k���j�s����쐬
}
void RenderUI::SetMtXPos(D3DXVECTOR3 pos)
{
	this->TranslationPos = pos;
	this->TranslationSet = pos;
	D3DXMatrixTranslation(&this->g_mtxPos, pos.x, pos.y, pos.z);//���s�ړ��s����쐬
}
void RenderUI::SetMtXRotation(D3DXVECTOR3 rot)
{
	D3DXMatrixRotationYawPitchRoll(&this->g_mtxRotation, rot.x, rot.y, rot.z);//��]�s����쐬
}
void RenderUI::SetColor(D3DCOLOR InColor)//�J���[�R�[�h���Z�b�g
{
	this->d3dColor = InColor;
}
void RenderUI::SetMtXView(D3DXMATRIX View)
{
	this->g_mtxView = View;
}
void RenderUI::SetMtXWProj(D3DXMATRIX Proj)
{
	this->g_mtxProj = Proj;
}
//�����܂�UI
//�������猸�Z�������ꂽ���_
//�f�[�^���Z�b�g
void RenderSubsyn::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
//�`��
void RenderSubsyn::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//�C���f�b�N�X�Z�b�g&���_�Z�b�g
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//��������g�������Ȃ����NULL��SET������
	//�������烿�e�X�g
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF,125);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//�������猸�Z����
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	//���C�e�B���O�I�t
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//���[���h
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//�r���[
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);

	//�����܂Ō��Z����
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�����܂Ń��e�X�g
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
void Rendermfm::SetRendData(MFMMESHDATA *inData)	//�f�[�^���Z�b�g��������
{
	this->pmfmData = inData;
	this->init();
}
void Rendermfm::Draw()							//�`��
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		MessageBox(NULL, "D3DDevice�̎擾���ł��܂���ł���", "�G���[", MB_OK);
	}

	pDevice->SetFVF(FVF_VERTEX_3D);
	
	pDevice->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�r���[
	g_mtxView = this->g_mtxView;
	pDevice->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//�v���W�F�N�V����
	pDevice->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);
	for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
	{
		pDevice->SetStreamSource(0, this->pmfmData->VertexBuffer[i], 0, sizeof(VERTEX3D));

		// �e�N�X�`���e�[�u���ɃZ�b�g
		if (this->pmfmData->matchData[i].TexName == "")
		{
		
		}
		else
		{
			pDevice->SetTexture(0, this->pmfmData->Texture[i]);
		}

		// �}�e���A�����f�o�C�X�ɃZ�b�g
		pDevice->SetMaterial(&this->pmfmData->Material[this->pmfmData->matchData[i].MaterialIndex]);


		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, this->pmfmData->matchData[i].PrimitiveNum);
	}
}


//�����܂Œ��_

