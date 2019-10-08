#pragma once
#ifndef __CREATEDATA_H__
#define __CREATEDATA_H__

#include "DrawData.h"
#include "Graphics.h"
#include <map>

struct TextureBuffer
{
	LPDIRECT3DTEXTURE9 Texture;
};
struct VertexShaderBuffer
{
	IDirect3DVertexShader9* VertexShader;
};
struct PixelShaderBuffer
{
	IDirect3DPixelShader9* PixelShader;
};
struct DeclarationBuffer
{
	LPDIRECT3DVERTEXDECLARATION9 Declaration = NULL;
};

class Create 
{
public:
	static void Render_Target_Texture(DATA_TYPE::RENDERTARGETTEXTUREDATA *InOut,int x,int y);
	static void Texture(DATA_TYPE::TEXTUREDATA *InOut, const char* TeXCFileName);
	static void VerTex2D_NotTex(DATA_TYPE::VERTEX2DDATA *InOut,int w,int h);
	static void VerTex2D(DATA_TYPE::VERTEX2DDATA *InOut, const char* TeXCFileName);
	static void VerTex_Line(DATA_TYPE::VERTEX *InOut, std::vector <VERTEXD> *vtx);
	static void VerTex(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, std::vector<VERTEX3D> *vtx, std::vector<WORD> *index);
	static void MFMMesh(DATA_TYPE::MFMMESHDATA *InOut, const char* TeXCFileName);
	static void MFMAnime(DATA_TYPE::MFMANIMEDATA *InOut, const char* TeXCFileName);
	static void MeshField(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, int w, int h,float Wsize, float Hsize, std::vector<std::vector<float>>);
	static void MeshFlatField(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, int w, int h, float Wsize, float Hsize);
	static void MeshNoField(DATA_TYPE::VERTEXDATA *InOut, int w, int h, float Wsize, float Hsize);
	static void MeshBoard(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, int w, int h, float Wsize, float Hsize, D3DXVECTOR2 Pos);
	static void MeshOneTex(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, int w, int h, float Wsize, float Hsize);
	static void MeshBoard(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName);
	static void MeshBoardBump(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName, const char* BumpFileName,int size);
	static void MeshAnimationBoard(DATA_TYPE::VERTEXDATA *InOut, const char* TeXCFileName);
	static bool VertexShader(DATA_TYPE::VERTEXSHADERDATA *Out, const char* TeXCFileName);
	static bool PixelShader(DATA_TYPE::PIXELSHADERDATA *Out, const char* TeXCFileName);
	static void Declaration(DATA_TYPE::DECLARATIONDATA *out, DWORD fvf);
	static TEXUV UVCode(const char* infileName, int AniNum, int nTexWidth, int nTexHiegth);
	static void Destroy();
private:
	static D3DXIMAGE_INFO LoadTextureInfo(const char* lpFlieName);
	static LPDIRECT3DTEXTURE9 CheckTexture(const char* TeXCFileName);
	static std::map<std::string, TextureBuffer>	     TextureStock;
	static std::map<std::string, VertexShaderBuffer> VertexShaderStock;
	static std::map<std::string, PixelShaderBuffer>  PixelShaderStock;
	static std::map<DWORD ,DeclarationBuffer>        DeclarationStock;
};

int EditPath(TCHAR *OutPath, TCHAR *InPath, TCHAR *AddPath);
int CutPath(TCHAR *Out, TCHAR *In);



#endif//__CREATEDATA_H__


