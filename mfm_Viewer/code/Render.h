#ifndef __RENDER_H__
#define __RENDER_H__

#include "DrawData.h"
#include "main.h"
#include "Light.h"
#include "Graphics.h"

#define COLORMASK  (00000011)
#define ALPHAMASK  (11111100)
#define ALLPASMASK (00000000)

class BaseShaderData 
{
public:
	void init();
	void SetVertexShader(DATA_TYPE::VERTEXSHADERDATA SetShader)
	{
		this->VertexShader = SetShader; 
	};
	void SetPixelShader(DATA_TYPE::PIXELSHADERDATA SetShader)
	{ 
		this->PixelShader = SetShader;
	};
	void SetLight(Lighter in) { this->Light = in; };		
	void SetMtXWorld(D3DXMATRIX World) { this->g_mtxWorld = World; };
	void SetMtXView(D3DXMATRIX View) { this->g_mtxView = View; };	
	void SetMtXWProj(D3DXMATRIX Proj) { this->g_mtxProj = Proj; };	
	D3DXMATRIX GetMtXWorld() { return this->g_mtxWorld; };	
	D3DXMATRIX GetMtXView() { return this->g_mtxView; };	
	D3DXMATRIX GetMtXWProj() { return this->g_mtxProj; };	
protected:
	DATA_TYPE::DECLARATIONDATA DeclarationData;
	DATA_TYPE::VERTEXSHADERDATA VertexShader;
	DATA_TYPE::PIXELSHADERDATA PixelShader;
	void SetDeviceMatrix();
	void SetDeviceShader();
	D3DXMATRIX g_mtxWorld;	
	D3DXMATRIX g_mtxView;	
	D3DXMATRIX g_mtxProj;	
	Lighter Light;
	const char* VPFilePath = "Shader\\VS_Default.hlsl";
	const char* PSFilePath = "Shader\\PS_Default.hlsl";
};
namespace Render 
{
	namespace Shader
	{
		class Line :public BaseShaderData 
		{
		public:
			void SetRendData(DATA_TYPE::VERTEX * VtxData, int);
			void Draw();
		private:
			const char* VS = "Shader\\VS_Line.hlsl";
			const char* PS = "Shader\\PS_Line.hlsl";
			int Max_Grid_Line = 0;
			DATA_TYPE::VERTEX *vtx;
			//VERTEXD* vtx;
		};
		class Surface:public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();							
		private:
			DATA_TYPE::VERTEXDATA* VerTexData;		
		};
		class SurfaceIndex : public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();							

