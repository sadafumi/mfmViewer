#include "Render.h"
#include "DrawData.h"
#include "Graphics.h"
#include "CreateData.h"
#include "Camera.h"

#define BoneMax (20)



void BaseShaderData::init()
{
	D3DXMatrixIdentity(&this->g_mtxWorld);					//ワールド行列を初期化
	D3DXVECTOR3 eye(0.0f, 0.0f, 1.0f);					//カメラ座標
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);					//注視点
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);					//カメラの向き
	D3DXMatrixLookAtLH(&this->g_mtxView, &eye, &at, &up);     //ビュー行列の初期化
	D3DXMatrixPerspectiveFovLH(&this->g_mtxProj,				//プロジェクション行列の初期化
		D3DXToRadian((120) / 2),
		(float)SCREEN_WIDTH / SCREEN_HIEGTH,
		0.1f,
		1000);
	Create::Declaration(&this->DeclarationData, FVF_VERTEX_3D);
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VPFilePath);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PSFilePath);
}
void BaseShaderData::SetDeviceMatrix()
{
	D3DXMATRIX matWorld;

	matWorld = this->g_mtxWorld * this->g_mtxView * this->g_mtxProj;
	D3DXMatrixTranspose(&matWorld, &matWorld);

	DeviceHider::SetVertexShaderFloat(0, &matWorld._11, 4);
}
void BaseShaderData::SetDeviceShader()
{
	DeviceHider::SetVertexShader(this->VertexShader);
	DeviceHider::SetPixelShader(this->PixelShader);
}
//=================================================================================================================================================================================================
//ここからシェーダープログラム
//=================================================================================================================================================================================================
void Render::Shader::Surface::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	this->VerTexData = VtxData;
	this->init();
}
void Render::Shader::Surface::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceMatrix();

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);

	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLELIST, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}
void Render::Shader::SurfaceIndex::SetRendData(DATA_TYPE::VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
void Render::Shader::SurfaceIndex::Draw()
{

	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceShader();
	
	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	
	//DeviceHider::SetRenderState(D3DRS_LIGHTING, TRUE);

	this->SetDeviceMatrix();

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);

	
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLELIST, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);

	//DeviceHider::SetRenderState(D3DRS_LIGHTING, FALSE);
}
void Render::Shader::Surface2D::SetRendData(DATA_TYPE::VERTEX2DDATA *InData, int X, int Y)
{
	VerTexData = InData;
	this->init();
	this->vcPositon = D3DXVECTOR2(0.0f, 0.0f);
	this->vcScale = D3DXVECTOR2(1.0f, 1.0f);
	this->AniCountX = X;
	this->AniCountY = Y;
	this->AniCount = 0;
	this->Color = D3DXVECTOR4(1, 1, 1, 1);
	D3DXMatrixIdentity(&this->g_mtxProj);
	this->g_mtxProj._11 = 2.0f / SCREEN_WIDTH;
	this->g_mtxProj._22 = 2.0f / SCREEN_HIEGTH;
	this->g_mtxProj._33 = 0;
	Create::Declaration(&this->DeclarationData, FVF_VERTEX_2D);
	Create::VertexShader(&this->VertexShader, (LPSTR)this->Shader2D );
	Create::PixelShader(&this->PixelShader,(LPSTR)this->ChangeColor);
}
void Render::Shader::Surface2D::SetAnimationNum(int in)
{
	this->AniCount = in;
}
void Render::Shader::Surface2D::SetColor(D3DXVECTOR4 In_Color)
{
	this->Color = In_Color;
}
void Render::Shader::Surface2D::Draw()
{
	D3DXVECTOR4 UVData;
	D3DXVECTOR4 Pos_Sca;

	if (this->AniCount < this->AniCountX * this->AniCountY)
	{
		this->AniCount = this->AniCount % (this->AniCountX * this->AniCountY);
	}
	int patternNUM = this->AniCount % (this->AniCountX * this->AniCountY);	//アニメーションのパターン数
	int patternH = (patternNUM % this->AniCountX);			//
	int patternV = (patternNUM / this->AniCountX);			//

	UVData.x = (float)this->AniCountX;
	UVData.y = (float)this->AniCountY;
	UVData.z = (float)patternH;
	UVData.w = (float)patternV;

	Pos_Sca.x = this->vcPositon.x;
	Pos_Sca.y = this->vcPositon.y;
	Pos_Sca.z = this->vcScale.x;
	Pos_Sca.w = this->vcScale.y;

	D3DXMATRIX mtxViewInv = this->g_mtxView;
	D3DXMatrixTranspose(&mtxViewInv, &mtxViewInv);
	mtxViewInv._14 = 0;
	mtxViewInv._24 = 0;
	mtxViewInv._34 = 0;

	//this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * mtxViewInv * this->g_mtxPos;
	
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceShader();

	this->SetDeviceMatrix();

	DeviceHider::SetVertexShaderFloat(4, &UVData.x, 1);
	DeviceHider::SetVertexShaderFloat(5, &Pos_Sca.x, 1);
	DeviceHider::SetVertexShaderFloat(6,&Color.x,1);

	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX2D));

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);

	DeviceHider::DrawPrimitive(D3DPT_TRIANGLEFAN, 2);
}
void Render::Shader::SurfaceVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}

