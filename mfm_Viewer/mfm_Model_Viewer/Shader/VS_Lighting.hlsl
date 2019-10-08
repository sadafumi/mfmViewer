
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorld				: packoffset(c0);
	matrix		g_mView					: packoffset(c4);
	matrix		g_mProjection			: packoffset(c8);
};

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position	: POSITION;
	float4 Color		: COLOR0;
	float4 Normal		: NORMAL;
	float2 Texcoord	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Normal		: NORMAL;
	float2 Texcoord	: TEXCOORD0;
	float3 Posforps	: TEXCOORD2;
	float4 Position	: SV_POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorld);		// 頂点座標（ローカル座標系）をワールド座標系に変換	
	Output.Posforps = (float3)Output.Position;
	Output.Position = mul(Output.Position, g_mView);						// 頂点座標（ワールド座標系）をカメラ座標系に変換
	Output.Position = mul(Output.Position, g_mProjection);				// 頂点座標（カメラ座標系）をスクリーン座標系に変換

	Output.Texcoord = Input.Texcoord;

	//Output.Normal = Input.Normal;
	Output.Normal = mul(Input.Normal, g_mWorld);

	return Output;
}