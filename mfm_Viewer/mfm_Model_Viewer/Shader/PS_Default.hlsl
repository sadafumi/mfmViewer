

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

sampler2D g_samLinear : register(s0);

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
	float4 vDiffuse = tex2D(g_samLinear, Input.vTexcoord);

	return vDiffuse ;
}
