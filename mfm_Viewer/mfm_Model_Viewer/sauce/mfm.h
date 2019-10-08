//-----------------------------------------------------------------------------
// AT12A242 宗貞史樹　2017/6/27 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// メインヘッダ			　　
//-----------------------------------------------------------------------------
#ifndef __MFM_H__
#define __MFM_H__
 
#include "Include.h"

struct Float3
{
	float x;
	float y;
	float z;
};

struct Float2
{
	float U;
	float V;
};

struct COLOR
{
	Float3 Ambient;
	Float3 Diffuse;
	Float3 Emissive;
	Float3 Specular;
	Float3 Bump;
	float  Transparency;
	float  Shininess;
	float  Reflectivity;
};

class Texture
{
public:
	void Set(TCHAR *in);
	TCHAR* Get();
private:
	TCHAR pTexName[MAX_PATH];
};

struct Material
{
	COLOR Color;
	Texture TexName;
};

class IntData
{
public:
	void SetNum(int in);
	int GetNum();
private:
	int Num;
};

class Float3pData
{
public:
	IntData Num;
	std::vector<Float3> Data;
};

class Float2pData
{
public:
	IntData Num;
	std::vector<Float2> Data;
};

class IntpData
{
public:
	IntData Num;
	std::vector<int> Data;
};

class Mesh
{
public:
	//データを出し入れするクラス群
	Float3pData Vertex;
	Float3pData Normals;
	Float2pData TexUV;
	IntpData Index;
	IntData MaterialIndex;
	IntData PrimitiveIndex;
private:
};

class Model
{
public:
	IntData					materialNum;	//マテリアル数
	IntData					MeshNum;		//メッシュ数
	std::vector<Mesh>		MeshData;		//メッシュの実データ
	std::vector<Material>	MaterialData;	//マテリアルの実データ
	//データをファイルから出し入れする関数
	void FileSaveData(TCHAR* Filename);
	void FileLoadData(TCHAR* Filename);
};


#endif //__MFM_H__
