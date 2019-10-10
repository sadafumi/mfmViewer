#include "main.h"
#include "mfm.hpp"
#include "CreateData.h"
#include "Graphics.h"
#include <D3DCompiler.h>
#include <DxErr.h>
#include <fstream>
#include <Windows.h>

std::map<std::string, TextureBuffer> Create::TextureStock;
std::map<std::string, VertexShaderBuffer> Create::VertexShaderStock;
std::map<std::string, PixelShaderBuffer> Create::PixelShaderStock;
std::map<DWORD, DeclarationBuffer> Create::DeclarationStock;

void Create::Render_Target_Texture(DATA_TYPE::RENDERTARGETTEXTUREDATA * InOut, int x, int y)
{	
	DeviceHider::CreateTexture(&InOut->Texture.pTexture,x,y);
	InOut->Texture.pTexture->GetSurfaceLevel(0, &InOut->Surface.Surface);
}
void Create::Texture(DATA_TYPE::TEXTUREDATA * InOut, const char * TeXCFileName)
{
	D3DXIMAGE_INFO dil;
	D3DXGetImageInfoFromFile(TeXCFileName, &dil);					//テクスチャの情報取得
	InOut->TexSizeX = (int)dil.Width;		//テクスチャのXYを渡す
	InOut->TexSizeY = (int)dil.Height;
	InOut->pTexture = CheckTexture(TeXCFileName);
}
void Create::VerTex2D_NotTex(DATA_TYPE::VERTEX2DDATA * InOut, int w, int h)
{
	std::vector<VERTEX2D> vtx;

	vtx.push_back({ D3DXVECTOR4(-(float)w/2,-(float)h/2, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//0
	vtx.push_back({ D3DXVECTOR4( (float)w/2,-(float)h/2, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//1
	vtx.push_back({ D3DXVECTOR4( (float)w/2, (float)h/2, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//3
	vtx.push_back({ D3DXVECTOR4(-(float)w/2, (float)h/2, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//2

	VERTEX3D * pVer;
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx.size(), &InOut->pVetTexBuffer);
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;

}
void Create::VerTex2D(DATA_TYPE::VERTEX2DDATA *InOut, const char* TeXCFileName)
{
	std::vector<VERTEX2D> vtx;
	std::vector<WORD> index;
	D3DXIMAGE_INFO dil;

	D3DXGetImageInfoFromFile(TeXCFileName, &dil);					//テクスチャの情報取得
	InOut->TexSizeX = (int)dil.Width;		//テクスチャのXYを渡す
	InOut->TexSizeY = (int)dil.Height;

	//vtx.push_back({ D3DXVECTOR4(0              ,  0              , 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//0
	//vtx.push_back({ D3DXVECTOR4((float)InOut->TexSizeX / 2,  0              , 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//1
	//vtx.push_back({ D3DXVECTOR4((float)InOut->TexSizeX / 2, (float)InOut->TexSizeY / 2, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//3
	//vtx.push_back({ D3DXVECTOR4(0              ,  (float)InOut->TexSizeY / 2, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//2



	vtx.push_back({ D3DXVECTOR4(0,0, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//0
	vtx.push_back({ D3DXVECTOR4(1,0, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//1
	vtx.push_back({ D3DXVECTOR4(1,1, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//3
	vtx.push_back({ D3DXVECTOR4(0,1, 1.0f, 1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//2

	VERTEX3D * pVer;
	InOut->pTexture = CheckTexture(TeXCFileName);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx.size(), &InOut->pVetTexBuffer);
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;

}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//頂点データからデータを生成する関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void Create::VerTex(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, std::vector<VERTEX3D> *vtx, std::vector<WORD> *index)
{
	int IndeXsize;
	int vtXsize;
	
	LPWORD * pIndex;
	VERTEX3D * pVer;
	
	InOut->IndeXsize =  IndeXsize = index->size();
	InOut->vtXsize = vtXsize = vtx->size();
	
	if (TeXCFileName != NULL)
	{
		InOut->pTexture = CheckTexture(TeXCFileName);
	}

	DeviceHider::CreateIndex(sizeof(WORD) * index->size(), &InOut->pIndexBuffer);
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx->size(), &InOut->pVetTexBuffer);
	//DORADだった場合フォーマットを32にする
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, index->data(), sizeof(WORD) * index->size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx->data(), sizeof(VERTEX3D) * vtx->size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;

}
void Create::VerTex(DATA_TYPE::VERTEXDATA* InOut, const char* TeXCFileName, std::vector<VERTEX3D>* vtx)
{
	VERTEX3D* pVer;

	InOut->vtXsize = vtx->size();

	if (TeXCFileName != NULL)
	{
		InOut->pTexture = CheckTexture(TeXCFileName);
	}

	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx->size(), &InOut->pVetTexBuffer);
	//DORADだった場合フォーマットを32にする
	InOut->pVetTexBuffer->Lock(0, 0, (void**)& pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx->data(), sizeof(VERTEX3D) * vtx->size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//MFMファイルを読み込みモデルデータを生成する関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void Create::MFMMesh(DATA_TYPE::MFMMESHDATA *InOut, const char* TeXCFileName)
{
	mfmlib::Model inMFMmodel;
	std::vector< vertexbuff > mesh_;

	if (inMFMmodel.FileLoadMeshData((TCHAR*)TeXCFileName))
	{
		char err[124];
		sprintf(&err[0], "モデル「%s」の読み込みに失敗しました", TeXCFileName);
		MessageBox(NULL, &err[0], "モデルの読み込みに失敗しました", MB_OK);
		return;
	}
	mesh_.resize(inMFMmodel.Meshs.size());
	
	// メッシュ数分回す
	for (int i = 0; i < (int)mesh_.size(); i++)
	{
		// インデックス数分回す
		mesh_[i].Vertex.resize(inMFMmodel.Meshs[i].Index.size());
		InOut->MeshData.resize(inMFMmodel.Meshs[i].Index.size());

		int temp_material_index = inMFMmodel.Meshs[i].MaterialIndex;
		// メッシュインデックス番号取得
		InOut->MeshData[i].MaterialIndex = temp_material_index;


		for (int j = 0; j <(int)mesh_[i].Vertex.size(); j++)
		{
			// 頂点
			if (inMFMmodel.Meshs[i].Vertex.size() != 0)
			{
				int temp_index_num = inMFMmodel.Meshs[i].Index[j];
				mesh_[i].Vertex[j].Pos.x = inMFMmodel.Meshs[i].Vertex[temp_index_num].x;
				mesh_[i].Vertex[j].Pos.y = inMFMmodel.Meshs[i].Vertex[temp_index_num].y;
				mesh_[i].Vertex[j].Pos.z = inMFMmodel.Meshs[i].Vertex[temp_index_num].z;
			}

			// 法線
			if (inMFMmodel.Meshs[i].Normals.size() != 0)
			{
				mesh_[i].Vertex[j].Normal.x = inMFMmodel.Meshs[i].Normals[j].x;
				mesh_[i].Vertex[j].Normal.y = inMFMmodel.Meshs[i].Normals[j].y;
				mesh_[i].Vertex[j].Normal.z = inMFMmodel.Meshs[i].Normals[j].z;
			}

			// UV
			if (inMFMmodel.Meshs[i].UV.size() != 0)
			{
				mesh_[i].Vertex[j].texcoord.x = inMFMmodel.Meshs[i].UV[j].U;
				mesh_[i].Vertex[j].texcoord.y = inMFMmodel.Meshs[i].UV[j].V;
			}

			mesh_[i].Vertex[j].color = D3DXCOLOR(255,255,255,255);
		}
		// テクスチャ名の読み込み

		if (inMFMmodel.Material[temp_material_index].name.data() != "")
		{
			InOut->MeshData[i].TexName = inMFMmodel.Material[temp_material_index].name;
		}
		// プリミティブ数の取得
		InOut->MeshData[i].PrimitiveNum = inMFMmodel.Meshs[i].PrimitiveIndex;
	}
	// マテリアル数の確定
	//InOut->Material.resize(inMFMmodel);

	VERTEX3D * pVer;

	InOut->VertexBuffer.resize(mesh_.size());
	InOut->Texture.resize(mesh_.size());
	for (int i = 0; i < (int)mesh_.size(); i++)
	{
		// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
		DeviceHider::CreateVerTex(sizeof(VERTEX3D) * mesh_[i].Vertex.size(), &InOut->VertexBuffer[i]);
		InOut->VertexBuffer[i]->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);
		memcpy(pVer, mesh_[i].Vertex.data(), sizeof(VERTEX3D) * mesh_[i].Vertex.size());
		InOut->VertexBuffer[i]->Unlock();

		TCHAR Buff[MAX_PATH];
		EditPath(Buff, (TCHAR*)InOut->MeshData[i].TexName.data(), (TCHAR*)TeXCFileName);

		InOut->Texture[i] = CheckTexture(Buff);
	}
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//MFMファイルを読み込みスキンメッシュアニメーションのついたモデルデータを生成する関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void Create::MFMAnime(DATA_TYPE::MFMANIMEDATA *InOut, const char* TeXCFileName)
{
	mfmlib::Model inMFMmodel;
	std::vector< Shaderbuff > mesh_;

	inMFMmodel.FileLoadFullData((TCHAR*)TeXCFileName);

	
	mesh_.resize(inMFMmodel.Meshs.size());

	// メッシュ数分回す
	for (int i = 0; i < (int)mesh_.size(); i++)
	{
		// インデックス数分回す
		mesh_[i].Vertex.resize(inMFMmodel.Meshs[i].Index.size());
		InOut->MeshData.resize(inMFMmodel.Meshs[i].Index.size());

		int temp_material_index = inMFMmodel.Meshs[i].MaterialIndex;
		// メッシュインデックス番号取得
		InOut->MeshData[i].MaterialIndex = temp_material_index;


		for (int j = 0; j < (int)mesh_[i].Vertex.size(); j++)
		{
			// 頂点
			if (inMFMmodel.Meshs[i].Vertex.size() != 0)
			{
				int temp_index_num = inMFMmodel.Meshs[i].Index[j];
				mesh_[i].Vertex[j].Pos.x = inMFMmodel.Meshs[i].Vertex[temp_index_num].x;
				mesh_[i].Vertex[j].Pos.y = inMFMmodel.Meshs[i].Vertex[temp_index_num].y;
				mesh_[i].Vertex[j].Pos.z = inMFMmodel.Meshs[i].Vertex[temp_index_num].z;
			}

			// 法線
			if (inMFMmodel.Meshs[i].Normals.size() != 0)
			{
				mesh_[i].Vertex[j].Normal.x = inMFMmodel.Meshs[i].Normals[j].x;
				mesh_[i].Vertex[j].Normal.y = inMFMmodel.Meshs[i].Normals[j].y;
				mesh_[i].Vertex[j].Normal.z = inMFMmodel.Meshs[i].Normals[j].z;
			}

			// UV
			if (inMFMmodel.Meshs[i].UV.size() != 0)
			{
				mesh_[i].Vertex[j].texcoord.x = inMFMmodel.Meshs[i].UV[j].U;
				mesh_[i].Vertex[j].texcoord.y = inMFMmodel.Meshs[i].UV[j].V;
			}

			mesh_[i].Vertex[j].color = D3DXCOLOR(255, 255, 255, 255);
		}
		// テクスチャ名の読み込み

		if (inMFMmodel.Material[temp_material_index].name.data() != "")
		{
			InOut->MeshData[i].TexName = inMFMmodel.Material[temp_material_index].name;
		}
		// プリミティブ数の取得
		InOut->MeshData[i].PrimitiveNum = inMFMmodel.Meshs[i].PrimitiveIndex;
	}
		//=====================================================================================================
		//アニメーション数を取得
		//InOut->nAnimFrame = inMFMmodel.FrameNum;
		//=====================================================================================================

		//=====================================================================================================
		//ボーンを取得
		////メッシュ数分だけボーン領域を拡張
		//InOut->bone.resize(mesh_.size());
		////1メッシュに存在するボーン数分だけ領域を拡張
		//InOut->bone[i].resize(inMFMmodel.BoneData[i].BoneNum);
		//for (int j = 0; j < (int)InOut->bone[i].size(); j++)
		//{
		//	//アニメーションフレーム分だけ拡張
		//	InOut->bone[i][j].MatAry.resize(InOut->nAnimFrame);
		//	D3DXMATRIX init, inv;
		//	for (int r = 0; r < 4; r++)
		//	{
		//		for (int c = 0; c < 4; c++)
		//		{
		//			//初期姿勢行列を取得
		//			init(r, c) = inMFMmodel.BoneData[i].Data[j].init.Get(r,c);
		//		}
		//	}
		//	//初期姿勢行列の逆行列を作成
		//	D3DXMatrixInverse(&inv, NULL, &init);
		//	for (int k = 0; k < InOut->nAnimFrame; k++)
		//	{
		//		D3DXMATRIX  perFrame;
		//		for (int r = 0; r < 4; r++)
		//		{
		//			for (int c = 0; c < 4; c++)
		//			{
		//				//行列移動
		//				perFrame(r, c) = inMFMmodel.BoneData[i].Data[j].perFrame.Data[k].Get(r, c);
		//			}
		//		}
		//		//移動行列に初期姿勢逆行列をかける
		//		InOut->bone[i][j].MatAry[k] = inv * perFrame;
		//	}
		//}
		////=====================================================================================================
	//}
	//=====================================================================================================

	
	VERTEX3D * pVer;

	InOut->VertexBuffer.resize(mesh_.size());
	InOut->Texture.resize(mesh_.size());
	for (int i = 0; i < (int)mesh_.size(); i++)
	{
		// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
		DeviceHider::CreateVerTex(sizeof(VERTEXANI) * mesh_[i].Vertex.size(), &InOut->VertexBuffer[i]);

		InOut->VertexBuffer[i]->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);
		memcpy(pVer, mesh_[i].Vertex.data(), sizeof(VERTEXANI) * mesh_[i].Vertex.size());
		InOut->VertexBuffer[i]->Unlock();

		TCHAR Buff[MAX_PATH];
		EditPath(Buff, (TCHAR*)InOut->MeshData[i].TexName.data(), (TCHAR*)TeXCFileName);
		InOut->Texture[i] = CheckTexture(Buff);
	}
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//メッシュフィールド用のデータを生成する関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void Create::MeshField(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, int w, int h,float Wsize, float Hsize, std::vector<std::vector<float>> Heigh)
{

	std::vector<VERTEX3D>		vtx;
	std::vector<WORD>			index;


	InOut->TexSizeX = w;
	InOut->TexSizeY = h;

	int X = 0, Y = 0;
	float Xof = h * 1.0f, Yof = w * 1.0f;


	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	int no;


	VERTEX3D *pV;
	DWORD *pIndex;


	h++;
	w++;
	for (X = 0; X < h; X++)
	{
		for (Y = 0; Y < w; Y++)
		{
			float HeiBuff = 0;
			if(Heigh.size() != 0)
			{
				HeiBuff = Heigh[X][Y];
			}
			//(float)Hei
			//頂点を作成
			InOut->vtx.push_back({ D3DXVECTOR3(((float)X - Xof) * Wsize,HeiBuff, ((float)Y - Yof)* Hsize) ,D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2( (float)X ,(float)Y) });//0
			if(X != (h - 1) )
			{//下段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)((w + Y) + (X * w)));
			}
			
			if (X < (h - 1))
			{//上段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)(Y + (X * w)));
			}
		}
		if (X < (h - 2))
		{//縮退用の頂点インデックスを指定
			InOut->index.push_back((unsigned short)((Y - 1) + (X * w)));
			InOut->index.push_back((unsigned short)((X + 2) * w));
		}

	}


	h--;
	w--;
	for (int z = 0; z <= h; z++)//0~4
	{
		for (int x = 0; x <=w; x++)//0~4
		{
			no = x + (z * (w + 1));
			if (no > w && no < ((w + 1) * (h + 1) - (w + 1)) && no % (w + 1) != 0 && no % (w + 1) != w)
			{
				vx = InOut->vtx[no + 1].Pos - InOut->vtx[no - 1].Pos;
				nx.x = -vx.y;
				nx.y = vx.x;
				nx.z = 0.0f;

				vz = InOut->vtx[no + (w + 1)].Pos - InOut->vtx[no - (w + 1)].Pos;
				nz.x = -vz.y;
				nz.y = vz.x;
				nz.z = 0.0f;

				n = nx + nz;
				D3DXVec3Normalize(&n, &n);
				InOut->vtx[no].Normal = n;
			}
			else
			{
				InOut->vtx[no].Normal = { 0.0f,-1.0f,0.0f };//
			}

		}
	}

	InOut->IndeXsize = InOut->index.size();
	InOut->vtXsize = InOut->vtx.size();
	InOut->pTexture = CheckTexture( TeXCFileName);
	InOut->vtXsize = (int)((w+ 1) * (h + 1));
	InOut->IndeXsize = ((w * h * 2) + ((h- 1) * 4));
	DeviceHider::CreateIndex(sizeof(WORD) * InOut->index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * InOut->vtx.size(), &InOut->pVetTexBuffer);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, InOut->index.data(), sizeof(WORD) * InOut->index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pV, InOut->vtx.data(), sizeof(VERTEX3D) * InOut->vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
																		// マテリアル数の確定
}
void Create::MeshFlatField(DATA_TYPE::VERTEXDATA * InOut, const char * TeXCFileName, int w, int h, float Wsize, float Hsize)
{
	std::vector<VERTEX3D>		vtx;
	std::vector<WORD>			index;


	InOut->TexSizeX = w;
	InOut->TexSizeY = h;

	int X = 0, Y = 0;
	float Xof = h * 1.0f, Yof = w * 1.0f;


	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	int no;


	VERTEX3D *pV;
	DWORD *pIndex;


	h++;
	w++;
	for (X = 0; X < h; X++)
	{
		for (Y = 0; Y < w; Y++)
		{
			//(float)Hei
			//頂点を作成
			InOut->vtx.push_back({ D3DXVECTOR3(((float)X - Xof) * Wsize,0, ((float)Y - Yof)* Hsize) ,D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2((float)X ,(float)Y) });//0
			if (X != (h - 1))
			{//下段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)((w + Y) + (X * w)));
			}

			if (X < (h - 1))
			{//上段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)(Y + (X * w)));
			}
		}
		if (X < (h - 2))
		{//縮退用の頂点インデックスを指定
			InOut->index.push_back((unsigned short)((Y - 1) + (X * w)));
			InOut->index.push_back((unsigned short)((X + 2) * w));
		}

	}


	h--;
	w--;
	for (int z = 0; z <= h; z++)//0~4
	{
		for (int x = 0; x <= w; x++)//0~4
		{
			no = x + (z * (w + 1));
			if (no > w && no < ((w + 1) * (h + 1) - (w + 1)) && no % (w + 1) != 0 && no % (w + 1) != w)
			{
				vx = InOut->vtx[no + 1].Pos - InOut->vtx[no - 1].Pos;
				nx.x = -vx.y;
				nx.y = vx.x;
				nx.z = 0.0f;

				vz = InOut->vtx[no + (w + 1)].Pos - InOut->vtx[no - (w + 1)].Pos;
				nz.x = -vz.y;
				nz.y = vz.x;
				nz.z = 0.0f;

				n = nx + nz;
				D3DXVec3Normalize(&n, &n);
				InOut->vtx[no].Normal = n;
			}
			else
			{
				InOut->vtx[no].Normal = { 0.0f,-1.0f,0.0f };//
			}

		}
	}

	InOut->IndeXsize = InOut->index.size();
	InOut->vtXsize = InOut->vtx.size();
	InOut->pTexture = CheckTexture(TeXCFileName);
	InOut->vtXsize = (int)((w + 1) * (h + 1));
	InOut->IndeXsize = ((w * h * 2) + ((h - 1) * 4));
	DeviceHider::CreateIndex(sizeof(WORD) * InOut->index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * InOut->vtx.size(), &InOut->pVetTexBuffer);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, InOut->index.data(), sizeof(WORD) * InOut->index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pV, InOut->vtx.data(), sizeof(VERTEX3D) * InOut->vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;

}
void Create::MeshNoField(DATA_TYPE::VERTEXDATA * InOut, int w, int h, float Wsize, float Hsize)
{

	std::vector<VERTEX3D>		vtx;
	std::vector<WORD>			index;


	InOut->TexSizeX = w;
	InOut->TexSizeY = h;

	int X = 0, Y = 0;
	float Xof = h * 1.0f, Yof = w * 1.0f;


	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	int no;


	VERTEX3D *pV;
	DWORD *pIndex;


	h++;
	w++;
	for (X = 0; X < h; X++)
	{
		for (Y = 0; Y < w; Y++)
		{
			//(float)Hei
			//頂点を作成
			InOut->vtx.push_back({ D3DXVECTOR3((((float)X - Xof) * Wsize), 0,(((float)Y - Yof)* Hsize)) ,D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2((float)X ,(float)Y) });//0
			if (X != (h - 1))
			{//下段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)((w + Y) + (X * w)));
			}

			if (X < (h - 1))
			{//上段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)(Y + (X * w)));
			}
		}
		if (X < (h - 2))
		{//縮退用の頂点インデックスを指定
			InOut->index.push_back((unsigned short)((Y - 1) + (X * w)));
			InOut->index.push_back((unsigned short)((X + 2) * w));
		}

	}


	h--;
	w--;
	for (int z = 0; z <= h; z++)//0~4
	{
		for (int x = 0; x <= w; x++)//0~4
		{
			no = x + (z * (w + 1));
			if (no > w && no < ((w + 1) * (h + 1) - (w + 1)) && no % (w + 1) != 0 && no % (w + 1) != w)
			{
				vx = InOut->vtx[no + 1].Pos - InOut->vtx[no - 1].Pos;
				nx.x = -vx.y;
				nx.y = vx.x;
				nx.z = 0.0f;

				vz = InOut->vtx[no + (w + 1)].Pos - InOut->vtx[no - (w + 1)].Pos;
				nz.x = -vz.y;
				nz.y = vz.x;
				nz.z = 0.0f;

				n = nx + nz;
				D3DXVec3Normalize(&n, &n);
				InOut->vtx[no].Normal = n;
			}
			else
			{
				InOut->vtx[no].Normal = { 0.0f,-1.0f,0.0f };//
			}

		}
	}

	InOut->IndeXsize = InOut->index.size();
	InOut->vtXsize = InOut->vtx.size();
	InOut->vtXsize = (int)((w + 1) * (h + 1));
	InOut->IndeXsize = ((w * h * 2) + ((h - 1) * 4));
	DeviceHider::CreateIndex(sizeof(WORD) * InOut->index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * InOut->vtx.size(), &InOut->pVetTexBuffer);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, InOut->index.data(), sizeof(WORD) * InOut->index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pV, InOut->vtx.data(), sizeof(VERTEX3D) * InOut->vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
																		// マテリアル数の確定
}
void Create::MeshBoard(DATA_TYPE::VERTEXDATA * InOut, const char* TeXCFileName, int w, int h, float Wsize, float Hsize, D3DXVECTOR2 Pos)
{

	std::vector<VERTEX3D>		vtx;
	std::vector<WORD>			index;


	InOut->TexSizeX = w;
	InOut->TexSizeY = h;

	int X = 0, Y = 0;
	float Xof = h * 1.0f, Yof = w * 1.0f;


	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	int no;


	VERTEX3D *pV;
	DWORD *pIndex;


	h++;
	w++;
	for (X = 0; X < h; X++)
	{
		for (Y = 0; Y < w; Y++)
		{
			//(float)Hei
			//頂点を作成
			InOut->vtx.push_back({ D3DXVECTOR3(Pos.x + (((float)X - Xof) * Wsize), (((float)Y - Yof)* Hsize) ,Pos.y) ,D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2((float)X ,(float)Y) });//0
			if (X != (h - 1))
			{//下段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)((w + Y) + (X * w)));
			}

			if (X < (h - 1))
			{//上段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)(Y + (X * w)));
			}
		}
		if (X < (h - 2))
		{//縮退用の頂点インデックスを指定
			InOut->index.push_back((unsigned short)((Y - 1) + (X * w)));
			InOut->index.push_back((unsigned short)((X + 2) * w));
		}

	}


	h--;
	w--;
	for (int z = 0; z <= h; z++)//0~4
	{
		for (int x = 0; x <= w; x++)//0~4
		{
			no = x + (z * (w + 1));
			if (no > w && no < ((w + 1) * (h + 1) - (w + 1)) && no % (w + 1) != 0 && no % (w + 1) != w)
			{
				vx = InOut->vtx[no + 1].Pos - InOut->vtx[no - 1].Pos;
				nx.x = -vx.y;
				nx.y = vx.x;
				nx.z = 0.0f;

				vz = InOut->vtx[no + (w + 1)].Pos - InOut->vtx[no - (w + 1)].Pos;
				nz.x = -vz.y;
				nz.y = vz.x;
				nz.z = 0.0f;

				n = nx + nz;
				D3DXVec3Normalize(&n, &n);
				InOut->vtx[no].Normal = n;
			}
			else
			{
				InOut->vtx[no].Normal = { 0.0f,-1.0f,0.0f };//
			}

		}
	}

	InOut->IndeXsize = InOut->index.size();
	InOut->vtXsize = InOut->vtx.size();
	InOut->pTexture = CheckTexture(TeXCFileName);
	InOut->vtXsize = (int)((w + 1) * (h + 1));
	InOut->IndeXsize = ((w * h * 2) + ((h - 1) * 4));
	DeviceHider::CreateIndex(sizeof(WORD) * InOut->index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * InOut->vtx.size(), &InOut->pVetTexBuffer);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, InOut->index.data(), sizeof(WORD) * InOut->index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pV, InOut->vtx.data(), sizeof(VERTEX3D) * InOut->vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
																		// マテリアル数の確定
}
void Create::MeshOneTex(DATA_TYPE::VERTEXDATA * InOut, const char* TeXCFileName, int w, int h, float Wsize, float Hsize)
{

	std::vector<VERTEX3D>		vtx;
	std::vector<WORD>			index;


	InOut->TexSizeX = w;
	InOut->TexSizeY = h;

	int X = 0, Y = 0;
	float Xof = h * 1.0f, Yof = w * 1.0f;


	D3DXVECTOR3 nx;
	D3DXVECTOR3 nz;
	D3DXVECTOR3 vx;
	D3DXVECTOR3 vz;
	D3DXVECTOR3 n;
	int no;


	VERTEX3D *pV;
	DWORD *pIndex;


	h++;
	w++;
	for (X = 0; X < h; X++)
	{
		for (Y = 0; Y < w; Y++)
		{
			//頂点を作成
			InOut->vtx.push_back({ D3DXVECTOR3(((float)X - Xof) * Wsize, 0,((float)Y - Yof)* Hsize),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2((float)X / (float)h ,(float)Y / (float)w) });//0
			if (X != (h - 1))
			{//下段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)((w + Y) + (X * w)));
			}

			if (X < (h - 1))
			{//上段の頂点インデックスを指定
				InOut->index.push_back((unsigned short)(Y + (X * w)));
			}
		}
		if (X < (h - 2))
		{//縮退用の頂点インデックスを指定
			InOut->index.push_back((unsigned short)((Y - 1) + (X * w)));
			InOut->index.push_back((unsigned short)((X + 2) * w));
		}

	}


	h--;
	w--;
	for (int z = 0; z <= h; z++)//0~4
	{
		for (int x = 0; x <= w; x++)//0~4
		{
			no = x + (z * (w + 1));
			if (no > w && no < ((w + 1) * (h + 1) - (w + 1)) && no % (w + 1) != 0 && no % (w + 1) != w)
			{
				vx = InOut->vtx[no + 1].Pos - InOut->vtx[no - 1].Pos;
				nx.x = -vx.y;
				nx.y = vx.x;
				nx.z = 0.0f;

				vz = InOut->vtx[no + (w + 1)].Pos - InOut->vtx[no - (w + 1)].Pos;
				nz.x = -vz.y;
				nz.y = vz.x;
				nz.z = 0.0f;

				n = nx + nz;
				D3DXVec3Normalize(&n, &n);
				InOut->vtx[no].Normal = n;
			}
			else
			{
				InOut->vtx[no].Normal = { 0.0f,-1.0f,0.0f };//
			}

		}
	}

	InOut->IndeXsize = InOut->index.size();
	InOut->vtXsize = InOut->vtx.size();
	InOut->pTexture = CheckTexture(TeXCFileName);
	InOut->vtXsize = (int)((w + 1) * (h + 1));
	InOut->IndeXsize = ((w * h * 2) + ((h - 1) * 4));
	DeviceHider::CreateIndex(sizeof(WORD) * InOut->index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * InOut->vtx.size(), &InOut->pVetTexBuffer);
	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, InOut->index.data(), sizeof(WORD) * InOut->index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pV, InOut->vtx.data(), sizeof(VERTEX3D) * InOut->vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
																		// マテリアル数の確定
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//ビルボード用のデータを生成する関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void Create::MeshBoard(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName)
{
	std::vector<VERTEX3D> vtx;
	std::vector<WORD> index;

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



	
	LPWORD * pIndex;
	VERTEX3D * pVer;
	InOut->IndeXsize = index.size();
	InOut->vtXsize = vtx.size();
	InOut->pTexture = CheckTexture( TeXCFileName);
	DeviceHider::CreateIndex(sizeof(WORD) * index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx.size(), &InOut->pVetTexBuffer);

	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, index.data(), sizeof(WORD) * index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
}
void Create::MeshBoardBump(DATA_TYPE::VERTEXDATA * InOut, const char* TeXCFileName, const char* BumpFileName ,int size)
{
	std::vector<VERTEX3D> vtx;
	std::vector<WORD> index;
	D3DXIMAGE_INFO dil;

	D3DXGetImageInfoFromFile(TeXCFileName, &dil);					//テクスチャの情報取得
	InOut->TexSizeX = (int)dil.Width;		//テクスチャのXYを渡す
	InOut->TexSizeY = (int)dil.Height;

	vtx.push_back({ D3DXVECTOR3(-(float)InOut->TexSizeX / size, -(float)InOut->TexSizeY / size, 0),D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//0
	vtx.push_back({ D3DXVECTOR3( (float)InOut->TexSizeX / size, -(float)InOut->TexSizeY / size, 0),D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//1
	vtx.push_back({ D3DXVECTOR3(-(float)InOut->TexSizeX / size,  (float)InOut->TexSizeY / size, 0),D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//2
	vtx.push_back({ D3DXVECTOR3( (float)InOut->TexSizeX / size,  (float)InOut->TexSizeY / size, 0),D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//3

	index.push_back(0);
	index.push_back(2);
	index.push_back(1);
	index.push_back(3);


	//index.push_back(1);
	//index.push_back(3);
	//index.push_back(3);




	LPWORD * pIndex;
	VERTEX3D * pVer;
	InOut->IndeXsize = index.size();
	InOut->vtXsize = vtx.size();
	InOut->pTexture = CheckTexture(TeXCFileName);
	InOut->pBump_Map = CheckTexture(BumpFileName);
	DeviceHider::CreateIndex(sizeof(WORD) * index.size(), &InOut->pIndexBuffer);//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx.size(), &InOut->pVetTexBuffer);

	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, index.data(), sizeof(WORD) * index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;

}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//ビルボードのテクスチャアニメーションに必要なデータを生成する関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void Create::MeshAnimationBoard(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName)
{
	std::vector<VERTEX3D> vtx;
	std::vector<WORD> index;
	D3DXIMAGE_INFO dil;

	D3DXGetImageInfoFromFile(TeXCFileName, &dil);					//テクスチャの情報取得
	InOut->TexSizeX = (int)dil.Width;		//テクスチャのXYを渡す
	InOut->TexSizeY = (int)dil.Height;

	vtx.push_back({ D3DXVECTOR3(-0.5, -0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,1) });//0
	vtx.push_back({ D3DXVECTOR3(0.5, -0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,1) });//1
	vtx.push_back({ D3DXVECTOR3(-0.5,  0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(1 ,0) });//2
	vtx.push_back({ D3DXVECTOR3(0.5,  0.5, 0),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(0 ,0) });//3

	index.push_back(1);
	index.push_back(0);
	index.push_back(3);
	index.push_back(2);

	
	LPWORD * pIndex;
	VERTEX3D * pVer;
	InOut->IndeXsize = index.size();
	InOut->vtXsize = vtx.size();
	InOut->pTexture = CheckTexture( TeXCFileName);
	DeviceHider::CreateIndex(sizeof(WORD) * index.size(), &InOut->pIndexBuffer);
	//DORADだった場合フォーマットを32にする
	DeviceHider::CreateVerTex(sizeof(VERTEX3D) * vtx.size(), &InOut->pVetTexBuffer);

	InOut->pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pIndex, index.data(), sizeof(WORD) * index.size());		//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pIndexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...
	InOut->pVetTexBuffer->Lock(0, 0, (void**)&pVer, D3DLOCK_DISCARD);	//こっからここまで俺のモーン( ´∀｀)
	memcpy(pVer, vtx.data(), sizeof(VERTEX3D) * vtx.size());			//俺の領地に城を立てる(｀・ω・´)ｼｬｷｰﾝ
	InOut->pVetTexBuffer->Unlock();										//やっぱ無理土地手放す(´・ω:;.:...;
}

bool Create::VertexShader(DATA_TYPE::VERTEXSHADERDATA *Out, const char* TeXCFileName)
{	
	if (VertexShaderStock.find(TeXCFileName) == VertexShaderStock.end())
	{
		HRESULT hrResult;

		ID3DBlob* pt_d3dblShaderBlob;
		ID3DBlob* pt_d3dblErrorBlob;
		std::fstream fsFile(TeXCFileName);

		if (fsFile.fail())
		{
			MessageBox(NULL, TeXCFileName, "VerTexShaderファイルの読み込み失敗", 0);
			return false;
		}
		std::string str((std::istreambuf_iterator<char>(fsFile)), std::istreambuf_iterator<char>());

		hrResult = D3DCompile(
			str.data(),
			str.size(),
			"",
			NULL,
			NULL,
			"main",
			"vs_3_0",
			D3DCOMPILE_OPTIMIZATION_LEVEL3,
			NULL,
			&pt_d3dblShaderBlob,
			&pt_d3dblErrorBlob
		);
		if (pt_d3dblErrorBlob != NULL)
		{
			//char* sErrorMessage = (char*)pt_d3dblErrorBlob->GetBufferPointer();
			MessageBox(NULL, (char*)pt_d3dblErrorBlob->GetBufferPointer(), "VerTexShaderコンパイルerror", 0);
			pt_d3dblErrorBlob->Release();
			return true;
		}

		if (FAILED(hrResult))
		{
			return true;
		}

		VertexShaderBuffer buff;
		hrResult = DeviceHider::CreateVertexShader((DWORD*)pt_d3dblShaderBlob->GetBufferPointer(), &buff.VertexShader);
		VertexShaderStock.emplace(TeXCFileName,buff);
		Out->pVertexShader = VertexShaderStock[TeXCFileName].VertexShader;


		if (FAILED(hrResult) || pt_d3dblErrorBlob != NULL)
		{
			//const char* sError = DXGetErrorString(hrResult);
			return true;
		}
		if (fsFile.is_open())
		{
			fsFile.close();
		}
		pt_d3dblShaderBlob->Release();
	}
	else
	{
		Out->pVertexShader = VertexShaderStock[TeXCFileName].VertexShader;
	}
	return false;
}
bool Create::PixelShader(DATA_TYPE::PIXELSHADERDATA *Out, const char* TeXCFileName)
{
	if (PixelShaderStock.find(TeXCFileName) == PixelShaderStock.end())
	{
		HRESULT hrResult;

		ID3DBlob* pt_d3dblShaderBlob;
		ID3DBlob* pt_d3dblErrorBlob;
		std::fstream fsFile(TeXCFileName);
		if (fsFile.fail())
		{
			MessageBox(NULL, TeXCFileName, "PixelShaderファイルの読み込み失敗", 0);
			return false;
		}
		std::string str((std::istreambuf_iterator<char>(fsFile)), std::istreambuf_iterator<char>());

		hrResult = D3DCompile(
			str.data(),
			str.size(),
			"",
			NULL,
			NULL,
			"main",
			"ps_3_0",
			D3DCOMPILE_OPTIMIZATION_LEVEL3,
			NULL,
			&pt_d3dblShaderBlob,
			&pt_d3dblErrorBlob
		);

		if (pt_d3dblErrorBlob != NULL)
		{
			//char* sErrorMessage = (char*)pt_d3dblErrorBlob->GetBufferPointer();
			MessageBox(NULL, (char*)pt_d3dblErrorBlob->GetBufferPointer(), "PixelShaderコンパイルerror", 0);

			pt_d3dblErrorBlob->Release();
			return true;
		}

		if (FAILED(hrResult))
		{
			return true;
		}

		PixelShaderBuffer buff;
		hrResult = DeviceHider::CreatePixelShader((DWORD*)pt_d3dblShaderBlob->GetBufferPointer(), &buff.PixelShader);
		PixelShaderStock.emplace(TeXCFileName,buff);
		Out->pPixelShader = PixelShaderStock[TeXCFileName].PixelShader;

		if (FAILED(hrResult) || pt_d3dblErrorBlob != NULL)
		{
			//const char* sError = DXGetErrorString(hrResult);
			return true;
		}
		if (fsFile.is_open())
		{
			fsFile.close();
		}

		pt_d3dblShaderBlob->Release();

	}
	else
	{
		Out->pPixelShader = PixelShaderStock[TeXCFileName].PixelShader;
	}
	return false;
}

void Create::Declaration(DATA_TYPE::DECLARATIONDATA *out, DWORD fvf)
{
	if(DeclarationStock.find(fvf) == DeclarationStock.end())
	{
		std::vector<D3DVERTEXELEMENT9> Elements;
		WORD wOffset = 0;

		if ((fvf & D3DFVF_XYZRHW) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 });
			wOffset += sizeof(float) * 4;
		}
		else if ((fvf & D3DFVF_XYZ) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 });
			wOffset += sizeof(float) * 3;
		}

		if ((fvf & D3DFVF_NORMAL) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 });
			wOffset += sizeof(float) * 3;
		}

		if ((fvf & D3DFVF_DIFFUSE) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 });
			wOffset += sizeof(unsigned long);
		}

		if ( (int)( fvf >= D3DFVF_TEX1 ) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 });
			wOffset += sizeof(float) * 2;
		}

		if ((fvf & D3DFVF_LASTBETA_UBYTE4) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 });
			wOffset += sizeof(float) * 4;
		}
		if ((fvf & D3DFVF_LASTBETA_D3DCOLOR) > 0)
		{
			Elements.push_back({ 0, wOffset,  D3DDECLTYPE_UBYTE4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 });
			wOffset += sizeof(unsigned int) * 4;
		}
		if ((fvf & D3DFVF_TEX2) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 });
			wOffset += sizeof(float) * 3;
		}
		if ((fvf & D3DFVF_TEX3) > 0)
		{
			Elements.push_back({ 0, wOffset, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 });
			wOffset += sizeof(float) * 3;
		}

		Elements.push_back(D3DDECL_END());
		HRESULT hrResult;
		DeclarationBuffer Buff;
		hrResult = DeviceHider::CreateVertexDeclaration(Elements.data(), &Buff.Declaration);

		if (FAILED(hrResult) )
		{
			return;
		}
		DeclarationStock.emplace(fvf, Buff);
		out->pDeclaration = DeclarationStock[fvf].Declaration;;

	}
	else
	{
		out->pDeclaration = DeclarationStock[fvf].Declaration;
	}
}

LPDIRECT3DTEXTURE9 Create::CheckTexture( const char* TeXCFileName)
{
	if (TextureStock.find(TeXCFileName) == TextureStock.end())
	{
		TextureBuffer buff;
		if (DeviceHider::CreateTexture(TeXCFileName, &buff.Texture))
		{
			char err[124];
			sprintf(&err[0], "テクスチャの取得「%s」に失敗しました", TeXCFileName);
			MessageBox(NULL, &err[0], "テクスチャの読み込みに失敗しました", MB_OK);
			return NULL;
		}
		TextureStock.emplace(TeXCFileName,buff);
		return TextureStock[TeXCFileName].Texture;
	}
	else
	{
		return TextureStock[TeXCFileName].Texture;
	}
}

void Create::Destroy()
{	
	for (std::pair<std::string, TextureBuffer> Texture : TextureStock)
	{
		Texture.second.Texture->Release();
	}
	TextureStock.clear();

	for (std::pair<std::string, VertexShaderBuffer> VertexShader : VertexShaderStock)
	{
		VertexShader.second.VertexShader->Release();
	}
	DeclarationStock.clear();
	for (std::pair<std::string, PixelShaderBuffer> PixelShader : PixelShaderStock)
	{
		PixelShader.second.PixelShader->Release();
	}
	DeclarationStock.clear();

	for (std::pair<DWORD, DeclarationBuffer> Declaration : DeclarationStock)
	{
		Declaration.second.Declaration->Release();
	}
	DeclarationStock.clear();
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//ファイルパスを整える関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//ファイルパスを切り取る関数
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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
TEXUV Create::UVCode(const char* infileName, int AniNum, int nTexWidth, int nTexHiegth)
{
	TEXUV OutUV;
	D3DXIMAGE_INFO dil = Create::LoadTextureInfo(infileName);

	int widht = (int)dil.Width;		//テクスチャのXYを渡す
	int heght = (int)dil.Height;

	int patternNUM = AniNum / 1 % (nTexWidth * nTexHiegth);	//アニメーションのパターン数
	int patternH = (patternNUM % nTexWidth);			//
	int patternV = (patternNUM / nTexWidth);			//
	int nTexWid = (widht / nTexWidth);	//
	int nTexHei = (heght / nTexHiegth);	//
	int tcx = patternH * nTexWid;		//
	int tcy = patternV * nTexHei;		//


	OutUV.U0 = (float)tcx / widht;
	OutUV.V0 = (float)tcy / heght;
	OutUV.U1 = (float)(tcx + nTexWid) / widht;
	OutUV.V1 = (float)(tcy + nTexHei) / heght;

	return OutUV;
}
D3DXIMAGE_INFO Create::LoadTextureInfo(const char* lpFlieName)
{
	D3DXIMAGE_INFO dil;
	D3DXGetImageInfoFromFile(lpFlieName, &dil);					//テクスチャの情報取得
	return dil;
}