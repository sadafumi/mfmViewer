#include "mfm.h"


void IntData::SetNum(int in)
{
	this->Num = in;
}
int IntData::GetNum()
{
	return this->Num;
}
void Texture::Set(TCHAR *in)
{
	strcpy(this->pTexName, in);
}
TCHAR* Texture::Get()
{
	if(this->pTexName == NULL)
	{
		return nullptr;
	}
	return this->pTexName;
}

//データをファイルと出しれする関数
void Model::FileSaveData(TCHAR* Filename)
{
	FILE *fp = NULL;
	
	if((fp = fopen(Filename, "wb")) == NULL)
	{
		printf("ファイル(%s)が開けませんでした", Filename);
		return;
	}
	int nBuff = NULL;
	Float3 fBuff;
	Float2 f2Buff;
	
	//Mesh数を渡す
	nBuff = this->MeshNum.GetNum();
	fwrite(&nBuff,sizeof(int),1,fp);
	
	for (size_t i = 0; i < (size_t)this->MeshNum.GetNum(); i++)
	{
		
		nBuff = this->MeshData[i].MaterialIndex.GetNum();
		fwrite(&nBuff, sizeof(int), 1, fp);
		nBuff = this->MeshData[i].PrimitiveIndex.GetNum();
		fwrite(&nBuff, sizeof(int), 1, fp);
		nBuff = this->MeshData[i].Vertex.Num.GetNum();
		fwrite(&nBuff, sizeof(int), 1, fp);
		for (size_t j = 0; j < (size_t)this->MeshData[i].Vertex.Num.GetNum(); j++)
		{
			fBuff = this->MeshData[i].Vertex.Data[j];
			fwrite(&fBuff, sizeof(Float3), 1, fp);
		}

		nBuff = this->MeshData[i].Index.Num.GetNum();
		fwrite(&nBuff, sizeof(int), 1, fp);
		for (size_t j = 0; j < (size_t)this->MeshData[i].Index.Num.GetNum(); j++)
		{
			nBuff = this->MeshData[i].Index.Data[j];
			fwrite(&nBuff, sizeof(int), 1, fp);
		}

		nBuff = this->MeshData[i].Normals.Num.GetNum();
		fwrite(&nBuff, sizeof(int), 1, fp);
		for (size_t j = 0; j < (size_t)this->MeshData[i].Normals.Num.GetNum(); j++)
		{
			fBuff = this->MeshData[i].Normals.Data[j];
			fwrite(&fBuff, sizeof(Float3), 1, fp);
		}

		nBuff = this->MeshData[i].TexUV.Num.GetNum();
		fwrite(&nBuff, sizeof(int), 1, fp);
		for (size_t j = 0; j < (size_t)this->MeshData[i].TexUV.Num.GetNum(); j++)
		{
			f2Buff = this->MeshData[i].TexUV.Data[j];
			fwrite(&f2Buff, sizeof(Float2), 1, fp);
		}
	}
	nBuff = this->materialNum.GetNum();
	fwrite(&nBuff, sizeof(int), 1, fp);
	for (size_t i = 0; i < (size_t)this->materialNum.GetNum(); i++)
	{
		fwrite(&this->MaterialData[i].Color.Ambient,sizeof(Float3),1,fp);
		fwrite(&this->MaterialData[i].Color.Bump, sizeof(Float3), 1, fp);
		fwrite(&this->MaterialData[i].Color.Diffuse, sizeof(Float3), 1, fp);
		fwrite(&this->MaterialData[i].Color.Emissive, sizeof(Float3), 1, fp);
		fwrite(&this->MaterialData[i].Color.Reflectivity, sizeof(float), 1, fp);
		fwrite(&this->MaterialData[i].Color.Specular, sizeof(Float3), 1, fp);
		fwrite(&this->MaterialData[i].Color.Shininess, sizeof(float), 1, fp);
		fwrite(&this->MaterialData[i].Color.Transparency, sizeof(float), 1, fp);
		fwrite(this->MaterialData[i].TexName.Get(), sizeof(TCHAR), MAX_PATH, fp);
	}

	fclose(fp);
}
void Model::FileLoadData(TCHAR* Filename)
{
	FILE *fp = NULL;

	if ((fp = fopen(Filename, "rb")) == NULL)
	{
		printf("ファイルが開けませんでした");
		return;
	}
	int nBuff;
	//Mesh数を受け取る
	fread(&nBuff, sizeof(int), 1, fp);
	this->MeshNum.SetNum(nBuff);
	this->MeshData.resize(this->MeshNum.GetNum());
	for (size_t i = 0; i < (size_t)this->MeshNum.GetNum(); i++)
	{		
		
		fread(&nBuff, sizeof(int), 1, fp);
		this->MeshData[i].MaterialIndex.SetNum(nBuff);
		fread(&nBuff, sizeof(int), 1, fp);
		this->MeshData[i].PrimitiveIndex.SetNum(nBuff);
		fread(&nBuff, sizeof(int), 1, fp);
		this->MeshData[i].Vertex.Num.SetNum(nBuff);
		this->MeshData[i].Vertex.Data.resize(this->MeshData[i].Vertex.Num.GetNum());
		for (size_t j = 0; j < (size_t)this->MeshData[i].Vertex.Num.GetNum(); j++)
		{
			fread(&this->MeshData[i].Vertex.Data[j], sizeof(Float3), 1, fp);
			
		}
		
		fread(&nBuff, sizeof(int), 1, fp);
		this->MeshData[i].Index.Num.SetNum(nBuff);
		this->MeshData[i].Index.Data.resize(this->MeshData[i].Index.Num.GetNum());
		for (size_t j = 0; j < (size_t)this->MeshData[i].Index.Num.GetNum(); j++)
		{
			fread(&this->MeshData[i].Index.Data[j], sizeof(int), 1, fp);
		}

		fread(&nBuff, sizeof(int), 1, fp);
		this->MeshData[i].Normals.Num.SetNum(nBuff);
		this->MeshData[i].Normals.Data.resize(this->MeshData[i].Normals.Num.GetNum());
		for (size_t j = 0; j < (size_t)this->MeshData[i].Normals.Num.GetNum(); j++)
		{
			fread(&this->MeshData[i].Normals.Data[j], sizeof(Float3), 1, fp);
		}
		
		fread(&nBuff, sizeof(int), 1, fp);
		this->MeshData[i].TexUV.Num.SetNum(nBuff);
		this->MeshData[i].TexUV.Data.resize(this->MeshData[i].TexUV.Num.GetNum());
		for (size_t j = 0; j < (size_t)this->MeshData[i].TexUV.Num.GetNum(); j++)
		{
			fread(&this->MeshData[i].TexUV.Data[j], sizeof(Float2), 1, fp);
		}
	}

	fread(&nBuff, sizeof(int), 1, fp);
	this->materialNum.SetNum(nBuff);
	this->MaterialData.resize(this->materialNum.GetNum());
	for (size_t i = 0; i < (size_t)this->materialNum.GetNum(); i++)
	{
		fread(&this->MaterialData[i].Color.Ambient, sizeof(Float3), 1, fp);
		fread(&this->MaterialData[i].Color.Bump, sizeof(Float3), 1, fp);
		fread(&this->MaterialData[i].Color.Diffuse, sizeof(Float3), 1, fp);
		fread(&this->MaterialData[i].Color.Emissive, sizeof(Float3), 1, fp);
		fread(&this->MaterialData[i].Color.Specular, sizeof(Float3), 1, fp);
		fread(&this->MaterialData[i].Color.Reflectivity, sizeof(float), 1, fp);
		fread(&this->MaterialData[i].Color.Shininess, sizeof(float), 1, fp);
		fread(&this->MaterialData[i].Color.Transparency, sizeof(float), 1, fp);
		TCHAR sBuff[MAX_PATH];
		fread(&sBuff, sizeof(TCHAR), MAX_PATH, fp);
		this->MaterialData[i].TexName.Set(sBuff);
		printf("%s\n",sBuff);
	}

	fclose(fp);
}