		private:
			DATA_TYPE::VERTEXDATA * VerTexData;		
		};
		class Surface2D :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEX2DDATA *InData, int X, int Y);	
			void SetAnimationNum(int);
			void SetPositon(D3DXVECTOR2 in) { this->vcPositon = in; };
			void SetScale(D3DXVECTOR2 in) { this->vcScale = in; };
			void SetColor(D3DXVECTOR4 Color);
			void Draw();							
		private:
			int		   AniCount;	
			int		   AniCountX;
			int		   AniCountY;
			const char* Shader2D = "Shader\\VS_2D.hlsl";
			const char* ChangeColor = "Shader\\PS_ChangeColor.hlsl";
			D3DXVECTOR4 Color;
			D3DXVECTOR2 vcPositon;
			D3DXVECTOR2 vcScale;
			DATA_TYPE::VERTEX2DDATA *VerTexData;			
			D3DXMATRIX g_mtxPos;
			D3DXMATRIX g_mtxScale;
			D3DXMATRIX g_mtxRotation;
		};
		class SurfaceVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();							
		private:
			DATA_TYPE::VERTEXDATA * VerTexData;	
		};
		class SurfaceLambertVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);
			void Draw();							
		private:
			const char* VS = "Shader\\VS_Lambert.hlsl";
			const char* PS = "Shader\\PS_Lambert.hlsl";
			DATA_TYPE::VERTEXDATA * VerTexData;		
		};
		class SurfacePhoneVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();							
		private:
			const char* VS = "Shader\\VS_Phone.hlsl";
			const char* PS = "Shader\\PS_Phone.hlsl";
			DATA_TYPE::VERTEXDATA * VerTexData;		
		};
		class SurfaceRimVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);
			void Draw();
		private:
			const char* VS = "Shader\\VS_Rim.hlsl";
			const char* PS = "Shader\\PS_Rim.hlsl";
			DATA_TYPE::VERTEXDATA * VerTexData;
		};
		class SurfaceHalf_LambertVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);
			void Draw();
		private:
			const char* VS = "Shader\\VS_Half_Lambert.hlsl";
			const char* PS = "Shader\\PS_Half_Lambert.hlsl";
			DATA_TYPE::VERTEXDATA * VerTexData;
		};		
		class SurfaceBumpVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();							
		private:
			const char* VS = "Shader\\VS_Bump_Map.hlsl";
			const char* PS = "Shader\\PS_Bump_Map.hlsl";
			DATA_TYPE::VERTEXDATA * VerTexData;			
		};
		class SurfaceNoTextureVtxStrip :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);
			void SetColor(D3DXVECTOR4 Color);
			void Draw();
		private:
			const char* VS = "Shader\\VS_NoTexture.hlsl";
			const char* PS = "Shader\\PS_NoTexture.hlsl";
			DATA_TYPE::VERTEXDATA * VerTexData;
			D3DXVECTOR4 Color;
		};


		class BillBoardSurface :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);			
			void Draw();									
			void SetMtXScale(float x, float y, float z);	
			void SetMtXPos(float x, float y, float z);		
			void SetMtXRotation(float x, float y, float z);	
		private:
			DATA_TYPE::VERTEXDATA * VerTexData;			
			D3DXMATRIX g_mtxPos;			
			D3DXMATRIX g_mtxScale;			
			D3DXMATRIX g_mtxRotation;		
		};
		class BillAnimationSurface :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData, int aniIndex, int X, int Y);			
			void Draw();									
			void SetAnimationSpeed(float Speed);			
			void SetMtXScale(float x, float y, float z);	
			void SetMtXPos(float x, float y, float z);		
			void SetMtXRotation(float x, float y, float z);	
		private:
			DATA_TYPE::VERTEXDATA * VerTexData;			
			float      AniSpeed;		
			int		   AniCount;		
			int		   AniIndex;		
			int		   AniCountX;
			int		   AniCountY;
			D3DXMATRIX g_mtxPos;		
			D3DXMATRIX g_mtxScale;		
			D3DXMATRIX g_mtxRotation;	
		};
		class SurfaceUI :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();								
			void SetMoveScale(D3DXVECTOR3 scale) { this->ScalingSet = scale; };			
			void SetMovePos(D3DXVECTOR3 pos) { this->TranslationSet = pos; };			
			void Move(float MoveSpeed);						
			void SetMtXScale(D3DXVECTOR3 scale);			
			void SetMtXPos(D3DXVECTOR3 pos);				
			void SetMtXRotation(D3DXVECTOR3 rot) { D3DXMatrixRotationYawPitchRoll(&this->g_mtxRotation, rot.x, rot.y, rot.z); };
			void SetColor(D3DCOLOR InColor) { this->d3dColor = InColor; };			
		private:
			D3DXVECTOR3 ScalingPos;			
			D3DXVECTOR3 ScalingSet;			
			D3DXVECTOR3 TranslationPos;		
			D3DXVECTOR3 TranslationSet;		

			DATA_TYPE::VERTEXDATA *VerTexData;			
			D3DXMATRIX g_mtxPos;			
			D3DXMATRIX g_mtxScale;			
			D3DXMATRIX g_mtxRotation;		
			D3DCOLOR   d3dColor;			
		};
		class SurfaceSubsyn :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::VERTEXDATA *VtxData);	
			void Draw();							
		private:
			DATA_TYPE::VERTEXDATA * VerTexData;		

		};
		class Modelmfm :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::MFMMESHDATA *inData);	
			void Draw();							
		private:
			DATA_TYPE::MFMMESHDATA * pmfmData;		

			//const char* VS = "Shader\\VS_Half_Lambert.hlsl";
			//const char* PS = "Shader\\PS_Half_Lambert.hlsl";

			//const char* VS = "Shader\\VS_Rim.hlsl";
			//const char* PS = "Shader\\PS_Rim.hlsl";

			const char* VS = "Shader\\VS_Phone.hlsl";
			const char* PS = "Shader\\PS_Phone.hlsl";

			//const char* VS = "Shader\\VS_Lighting.hlsl";
			//const char* PS = "Shader\\PS_Lighting.hlsl";

			//const char* VS = "Shader\\VS_Lambert.hlsl";
			//const char* PS = "Shader\\PS_Lambert.hlsl";
		};
		class ModelToonmfm :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::MFMMESHDATA *inData);
			void Draw();
		private:
			DATA_TYPE::MFMMESHDATA * pmfmData;
			const char* PS = "Shader\\PS_Toon.hlsl";
		};
		class Model_mfm_Stencil_Shadow :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::MFMMESHDATA *inData);
			void Draw();							
		private:
			DATA_TYPE::MFMMESHDATA * pmfmData;			
		};
		class Animationmfm :public BaseShaderData
		{
		public:
			void SetRendData(DATA_TYPE::MFMANIMEDATA *inData);
			void SetAniSpe(float in) { this->AnimSpeed = in; };
			void Draw();
		private:
			DATA_TYPE::MFMANIMEDATA * pmfmData;
			float AnimSpeed;
			float NowAnimFrame;
		};

	}
}
#endif//_RENDER_H__