void Render::Shader::SurfaceVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceShader();
	//インデックスセット&頂点セット
	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);

	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}
void Render::Shader::SurfaceBumpVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	VerTexData = VtxData;
	this->init();
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}
void Render::Shader::SurfaceBumpVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);
	this->SetDeviceShader();

	//インデックスセット&頂点セット
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();
	DeviceHider::SetVertexShaderFloat(4,&this->Light.CamePos.x,1);
	DeviceHider::SetVertexShaderFloat(5, &this->Light.Light.x, 1);

	//this->Light.SetPS(0);
	DeviceHider::SetPixelShaderFloat(0, &this->Light.Light.x, 1);
	DeviceHider::SetPixelShaderFloat(1, &this->Light.Ambient.x, 1);
	float Specular = 20.0f;
	DeviceHider::SetPixelShaderFloat(2, &Specular, 1);
	DeviceHider::SetPixelShaderFloat(3, &this->Light.Power, 1);

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);
	DeviceHider::SetTexture(1,this->VerTexData->pBump_Map);

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}
void Render::Shader::SurfaceLambertVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	VerTexData = VtxData;
	this->init();
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}
void Render::Shader::SurfaceLambertVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);
	this->SetDeviceShader();

	//インデックスセット&頂点セット
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();
	DeviceHider::SetVertexShaderFloat(4, &this->Light.Light.x, 1);
	DeviceHider::SetVertexShaderFloat(5, &this->Light.CamePos.x, 1);
	DeviceHider::SetVertexShaderFloat(6, &this->Light.Ambient_mat.x, 1);

	float Specular = 20.0f;
	DeviceHider::SetPixelShaderFloat(0, &Specular, 1);
	DeviceHider::SetPixelShaderFloat(1, &this->Light.Power, 1);

	DeviceHider::SetTexture(0, this->VerTexData->pTexture);
	//DeviceHider::SetTexture(1, this->VerTexData->pBump_Map);

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);	
}
void Render::Shader::SurfacePhoneVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	VerTexData = VtxData;
	this->init();
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}
void Render::Shader::SurfacePhoneVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);
	this->SetDeviceShader();

	//インデックスセット&頂点セット
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();
	DeviceHider::SetVertexShaderFloat(4, &this->Light.Light.x, 1);
	DeviceHider::SetVertexShaderFloat(5, &this->Light.CamePos.x, 1);
	DeviceHider::SetVertexShaderFloat(6, &this->Light.Ambient_mat.x, 1);

	DeviceHider::SetPixelShaderFloat(0, &this->Light.Specular_Power, 1);
	DeviceHider::SetPixelShaderFloat(1, &this->Light.Power, 1);

	DeviceHider::SetTexture(0, this->VerTexData->pTexture);
	//DeviceHider::SetTexture(1, this->VerTexData->pBump_Map);

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}
void Render::Shader::SurfaceRimVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	VerTexData = VtxData;
	this->init();
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}

