

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

// 光
// マテリアル
float	m_Power : register(c0);
// スペキュラ光の計算用	

sampler2D g_Texture : register(s0);

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float4 Color	: COLOR0;
	float2 Texcoord	: TEXCOORD0;
	float3 Normal   : TEXCOORD1;
	float3 Eye      : TEXCOORD2;
	float Power : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT Input) : SV_TARGET
{
	float4 out_Color;

	float P = 1.0f - max(0.0f,dot(Input.Normal, Input.Eye));
	P = P * m_Power;
	P = P * P;

	out_Color = Input.Color * tex2D(g_Texture, Input.Texcoord) + Input.Power * P;

	return out_Color;
}
