
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position	: POSITION;
	float4 Normal		: NORMAL;
	float2 Texcoord	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Position	: SV_POSITION;
	float2 Texcoord	: TEXCOORD0;
	float3 Normal   : TEXCOORD1;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorldViewProjection);		// 頂点座標（ローカル座標系）をワールド座標系に変換	

	Output.Texcoord = Input.Texcoord;
	
	Output.Normal = normalize(Input.Normal.xyz);
	
	return Output;
}