void Render::Shader::SurfaceRimVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);
	this->SetDeviceShader();

	//インデックスセット&頂点セット
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();
	DeviceHider::SetVertexShaderFloat(4, &this->Light.Light.x, 1);
	DeviceHider::SetVertexShaderFloat(5, &this->Light.CamePos.x, 1);
	DeviceHider::SetVertexShaderFloat(6, &this->Light.Ambient_mat.x, 1);
	//float Specular = 20.0f;
	DeviceHider::SetPixelShaderFloat(0, &this->Light.Power, 1);

	DeviceHider::SetTexture(0, this->VerTexData->pTexture);
	//DeviceHider::SetTexture(1, this->VerTexData->pBump_Map);

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}
void Render::Shader::SurfaceHalf_LambertVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	VerTexData = VtxData;
	this->init();
	//Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}

void Render::Shader::SurfaceHalf_LambertVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);
	this->SetDeviceShader();

	//インデックスセット&頂点セット
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();

	//float Specular = 20.0f;
	DeviceHider::SetPixelShaderFloat(0, &this->Light.Light.x, 1);

	DeviceHider::SetTexture(0, this->VerTexData->pTexture);
	//DeviceHider::SetTexture(1, this->VerTexData->pBump_Map);

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}
void Render::Shader::SurfaceNoTextureVtxStrip::SetRendData(DATA_TYPE::VERTEXDATA * VtxData)
{
	VerTexData = VtxData;
	this->init();
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}

void Render::Shader::SurfaceNoTextureVtxStrip::SetColor(D3DXVECTOR4 in_Color)
{
	this->Color = in_Color;
}

void Render::Shader::SurfaceNoTextureVtxStrip::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);
	this->SetDeviceShader();

	//インデックスセット&頂点セット
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();

	DeviceHider::SetPixelShaderFloat(0, &this->Color.x, 1);
	//float Specular = 20.0f;

	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
}

void Render::Shader::BillBoardSurface::SetRendData(DATA_TYPE::VERTEXDATA *InData)
{
	VerTexData = InData;
	this->SetMtXPos(0, 0, 0);
	this->SetMtXRotation(0, 0, 0);
	this->SetMtXScale(1, 1, 1);
}
void Render::Shader::BillBoardSurface::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	//インデックスセット&頂点セット
	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆
	D3DXMATRIX mtxViewInv = this->g_mtxView;
	D3DXMatrixTranspose(&mtxViewInv, &mtxViewInv);
	mtxViewInv._14 = 0;
	mtxViewInv._24 = 0;
	mtxViewInv._34 = 0;

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * mtxViewInv * this->g_mtxPos;

	DeviceHider::SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DeviceHider::SetRenderState(D3DRS_ALPHAREF, 128);
	DeviceHider::SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ライティングオフ
	DeviceHider::SetRenderState(D3DRS_LIGHTING, FALSE);

	this->SetDeviceMatrix();

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);
	//DeviceHider->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize - 2);

	DeviceHider::SetRenderState(D3DRS_LIGHTING, TRUE);
	DeviceHider::SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
