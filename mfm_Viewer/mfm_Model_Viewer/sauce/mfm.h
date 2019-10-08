//-----------------------------------------------------------------------------
// AT12A242 �@��j���@2017/6/27 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ���C���w�b�_			�@�@
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
	//�f�[�^���o�����ꂷ��N���X�Q
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
	IntData					materialNum;	//�}�e���A����
	IntData					MeshNum;		//���b�V����
	std::vector<Mesh>		MeshData;		//���b�V���̎��f�[�^
	std::vector<Material>	MaterialData;	//�}�e���A���̎��f�[�^
	//�f�[�^���t�@�C������o�����ꂷ��֐�
	void FileSaveData(TCHAR* Filename);
	void FileLoadData(TCHAR* Filename);
};


#endif //__MFM_H__
