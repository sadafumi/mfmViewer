#ifndef __RENDER_H__
#define __RENDER_H__

#include "DrawData.h"
#include "main.h"
#include "Animation.h"

#define COLORMASK  (00000011)
#define ALPHAMASK  (11111100)
#define ALLPASMASK (00000000)


//ここから頂点
class BaseData
{
public:
	void init();
	void SetLight(D3DLIGHT9 in);		//Lightをセット
	void SetMtXWorld(D3DXMATRIX World);
		//ワールド行列をセット
	void SetMtXView(D3DXMATRIX View);		//ビュー行列をセット
	void SetMtXWProj(D3DXMATRIX Proj);		//プロジェクション行列をセット
protected:
	D3DXMATRIX g_mtxWorld;			//ワールド行列
	D3DXMATRIX g_mtxView;			//ビュー行列
	D3DXMATRIX g_mtxProj;			//プロジェクション行列
	D3DLIGHT9 Light;
};
class RenderVtx:public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);	//データをセット＆初期化
	void Draw();							//描画
	
private:
	VERTEXDATA *VerTexData;			//頂点データ
};
//ここまでメッシュ
//ここからメッシュ
class RenderMesh :public BaseData
{
public:
	void SetRendData(MESHDATA *MeshData);	//データをセット＆初期化
	void Draw();							//描画
private:
	MESHDATA *MeshData;				//メッシュデータ
	
};
//ここまでメッシュ
//ここからフレームメッシュ
class RenderFrameMesh :public BaseData
{
public:
	void SetRendData(FRAMEDATA *FrameMeshData);	//データをセット＆初期化
	void Draw();							//描画
private:
	void Updata(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void Convert(LPD3DXFRAME pFrameBase);
	void Render(MESHCONTAINERDERIVED* pMeshContainer, FRAMEDERIVED* pFrame);
	FRAMEDATA *FrameMeshData;				//メッシュデータ

};
//ここまでフレームメッシュ
//ここから頂点ストリーム
class RenderVtxStrip :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);	//データをセット＆初期化
	void Draw();							//描画
private:
	VERTEXDATA *VerTexData;			//頂点データ	
};
//ここまで頂点ストリーム
//ここからビルボード
class RenderBillBoard :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);			//データをセット＆初期化
	void Draw();									//描画
	void SetMtXScale(float x, float y, float z);	//スケールセット
	void SetMtXPos(float x, float y, float z);		//移動セット
	void SetMtXRotation(float x, float y, float z);	//回転セット
private:
	VERTEXDATA *VerTexData;			//頂点データ
	D3DXMATRIX g_mtxPos;			//移動行列
	D3DXMATRIX g_mtxScale;			//拡大行列
	D3DXMATRIX g_mtxRotation;		//回転行列
};
//ここまでビルボード
//ここからビルボードアニメーション
class RenderBillAnimation :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData, int aniIndex, int X, int Y);			//データをセット＆初期化
	void Draw();									//描画
	void SetAnimationSpeed(float Speed);			//アニメーションスピード
	void SetMtXScale(float x, float y, float z);	//スケールセット
	void SetMtXPos(float x, float y, float z);		//移動セット
	void SetMtXRotation(float x, float y, float z);	//回転セット
	void SetMtXView(D3DXMATRIX View);				//ビュー行列をセット
	void SetMtXWProj(D3DXMATRIX Proj);				//プロジェクション行列をセット
private:
	VERTEXDATA *VerTexData;			//頂点データ
	float      AniSpeed;			//アニメーション
	int		   AniCount;			//アニメーションカウント
	int		   AniIndex;			//アニメーション最大数
	int		   AniCountX;
	int		   AniCountY;
	D3DXMATRIX g_mtxPos;			//移動行列
	D3DXMATRIX g_mtxScale;			//拡大行列
	D3DXMATRIX g_mtxRotation;		//回転行列
};
//ここまでビルボードアニメーション
//ここからUI
class RenderUI:public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);			//データをセット＆初期化
	void Draw();									//描画
	void SetMoveScale(D3DXVECTOR3 pos);				// 拡縮先セット
	void SetMovePos(D3DXVECTOR3 scale);				// 移動先セット
	void Move(float MoveSpeed);						// リアルタイム動作
	void SetMtXScale(D3DXVECTOR3 pos);				// 実際のスケールセット
	void SetMtXPos(D3DXVECTOR3 scale);				// 実際の移動セット
	void SetMtXRotation(D3DXVECTOR3 rot);			// 回転セット
	void SetColor(D3DCOLOR InColor);				//カラーコードをセット
	void SetMtXView(D3DXMATRIX View);				//ビュー行列をセット
	void SetMtXWProj(D3DXMATRIX Proj);				//プロジェクション行列をセット
private:
	D3DXVECTOR3 ScalingPos;			// 実際の拡縮情報
	D3DXVECTOR3 ScalingSet;			// 目的拡縮情報
	D3DXVECTOR3 TranslationPos;		// 実際の平行移動
	D3DXVECTOR3 TranslationSet;		// 目的位置

	VERTEXDATA *VerTexData;			//頂点データ
	D3DXMATRIX g_mtxPos;			//移動行列
	D3DXMATRIX g_mtxScale;			//拡大行列
	D3DXMATRIX g_mtxRotation;		//回転行列
	D3DCOLOR   d3dColor;			//基礎のカラー
};
//ここまでUI
//ここから減算合成
class RenderSubsyn :public BaseData
{
public:
	void SetRendData(VERTEXDATA *VtxData);	//データをセット＆初期化
	void Draw();							//描画
private:
	VERTEXDATA *VerTexData;			//頂点データ

};
class Rendermfm :public BaseData
{
public:
	void SetRendData(MFMMESHDATA *inData);	//データをセット＆初期化
	void Draw();							//描画
private:
	MFMMESHDATA *pmfmData;			//頂点データ

};

//ここまで減算合成

#endif//__RENDER_H__