void Render::Shader::BillBoardSurface::SetMtXScale(float x, float y, float z)
{
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, x, y, z);//スケーリング（拡大縮小）行列を作成
	this->g_mtxScale = mtxScale;
}
void Render::Shader::BillBoardSurface::SetMtXPos(float x, float y, float z)
{
	D3DXMATRIX mtxWorldPos;
	D3DXMatrixTranslation(&mtxWorldPos, x, y, z);//平行移動行列を作成
	this->g_mtxPos = mtxWorldPos;
}
void Render::Shader::BillBoardSurface::SetMtXRotation(float x, float y, float z)
{
	D3DXMATRIX mtxWorldRotion;
	D3DXMatrixRotationYawPitchRoll(&mtxWorldRotion, x, y, z);//回転行列を作成
	this->g_mtxRotation = mtxWorldRotion;
}
void Render::Shader::BillAnimationSurface::SetRendData(DATA_TYPE::VERTEXDATA *VtxData, int aniIndex, int X, int Y)
{
	VerTexData = VtxData;
	this->init();
	this->AniIndex = aniIndex;
	this->AniCountX = X;
	this->AniCountY = Y;
	this->AniCount = 0;
	this->AniSpeed = 1;
	this->SetMtXPos(0, 0, 0);
	this->SetMtXRotation(0, 0, 0);
	this->SetMtXScale(1, 1, 1);
}
void Render::Shader::BillAnimationSurface::Draw()
{
	VERTEX3D *pVt;
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->AniCount;
	this->AniIndex;
	this->AniSpeed;
	this->AniCountX;
	this->AniCountY;
	this->VerTexData->TexSizeX;
	this->VerTexData->TexSizeY;
	int patternNUM = this->AniCount % (this->AniCountX * this->AniCountY);	//アニメーションのパターン数
	int patternH = (patternNUM % this->AniCountX);			//
	int patternV = (patternNUM / this->AniCountX);			//
	int nTexWid = (this->VerTexData->TexSizeX / this->AniCountX);	//
	int nTexHei = (this->VerTexData->TexSizeY / this->AniCountY);	//
	int tcx = patternH * nTexWid;		//
	int tcy = patternV * nTexHei;		//

	float AniTexu0 = (float)tcx / this->VerTexData->TexSizeX;
	float AniTexv0 = (float)tcy / this->VerTexData->TexSizeY;
	float AniTexu1 = ((float)tcx + (float)nTexWid) / this->VerTexData->TexSizeX;
	float AniTexv1 = ((float)tcy + (float)nTexHei) / this->VerTexData->TexSizeY;


	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	pVt[0].texcoord = { D3DXVECTOR2(AniTexu1, AniTexv1) };
	pVt[1].texcoord = { D3DXVECTOR2(AniTexu0, AniTexv1) };
	pVt[2].texcoord = { D3DXVECTOR2(AniTexu1, AniTexv0) };
	pVt[3].texcoord = { D3DXVECTOR2(AniTexu0, AniTexv0) };

	this->VerTexData->pVetTexBuffer->Unlock();

	//インデックスセット&頂点セット
	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));

	//こいつらを使いたくなければNULLをSETだぜ☆
	D3DXMATRIX mtxViewInv = this->g_mtxView;
	D3DXMatrixTranspose(&mtxViewInv, &mtxViewInv);
	mtxViewInv._14 = 0;
	mtxViewInv._24 = 0;
	mtxViewInv._34 = 0;

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * mtxViewInv * this->g_mtxPos;

	DeviceHider::SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DeviceHider::SetRenderState(D3DRS_ALPHAREF, 128);
	DeviceHider::SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DeviceHider::SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	DeviceHider::SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//ライティングオフ
	DeviceHider::SetRenderState(D3DRS_LIGHTING, FALSE);

	this->SetDeviceMatrix();

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);
	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);
	//DeviceHider->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->VerTexData->vtXsize, 0, this->VerTexData->IndeXsize);

	DeviceHider::SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	DeviceHider::SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DeviceHider::SetRenderState(D3DRS_LIGHTING, TRUE);
	DeviceHider::SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	this->AniCount += (int)this->AniSpeed;
}
void Render::Shader::BillAnimationSurface::SetAnimationSpeed(float Speed)			//アニメーションスピード
{
	this->AniSpeed = Speed;
}
void Render::Shader::BillAnimationSurface::SetMtXScale(float x, float y, float z)
{
	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, x, y, z);//スケーリング（拡大縮小）行列を作成
	this->g_mtxScale = mtxScale;
}
void Render::Shader::BillAnimationSurface::SetMtXPos(float x, float y, float z)
{
	D3DXMATRIX mtxWorldPos;
	D3DXMatrixTranslation(&mtxWorldPos, x, y, z);//平行移動行列を作成
	this->g_mtxPos = mtxWorldPos;
}
void Render::Shader::BillAnimationSurface::SetMtXRotation(float x, float y, float z)
{
	D3DXMATRIX mtxWorldRotion;
	D3DXMatrixRotationYawPitchRoll(&mtxWorldRotion, x, y, z);//回転行列を作成
	this->g_mtxRotation = mtxWorldRotion;
}
void Render::Shader::SurfaceUI::SetRendData(DATA_TYPE::VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();

	this->TranslationPos = D3DXVECTOR3(0, 0, 0);
	this->TranslationSet = D3DXVECTOR3(0, 0, 0);
	this->ScalingPos = D3DXVECTOR3(1, 1, 1);
	this->ScalingSet = D3DXVECTOR3(1, 1, 1);

	this->SetMtXPos(this->TranslationPos);
	this->SetMtXScale(this->ScalingPos);
	this->SetMtXRotation(D3DXVECTOR3(0, 0, 0));
	this->d3dColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}
