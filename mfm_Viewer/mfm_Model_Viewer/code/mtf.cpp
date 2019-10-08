#include "mtf.h"
#include <Windows.h>

namespace mtf
{
	void Texture::LoadTexture(std::string Path)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "rb")) == NULL)//ファイルが開けるか検証
		{
			MessageBox(NULL, "LOADファイルを開けませんでした","ロードエラー", MB_OK);
			return;//開けなかったら帰る
		}
		fread(&this->Height, sizeof(int), 1, fp);//高さを読み込み
		fread(&this->Width, sizeof(int), 1, fp);//幅を読み込み
		this->Data.resize(this->Height);//高さ分だけ一次元目の配列を広げる
		for(int i = 0; i <  this->Height; i++)
		{
			this->Data[i].resize(this->Width);//幅分だけ一次元目の配列を広げる
			for (int j = 0; j < this->Width; j++)
			{
				fread(&this->Data[i][j], sizeof(Color), 1, fp);//Color(Uchar4)を読み込む
			}
		}
		fclose(fp);//ファイルを閉じる

	}
	void Texture::SaveTexture(std::string Path)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "wb")) == NULL)//ファイルが開けるか検証
		{
			MessageBox(NULL, "SAVEファイルを開けませんでした", "ロードエラー", MB_OK);
			return;//開けなかったら帰る
		}
		fwrite(&this->Height, sizeof(int), 1, fp);//高さを書き込む
		fwrite(&this->Width, sizeof(int), 1, fp);//幅を書き込む
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				fwrite(&this->Data[i][j], sizeof(Color), 1, fp);//Color(Uchar4)を書き込む
			}
		}
		fclose(fp);//ファイルを閉じる
	}
}
