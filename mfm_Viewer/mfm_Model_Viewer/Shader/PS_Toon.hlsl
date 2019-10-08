

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

float4 m_LightDir : register(c0);                     //平行光源の方向ベクトル

sampler2D g_Texture : register(s0);
sampler2D g_ToonMap : register(s1);


//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float2 vTexcoord	: TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT Input) : SV_TARGET
{
	float4 vDiffuse = tex2D(g_Texture, Input.vTexcoord);

	return vDiffuse ;
}