void Render::Shader::SurfaceUI::Draw()
{
	VERTEX3D *pVt;
	D3DCOLOR ColorStocker;

	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	//インデックスセット&頂点セット
	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);

	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	ColorStocker = pVt[0].color;
	pVt[0].color = pVt[1].color = pVt[2].color = pVt[3].color = this->d3dColor;

	this->VerTexData->pVetTexBuffer->Unlock();

	//頂点データ
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->g_mtxWorld = this->g_mtxScale * this->g_mtxRotation * this->g_mtxPos;

	DeviceHider::SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DeviceHider::SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	DeviceHider::SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//ライティングオフ
	DeviceHider::SetRenderState(D3DRS_LIGHTING, FALSE);

	this->SetDeviceMatrix();

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);

	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize - 2);

	this->VerTexData->pVetTexBuffer->Lock(0, 0, (void**)&pVt, D3DLOCK_DISCARD);

	pVt[0].color = pVt[1].color = pVt[2].color = pVt[3].color = ColorStocker;

	this->VerTexData->pVetTexBuffer->Unlock();

	DeviceHider::SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	DeviceHider::SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DeviceHider::SetRenderState(D3DRS_LIGHTING, TRUE);
	//DeviceHider->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	this->d3dColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}
void Render::Shader::SurfaceUI::Move(float MoveSpeed)
{
	// セットした位置情報と現在の位置情報の差分をスピードで掛け算(1.0f = 100%)
	this->TranslationPos += (this->TranslationSet - this->TranslationPos) * MoveSpeed;
	this->ScalingPos += (this->ScalingSet - this->ScalingPos) * MoveSpeed;
	// 計算した情報をセット
	this->SetMtXPos(this->TranslationPos);
	this->SetMtXScale(this->ScalingPos);
}
void Render::Shader::SurfaceUI::SetMtXScale(D3DXVECTOR3 scale)
{
	this->ScalingPos = scale;
	this->ScalingSet = scale;
	D3DXMatrixScaling(&this->g_mtxScale, scale.x, scale.y, scale.z);//スケーリング（拡大縮小）行列を作成
}
void Render::Shader::SurfaceUI::SetMtXPos(D3DXVECTOR3 pos)
{
	this->TranslationPos = pos;
	this->TranslationSet = pos;
	D3DXMatrixTranslation(&this->g_mtxPos, pos.x, pos.y, pos.z);//平行移動行列を作成
}
void Render::Shader::SurfaceSubsyn::SetRendData(DATA_TYPE::VERTEXDATA *InData)
{
	VerTexData = InData;
	this->init();
}
void Render::Shader::SurfaceSubsyn::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	//インデックスセット&頂点セット
	DeviceHider::SetIndices(this->VerTexData->pIndexBuffer);
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆
	//ここからαテスト
	DeviceHider::SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DeviceHider::SetRenderState(D3DRS_ALPHAREF, 125);
	DeviceHider::SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//ここから減算合成
	DeviceHider::SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	DeviceHider::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DeviceHider::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	//ライティングオフ
	DeviceHider::SetRenderState(D3DRS_LIGHTING, TRUE);

	this->SetDeviceMatrix();

	DeviceHider::SetTexture(0,this->VerTexData->pTexture);

	DeviceHider::DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, this->VerTexData->vtXsize, this->VerTexData->IndeXsize);

	//ここまで減算合成
	DeviceHider::SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DeviceHider::SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DeviceHider::SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//ここまでαテスト
	DeviceHider::SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
