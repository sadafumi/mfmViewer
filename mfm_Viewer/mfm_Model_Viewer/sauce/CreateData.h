#ifndef __CREATEDATA_H__
#define __CREATEDATA_H__

#include"Include.h"



void CreateVerTex(VERTEXDATA *InOut,LPSTR TeXCFileName, std::vector<VERTEX3D> *vtx, std::vector<WORD> *index);
//描画に必要な頂点データ作成しそのデータの構造体ポインタを返す
void CreateMesh(MESHDATA *InOut,LPSTR TeXCFileName);
//描画に必要なメッシュデータ作成しそのデータの構造体ポインタを返す
void CreateMFMMesh(MFMMESHDATA *InOut, LPSTR TeXCFileName);
//描画に必要なメッシュデータ作成しそのデータの構造体ポインタを返す
void CreateMeshField(VERTEXDATA *InOut,LPSTR TeXCFileName, int w, int h);
//描画に必要なメッシュデータ作成しそのデータの構造体ポインタを返す
void CreateMeshBoard(VERTEXDATA *InOut, LPSTR TeXCFileName);
//描画に必要なメッシュデータ作成しそのデータの構造体ポインタを返す
void CreateFramDataMesh(FRAMEDATA *InOut, LPSTR TeXCFileName);
//描画に必要なアニメーションの入ったメッシュを読み込む作成しそのデータの構造体ポインタを返す
void CreateMeshAnimationBoard(VERTEXDATA *InOut, LPSTR TeXCFileName);
int EditPath(TCHAR *OutPath, TCHAR *InPath, TCHAR *AddPath);
int CutPath(TCHAR *Out, TCHAR *In);



#endif//__CREATEDATA_H__


