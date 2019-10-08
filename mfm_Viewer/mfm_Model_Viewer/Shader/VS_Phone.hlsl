
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};
float4	m_LightDir	: register(c4);
float4	m_EyePos	: register(c5);
float4	m_Ambient	: register(c6);

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
	float4 Color		: COLOR0;
	float2 Texcoord	: TEXCOORD0;
	float4 Position	: SV_POSITION;
	float3 N      : TEXCOORD1;
	float3 L      : TEXCOORD2;
	float3 E      : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorldViewProjection);		// 頂点座標（ローカル座標系）をワールド座標系に変換	

	Output.Texcoord = Input.Texcoord;

	Output.L = -normalize(m_LightDir.xyz);

	Output.N = Input.Normal.xyz;

	Output.E = m_EyePos.xyz - Output.Position.xyz;

	Output.Color = min(max(m_Ambient, dot(Output.N, Output.L)), 1.0f);
	
	return Output;
}