void Render::Shader::Modelmfm::SetRendData(DATA_TYPE::MFMMESHDATA *inData)	//データをセット＆初期化
{
	this->pmfmData = inData;
	this->init();
	//Create::VertexShader(&this->VertexShader, (LPSTR)this->VS);
	//Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
	//this->Color = D3DXVECTOR4(0.0f, 0.0f, 0.0f,0.0f);
}
void Render::Shader::Modelmfm::UpdateModel(DATA_TYPE::MFMMESHDATA* inData)
{
	this->pmfmData = inData;
}
void Render::Shader::Modelmfm::SetColor(D3DXVECTOR4 in_Color)
{
	this->Color = in_Color;
}
void Render::Shader::Modelmfm::Draw()							//描画
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceShader();

	this->SetDeviceMatrix();

	//DeviceHider::SetVertexShaderFloat(4, &this->Light.Light.x, 1);
	//DeviceHider::SetVertexShaderFloat(5, &this->Light.CamePos.x, 1);
	//DeviceHider::SetVertexShaderFloat(6, &this->Light.Ambient_mat.x, 1);

	//DeviceHider::SetPixelShaderFloat(0, &this->Light.Specular_Power, 1);
	//DeviceHider::SetPixelShaderFloat(1, &this->Light.Power, 1);
	//DeviceHider::SetPixelShaderFloat(2, &this->Color.x, 1);


	if (this->pmfmData != NULL)
	{
		for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
		{
			DeviceHider::SetStreamSource(this->pmfmData->VertexBuffer[i], sizeof(VERTEX3D));

			// テクスチャテーブルにセット
			if (this->pmfmData->MeshData[i].TexName == "")
			{

			}
			else
			{
				DeviceHider::SetTexture(0,this->pmfmData->Texture[i]);
			}

			// マテリアルをデバイスにセット
			//DeviceHider::SetMaterial(&this->pmfmData->Material[this->pmfmData->MeshData[i].MaterialIndex]);

			//DeviceHider::DrawPrimitive(D3DPT_POINTLIST, this->pmfmData->MeshData[i].PrimitiveNum);
			DeviceHider::DrawPrimitive(D3DPT_TRIANGLELIST, this->pmfmData->MeshData[i].PrimitiveNum);
		}
	}
}

void Render::Shader::ModelToonmfm::SetRendData(DATA_TYPE::MFMMESHDATA * inData)
{
	this->pmfmData = inData;
	this->init();
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS);
}

void Render::Shader::ModelToonmfm::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceShader();

	//D3DXMatrixTranspose(&this->g_mtxWorld, &this->g_mtxWorld);
	//D3DXMatrixTranspose(&this->g_mtxView, &this->g_mtxView);
	//DeviceHider::SetVertexShaderFloat(0, &this->g_mtxWorld._11, 4);
	//DeviceHider::SetVertexShaderFloat(4, &this->g_mtxView._11, 4);
	//DeviceHider::SetVertexShaderFloat(8, &this->g_mtxProj._11, 4);

	//this->Light.SetPS(0);
	this->SetDeviceMatrix();

	DeviceHider::SetPixelShaderFloat(0, &this->Light.Light.x, 1);
	//DeviceHider::SetVertexShaderFloat(4, &this->Light.Light.x, 1);
	//DeviceHider::SetVertexShaderFloat(5, &this->Light.CamePos.x, 1);
	//DeviceHider::SetVertexShaderFloat(6, &this->Light.Ambient_mat.x, 1);

	//float Specular = 20.0f;
	DeviceHider::SetPixelShaderFloat(0, &this->Light.Power, 1);

	if (this->pmfmData != NULL)
	{
		for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
		{
			DeviceHider::SetStreamSource(this->pmfmData->VertexBuffer[i], sizeof(VERTEX3D));
			if (this->pmfmData->MeshData[i].TexName == "")
			{

			}
			else
			{
				DeviceHider::SetTexture(0, this->pmfmData->Texture[i]);
			}
			DeviceHider::DrawPrimitive(D3DPT_TRIANGLELIST, this->pmfmData->MeshData[i].PrimitiveNum);
		}
	}
}

