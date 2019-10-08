
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};
float4	m_LightDir	: register(c4);
float4	m_Ambient	: register(c5);
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
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorldViewProjection);		// 頂点座標（ローカル座標系）をワールド座標系に変換	

	Output.Texcoord = Input.Texcoord;

	float3 L = -normalize(m_LightDir.xyz);

	float3 N = normalize(Input.Normal.xyz);

	Output.Color = max(m_Ambient, dot(N, L));

	return Output;
}