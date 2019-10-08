#include "Render.h"


void BaseData::init()
{
	D3DXMatrixIdentity(&this->g_mtxWorld);					//ワールド行列を初期化
	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);					//カメラ座標
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);					//注視点
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);					//カメラの向き
	D3DXMatrixLookAtLH(&this->g_mtxView, &eye, &at, &up);     //ビュー行列の初期化
	D3DXMatrixPerspectiveFovLH(&this->g_mtxProj,				//プロジェクション行列の初期化
		D3DXToRadian((120) / 2),
		(float)SCREEN_WIDTH / SCREEN_HIEGTH,
		0.1f,
		2000);
}
void BaseData::SetLight(D3DLIGHT9 in)		//Lightをセット
{
	this->Light = in;
}
void BaseData::SetMtXWorld(D3DXMATRIX World)		//ワールド行列をセット
{
	this->g_mtxWorld = World;
}
void BaseData::SetMtXView(D3DXMATRIX View)		//ビュー行列をセット
{
	this->g_mtxView = View;
}
void BaseData::SetMtXWProj(D3DXMATRIX Proj)		//プロジェクション行列をセット
{
	this->g_mtxProj = Proj;
}
	
//ここから頂点
//データをセット
void RenderVtx::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
//描画
void RenderVtx::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//インデックスセット&頂点セット
	Device->SetIndices( this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆


	//ライティングオフ
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//ワールド
	
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
}
//ワールド行列をセット
//ここまで頂点
//ここからメッシュ
//データをセット
void RenderMesh::SetRendData(MESHDATA *InData)
{
	MeshData = InData;
	this->init();
}
//描画
void RenderMesh::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();
	//ワールド
	Device->SetTransform(D3DTS_WORLD, &g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &g_mtxView);
	//プロジェクション
	Device->SetTransform(D3DTS_PROJECTION, &g_mtxProj);

	for (DWORD i = 0; i < this->MeshData->dwNumMaterials; i++)
	{
		Device->SetMaterial(&this->MeshData->pMeshMaterials[i]);
		Device->SetTexture(0, this->MeshData->pMeshTextures[i]);
		this->MeshData->pMesh->DrawSubset(i);
	}
}
//ここまでメッシュ
//ここからフレームメッシュ
//データをセット
void RenderFrameMesh::SetRendData(FRAMEDATA *InData)
{
	this->FrameMeshData = InData;
	this->init();
}
//描画
void RenderFrameMesh::Draw()
{
	static FLOAT fAnimTime,fAnimTimeHold = fAnimTime;
	this->Updata(this->FrameMeshData->pFrameRoot, &this->g_mtxWorld);
	this->Convert(this->FrameMeshData->pFrameRoot);
	this->FrameMeshData->pAnimController->AdvanceTime(fAnimTime - fAnimTimeHold, NULL);
	fAnimTimeHold = fAnimTime;
	fAnimTime += 0.0001f;
}
//更新
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
//描画
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
	//スキンメッシュの場合
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
	//通常メッシュの場合
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
//ここまでフレームメッシュ
//ここから頂点ストリップ
//データをセット
void RenderVtxStrip::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
//描画
void RenderVtxStrip::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//インデックスセット&頂点セット
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆

	//ライティングオフ
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//Device->SetRenderState(D3DRS_FILLMODE, 2);
	//ワールド
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);
	//Device->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize-2);
}
//ここまで頂点ストリップ
//ここからビルボード
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

	//インデックスセット&頂点セット
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆
	D3DXMATRIX mtxViewInv = this->g_mtxView;
	D3DXMatrixTranspose(&mtxViewInv, &mtxViewInv);
	mtxViewInv._14 = 0;
	mtxViewInv._24 = 0;
	mtxViewInv._34 = 0;

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * mtxViewInv * this->g_mtxPos;

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 128);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	//ライティングオフ
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//Device->SetRenderState(D3DRS_FILLMODE, 2);
	//ワールド
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
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
	D3DXMatrixScaling(&mtxScale, x, y, z);//スケーリング（拡大縮小）行列を作成
	this->g_mtxScale = mtxScale;
}
void RenderBillBoard::SetMtXPos(float x, float y, float z)
{
	D3DXMATRIX mtxWorldPos;
	D3DXMatrixTranslation(&mtxWorldPos, x, y, z);//平行移動行列を作成
	this->g_mtxPos = mtxWorldPos;
}
void RenderBillBoard::SetMtXRotation(float x, float y, float z)
{
	D3DXMATRIX mtxWorldRotion;
	D3DXMatrixRotationYawPitchRoll(&mtxWorldRotion, x, y, z);//回転行列を作成
	this->g_mtxRotation = mtxWorldRotion;
}
//ここまでビルボード
//ここからビルボードアニメーション
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
	int patternNUM = this->AniCount % (this->AniCountX * this->AniCountY);	//アニメーションのパターン数
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

	//インデックスセット&頂点セット
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));

	//こいつらを使いたくなければNULLをSETだぜ☆
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

	//ライティングオフ
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//Device->SetRenderState(D3DRS_FILLMODE, 2);
	//ワールド
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
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
void RenderBillAnimation::SetAnimationSpeed(float Speed)			//アニメーションスピード
{
	this->AniSpeed = Speed;
}
void RenderBillAnimation::SetMtXScale(float x, float y, float z)
{
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, x, y, z);//スケーリング（拡大縮小）行列を作成
	this->g_mtxScale = mtxScale;
}
void RenderBillAnimation::SetMtXPos(float x, float y, float z)
{
	D3DXMATRIX mtxWorldPos;
	D3DXMatrixTranslation(&mtxWorldPos, x, y, z);//平行移動行列を作成
	this->g_mtxPos = mtxWorldPos;
}
void RenderBillAnimation::SetMtXRotation(float x, float y, float z)
{
	D3DXMATRIX mtxWorldRotion;
	D3DXMatrixRotationYawPitchRoll(&mtxWorldRotion, x, y, z);//回転行列を作成
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
//ここまでビルボードアニメーション
//ここからUI
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

	//インデックスセット&頂点セット
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	
	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	ColorStocker = pVt[0].color;
	pVt[0].color = pVt[1].color = pVt[2].color = pVt[3].color = this->d3dColor;

	this->VerTexData->pVetTexBuffer->Unlock();

	//頂点データ
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * this->g_mtxPos;

	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	
	//ライティングオフ
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//ワールド
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
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
	// セットした位置情報と現在の位置情報の差分をスピードで掛け算(1.0f = 100%)
	this->TranslationPos += (this->TranslationSet - this->TranslationPos) * MoveSpeed;
	this->ScalingPos += (this->ScalingSet - this->ScalingPos) * MoveSpeed;
	// 計算した情報をセット
	this->SetMtXPos(this->TranslationPos);
	this->SetMtXScale(this->ScalingPos);
}
void RenderUI::SetMtXScale(D3DXVECTOR3 scale)
{
	this->ScalingPos = scale;
	this->ScalingSet = scale;
	D3DXMatrixScaling(&this->g_mtxScale, scale.x, scale.y, scale.z);//スケーリング（拡大縮小）行列を作成
}
void RenderUI::SetMtXPos(D3DXVECTOR3 pos)
{
	this->TranslationPos = pos;
	this->TranslationSet = pos;
	D3DXMatrixTranslation(&this->g_mtxPos, pos.x, pos.y, pos.z);//平行移動行列を作成
}
void RenderUI::SetMtXRotation(D3DXVECTOR3 rot)
{
	D3DXMatrixRotationYawPitchRoll(&this->g_mtxRotation, rot.x, rot.y, rot.z);//回転行列を作成
}
void RenderUI::SetColor(D3DCOLOR InColor)//カラーコードをセット
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
//ここまでUI
//ここから減算合成された頂点
//データをセット
void RenderSubsyn::SetRendData(VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
//描画
void RenderSubsyn::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetD3DDevice();

	Device->SetFVF(FVF_VERTEX_3D);

	//インデックスセット&頂点セット
	Device->SetIndices(this->VerTexData->pIndexBuffer);
	Device->SetStreamSource(0, this->VerTexData->pVetTexBuffer, 0, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆
	//ここからαテスト
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF,125);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//ここから減算合成
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	//ライティングオフ
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//ワールド
	Device->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	//ビュー
	Device->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
	Device->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);

	Device->SetTexture(0, this->VerTexData->pTexture);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);

	//ここまで減算合成
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//ここまでαテスト
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
void Rendermfm::SetRendData(MFMMESHDATA *inData)	//データをセット＆初期化
{
	this->pmfmData = inData;
	this->init();
}
void Rendermfm::Draw()							//描画
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		MessageBox(NULL, "D3DDeviceの取得ができませんでした", "エラー", MB_OK);
	}

	pDevice->SetFVF(FVF_VERTEX_3D);
	
	pDevice->SetTransform(D3DTS_WORLD, &this->g_mtxWorld);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//ビュー
	g_mtxView = this->g_mtxView;
	pDevice->SetTransform(D3DTS_VIEW, &this->g_mtxView);
	//プロジェクション
	pDevice->SetTransform(D3DTS_PROJECTION, &this->g_mtxProj);
	for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
	{
		pDevice->SetStreamSource(0, this->pmfmData->VertexBuffer[i], 0, sizeof(VERTEX3D));

		// テクスチャテーブルにセット
		if (this->pmfmData->matchData[i].TexName == "")
		{
		
		}
		else
		{
			pDevice->SetTexture(0, this->pmfmData->Texture[i]);
		}

		// マテリアルをデバイスにセット
		pDevice->SetMaterial(&this->pmfmData->Material[this->pmfmData->matchData[i].MaterialIndex]);


		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, this->pmfmData->matchData[i].PrimitiveNum);
	}
}


//ここまで頂点

