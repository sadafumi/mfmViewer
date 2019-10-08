
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

// 光
// マテリアル
float	m_Specular : register(c0);
float	m_SpecularPower : register(c1);
float	color : register(c2);

// スペキュラ光の計算用	

sampler2D g_Texture : register(s0);

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float4 Color	: COLOR0;
	float2 Texcoord	: TEXCOORD0;
	float3 N      : TEXCOORD1;
	float3 L      : TEXCOORD2;
	float3 E      : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT Input) : SV_TARGET
{
	float4 out_Color;

	float3 N = normalize(Input.N);
	float3 H = normalize(Input.L + normalize(Input.E));
	float S = pow(max(0.0f, dot(N, H)), m_Specular) * m_SpecularPower;

	out_Color = Input.Color * tex2D(g_Texture, Input.Texcoord) + S;
	out_Color = out_Color + color;

	return out_Color;
}