void Render::Shader::Model_mfm_Stencil_Shadow::SetRendData(DATA_TYPE::MFMMESHDATA * inData)
{
	this->pmfmData = inData;
	this->init();
}
void Render::Shader::Model_mfm_Stencil_Shadow::Draw()
{
	//DeviceHider::SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
//SetRenderState(D3DRS_COLORWRITEENABLE, 0);//←カラー無効
// D3DDeviceの取得

	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	//DeviceHider::SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1, 1, 1, 1));

	this->SetDeviceShader();
	this->SetDeviceMatrix();

	DeviceHider::SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	DeviceHider::SetRenderState(D3DRS_STENCILENABLE, TRUE);//←ステンシルを有効に
	DeviceHider::SetRenderState(D3DRS_COLORWRITEENABLE, 0);//←カラー無効
	DeviceHider::SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	DeviceHider::SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	DeviceHider::SetRenderState(D3DRS_STENCILREF, 1);
	DeviceHider::SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//表面


	if (this->pmfmData != NULL)
	{
		for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
		{
			DeviceHider::SetStreamSource(this->pmfmData->VertexBuffer[i], sizeof(VERTEX3D));

			// テクスチャテーブルにセット
			if (this->pmfmData->MeshData[i].TexName == "")
			{

			}
			else
			{
				DeviceHider::SetTexture(0, this->pmfmData->Texture[i]);
			}

			// マテリアルをデバイスにセット
			//DeviceHider::SetMaterial(&this->pmfmData->Material[this->pmfmData->MeshData[i].MaterialIndex]);

			//DeviceHider::DrawPrimitive(D3DPT_POINTLIST, this->pmfmData->MeshData[i].PrimitiveNum);
			DeviceHider::DrawPrimitive(D3DPT_TRIANGLELIST, this->pmfmData->MeshData[i].PrimitiveNum);
		}
	}

	DeviceHider::SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_DECR);
	DeviceHider::SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);//表面

	if (this->pmfmData != NULL)
	{
		for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
		{
			DeviceHider::SetStreamSource(this->pmfmData->VertexBuffer[i], sizeof(VERTEX3D));

			// テクスチャテーブルにセット
			if (this->pmfmData->MeshData[i].TexName == "")
			{

			}
			else
			{
				DeviceHider::SetTexture(0, this->pmfmData->Texture[i]);
			}

			// マテリアルをデバイスにセット
			//DeviceHider::SetMaterial(&this->pmfmData->Material[this->pmfmData->MeshData[i].MaterialIndex]);

			//DeviceHider::DrawPrimitive(D3DPT_POINTLIST, this->pmfmData->MeshData[i].PrimitiveNum);
			DeviceHider::DrawPrimitive(D3DPT_TRIANGLELIST, this->pmfmData->MeshData[i].PrimitiveNum);
		}
	}

	DeviceHider::SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//表面
	DeviceHider::SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);//←カラー有効に
	DeviceHider::SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	if (this->pmfmData != NULL)
	{
		for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
		{
			DeviceHider::SetStreamSource(this->pmfmData->VertexBuffer[i], sizeof(VERTEX3D));

			// テクスチャテーブルにセット
			if (this->pmfmData->MeshData[i].TexName == "")
			{

			}
			else
			{
				DeviceHider::SetTexture(0, this->pmfmData->Texture[i]);
			}

			// マテリアルをデバイスにセット
			//DeviceHider::SetMaterial(&this->pmfmData->Material[this->pmfmData->MeshData[i].MaterialIndex]);

			//DeviceHider::DrawPrimitive(D3DPT_POINTLIST, this->pmfmData->MeshData[i].PrimitiveNum);
			DeviceHider::DrawPrimitive(D3DPT_TRIANGLELIST, this->pmfmData->MeshData[i].PrimitiveNum);
		}
	}
	DeviceHider::SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DeviceHider::SetRenderState(D3DRS_STENCILENABLE, FALSE);//←ステンシルを無効に


}
void Render::Shader::Animationmfm::SetRendData(DATA_TYPE::MFMANIMEDATA *inData)
{ 
	this->pmfmData = inData; 
	this->init();
	this->NowAnimFrame = 2;
	this->AnimSpeed = 1.0f;

	Create::Declaration(&this->DeclarationData, FVF_VERTEX_ANIME);
}
void Render::Shader::Animationmfm::Draw()
{
	//テクニックを設定
	this->NowAnimFrame += this->AnimSpeed;
	if (this->pmfmData->nAnimFrame <= this->NowAnimFrame)
	{
		this->NowAnimFrame = 0;
	}

	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	D3DXMATRIX **BoneMat;
	BoneMat = new D3DXMATRIX*[this->pmfmData->VertexBuffer.size()];
	for (int y = 0; y < (int)this->pmfmData->VertexBuffer.size(); y++)
	{

		BoneMat[y] = new D3DXMATRIX[this->pmfmData->bone[y].size()];
		for (int x = 0; x < (int)this->pmfmData->bone[y].size(); x++)
		{
			BoneMat[y][x] = this->pmfmData->bone[y][x].MatAry[(int)this->NowAnimFrame];
		}
	}

	DeviceHider::SetRenderState(D3DRS_CULLMODE, false);
	//テクニックを開始

	this->SetDeviceShader();

	this->SetDeviceMatrix();

	for (DWORD i = 0; i < this->pmfmData->VertexBuffer.size(); i++)
	{
		//this->pEffect->SetVector("LightPos", &this->light.GetPos());
		//this->pEffect->SetFloat("LightBrightness", this->light.GetBrightness());
		DeviceHider::SetVertexShaderFloat(4, &this->Light.Diffuse.x,1);
		DeviceHider::SetVertexShaderFloat(8, &BoneMat[i]->_11, (UINT)this->pmfmData->bone[i].size() * 4);
		DeviceHider::SetTexture(0,this->pmfmData->Texture[i]);
		DeviceHider::SetStreamSource(this->pmfmData->VertexBuffer[i], sizeof(VERTEXANI));
		DeviceHider::DrawPrimitive(D3DPT_TRIANGLELIST, this->pmfmData->MeshData[i].PrimitiveNum);
	}



	for (int i = 0; i < (int)this->pmfmData->VertexBuffer.size(); i++)
	{
		delete[] BoneMat[i];
	}
	delete[] BoneMat;

	//DebugText(10, 45, "現在のフレーム(%f)", this->NowAnimFrame);
}
//=================================================================================================================================================================================================
//ここからシェーダープログラム
//=================================================================================================================================================================================================

void Render::Shader::VtxStripLine::SetRendData(DATA_TYPE::VERTEXDATA* VtxData)
{
	VerTexData = VtxData;
	this->init();
	Create::VertexShader(&this->VertexShader, (LPSTR)this->VS_NOTex);
	Create::PixelShader(&this->PixelShader, (LPSTR)this->PS_NOTex);

}

void Render::Shader::VtxStripLine::SetColor(D3DXVECTOR4 in_color)
{
	this->Color = in_color;
}

void Render::Shader::VtxStripLine::Draw()
{
	DeviceHider::SetVertexDeclaration(this->DeclarationData.pDeclaration);

	this->SetDeviceShader();
	//インデックスセット&頂点セット
	DeviceHider::SetStreamSource(this->VerTexData->pVetTexBuffer, sizeof(VERTEX3D));
	//こいつらを使いたくなければNULLをSETだぜ☆

	this->SetDeviceMatrix();

	DeviceHider::SetPixelShaderFloat(0, &this->Color.x,4);

	DeviceHider::DrawPrimitive(D3DPT_LINELIST, this->VerTexData->vtXsize);
}
