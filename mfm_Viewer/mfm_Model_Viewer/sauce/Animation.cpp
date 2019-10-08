#include "Include.h"

//フレームの作成
HRESULT HIERARCHYDERIVED::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
{
	FRAMEDERIVED *pFrame;
	*ppNewFrame = NULL;

	pFrame = new FRAMEDERIVED;
	if (pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	pFrame->Name = new TCHAR[lstrlen(Name) + 1];
	if (!pFrame->Name)
	{
		return E_FAIL;
	}
	strcpy(pFrame->Name, Name);

	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	pFrame->pMeshContainer = NULL;
	pFrame->pFrameSibling = NULL;
	pFrame->pFrameFirstChild = NULL;
	*ppNewFrame = pFrame;
	pFrame = NULL;
	delete pFrame;

	return S_OK;
}
//メッシュコンテナーを作成する
HRESULT HIERARCHYDERIVED::CreateMeshContainer(
	LPCSTR Name, 
	CONST D3DXMESHDATA* pMeshData,
	CONST D3DXMATERIAL* pMaterials, 
	CONST D3DXEFFECTINSTANCE* pEffectInstances,
	DWORD NumMaterials, 
	CONST DWORD *pAdjacency, 
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppMeshContainer)
{
	pEffectInstances = pEffectInstances;
	HRESULT hr;
	MESHCONTAINERDERIVED *pMeshContainer = NULL;
	INT iFacesAmount;
	DWORD iMaterial;
	LPDIRECT3DDEVICE9 pDevice = NULL;
	LPD3DXMESH pMesh = NULL;
	*ppMeshContainer = NULL;
	DWORD dwBoneAmt = 0;

	pMesh = pMeshData->pMesh;
	pMeshContainer = new MESHCONTAINERDERIVED;
	if (pMeshContainer == NULL)
	{
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pMeshContainer, sizeof(MESHCONTAINERDERIVED));

	pMeshContainer->Name = new TCHAR[lstrlen(Name) + 1];
	if (!pMeshContainer->Name)
	{
		return E_FAIL;
	}
	strcpy(pMeshContainer->Name, Name);
	pMesh->GetDevice(&pDevice);
	iFacesAmount = pMesh->GetNumFaces();

	// 当該メッシュが法線を持たない場合は法線を追加する
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		hr = pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			pDevice, &pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
		{
			return E_FAIL;
		}

		pMesh = pMeshContainer->MeshData.pMesh;
		D3DXComputeNormals(pMesh, NULL);
	}
	else
	{
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		pMesh->AddRef();
	}
	//メッシュのマテリアル設定
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount * 3];
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		return E_FAIL;
	}
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount * 3);
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	if (NumMaterials > 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				TCHAR strTexturePath[MAX_PATH];
				strcpy(strTexturePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				if (FAILED(D3DXCreateTextureFromFile(pDevice, strTexturePath,
					&pMeshContainer->ppTextures[iMaterial])))
					pMeshContainer->ppTextures[iMaterial] = NULL;
				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else
	{
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}
	//当該メッシュがスキン情報を持っている場合（スキンメッシュ固有の処理）
	if (pSkinInfo != NULL)
	{
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();
		dwBoneAmt = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneAmt];

		for (DWORD i = 0; i < dwBoneAmt; i++)
		{
			memcpy(&pMeshContainer->pBoneOffsetMatrices[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX));
		}
		if (FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
			pMesh,
			NULL, pMeshContainer->pAdjacency, NULL, NULL, NULL,
			&pMeshContainer->dwWeight,
			&pMeshContainer->dwBoneAmt,
			&pMeshContainer->pBoneBuffer,
			&pMeshContainer->MeshData.pMesh)
		))
		{
			return E_FAIL;
		}
	}
	//ローカルに生成したメッシュコンテナーを呼び出し側にコピーする
	*ppMeshContainer = pMeshContainer;

	return S_OK;
}
//フレームを破棄する
HRESULT HIERARCHYDERIVED::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	delete[] pFrameToFree->Name;
	delete pFrameToFree;
	return S_OK;
}
//メッシュコンテナーを破棄する
HRESULT HIERARCHYDERIVED::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	DWORD iMaterial;
	MESHCONTAINERDERIVED *pMeshContainer = (MESHCONTAINERDERIVED*)pMeshContainerBase;

	delete[] pMeshContainer->Name;
	delete[] pMeshContainer->pAdjacency;
	delete[] pMeshContainer->pMaterials;

	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			 delete pMeshContainer->ppTextures[iMaterial];
		}
	}

	delete[] pMeshContainer->ppTextures;
	delete pMeshContainer->MeshData.pMesh;
	delete pMeshContainer;

	return S_OK;
}
//ボーンの領域を確保
HRESULT AllocateBoneMatrix(FRAMEDATA* InData, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	FRAMEDERIVED *pFrame = NULL;
	DWORD dwBoneAmt = 0;

	MESHCONTAINERDERIVED *pMeshContainer = (MESHCONTAINERDERIVED*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}
	dwBoneAmt = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneAmt];

	for (DWORD i = 0; i<dwBoneAmt; i++)
	{
		pFrame = (FRAMEDERIVED*)D3DXFrameFind(InData->pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;

	}
	return S_OK;
}
//すべてのボーンの領域を確保
HRESULT AllocateAllBoneMatrices(FRAMEDATA* InData, LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer != NULL)
	{
		if (FAILED(AllocateBoneMatrix(InData, pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameSibling != NULL)
	{
		if (FAILED(AllocateAllBoneMatrices(InData, pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		if (FAILED(AllocateAllBoneMatrices(InData, pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}