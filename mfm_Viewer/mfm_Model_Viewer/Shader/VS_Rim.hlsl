
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
	float3 Normal   : TEXCOORD1;
	float3 Eye      : TEXCOORD2;
	float Power    : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorldViewProjection);		// 頂点座標（ローカル座標系）をワールド座標系に変換	

	Output.Texcoord = Input.Texcoord;

	float3 L = -m_LightDir.xyz;
	
	Output.Normal = normalize(Input.Normal.xyz);

	Output.Color = max(m_Ambient, dot(Output.Normal,L));

	Output.Eye = normalize(m_EyePos.xyz - Input.Position.xyz);

	Output.Power = max(0.0f,dot(Output.Eye, m_LightDir.xyz));
	
	return Output;
}