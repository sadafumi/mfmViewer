#ifndef __ANIMETION_H__
#define __ANIMETION_H__

#include "DrawData.h"

//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
struct MESHCONTAINERDERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight;//重みの個数（重みとは頂点への影響。）
	DWORD dwBoneAmt;//ボーンの数
	LPD3DXBUFFER pBoneBuffer;//ボーン・テーブル
	D3DXMATRIX** ppBoneMatrix;//全てのボーンのワールド行列の先頭ポインター
	D3DXMATRIX* pBoneOffsetMatrices;//フレームとしてのボーンのワールド行列のポインター
};

//派生フレーム構造体 (それぞれのメッシュ用の最終ワールド行列を追加する）
struct FRAMEDERIVED : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};

class HIERARCHYDERIVED : public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(
		THIS_ LPCTSTR, 
		CONST D3DXMESHDATA*, 
		CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, 
		DWORD, 
		CONST DWORD *, 
		LPD3DXSKININFO, 
		LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
};

//ボーンの領域確保
HRESULT AllocateBoneMatrix(FRAMEDATA* InData, LPD3DXMESHCONTAINER);
//すべてのボーンの領域確保
HRESULT AllocateAllBoneMatrices(FRAMEDATA* InData, LPD3DXFRAME);


#endif//__ANIMETION_H__
