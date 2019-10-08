

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

// 光
// マテリアル
float4	m_LightDir : register(c0);
// スペキュラ光の計算用	
float4 m_Ambient		: register(c1);       //環境光
float  m_Specular		: register(c2);      //ハイライトの範囲
float  m_SpecularPower	: register(c3);  //ハイライトの強度

sampler2D g_Texture : register(s0);
sampler2D g_Bump	: register(s1);        //法線マップ

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float2 Texcoord : TEXCOORD0;
	float3 Eye : TEXCOORD1; //頂点座標系での視線方向ベクトル
	float3 Light : TEXCOORD2; //頂点座標系での頂点 → ライト位置ベクトル
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT Input) : SV_TARGET
{
	float4 out_Color;

	float3 Normal = 2.0f * tex2D(g_Bump, Input.Texcoord).xyz - 1.0f;

	float3 H = normalize(Input.Light + Input.Eye);

	float S = pow(max(0.0f, dot(Normal, H)), m_Specular) * m_SpecularPower;

	out_Color =  tex2D(g_Texture, Input.Texcoord) * max(m_Ambient, dot(Normal, Input.Light)) + S;

	return out_Color;
}
