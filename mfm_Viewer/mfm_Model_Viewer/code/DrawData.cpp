#include "DrawData.h"



void DATA_TYPE::VERTEX2DDATA::Destroy()
{
	if (this->pVetTexBuffer != NULL)
	{
		this->pVetTexBuffer->Release();
	}
}

void DATA_TYPE::VERTEXDATA::Destroy()
{
	if (this->pVetTexBuffer != NULL)
	{
		this->pVetTexBuffer->Release();
	}
	if (this->pIndexBuffer != NULL)
	{
		this->pIndexBuffer->Release();
	}
}

void DATA_TYPE::MFMMESHDATA::Destroy()
{
	for (int i = 0; i < (int)this->VertexBuffer.size(); i++)
	{
		if (this->VertexBuffer[i] != NULL)
		{
			this->VertexBuffer[i]->Release();
		}
	}
}

void DATA_TYPE::MFMANIMEDATA::Destroy()
{
	for (int i = 0; i < (int)this->VertexBuffer.size(); i++)
	{
		if (this->VertexBuffer[i] != NULL)
		{
			this->VertexBuffer[i]->Release();
		}
	}
}

void DATA_TYPE::RENDERTARGETTEXTUREDATA::Destroy()
{
	this->Surface.Destroy();
	this->Texture.Destroy();
}

void DATA_TYPE::TEXTUREDATA::Destroy()
{
	if (this->pTexture != NULL)
	{
		this->pTexture->Release();
	}
}

void DATA_TYPE::SURFACEDATA::Destroy()
{
	if (this->Surface != NULL)
	{
		this->Surface->Release();
	}
}
