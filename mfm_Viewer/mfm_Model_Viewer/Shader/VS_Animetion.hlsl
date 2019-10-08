
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		WorldViewProjection	: packoffset(c0);
	matrix		Bones[60]	: packoffset(c4);
};
float4	Diffuse : register(c8);
float4  LightPos : register(c12);
float  LightBrightness : register(c16);

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position  	: POSITION;
	float4 Color		: COLOR0;
	float3 Normal		: NORMAL;
	float2 Texcoord	  : TEXCOORD0;
	float4 Blend 		: BLENDWEIGHT;
	int4   Index		: BLENDINDICES;
};

struct VS_OUTPUT
{
	float3 Normal	: NORMAL;
	float2 Texcoord	: TEXCOORD0;
	float4 Position	: SV_POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Input.Position.w = 1.0f;
	float w[4] = (float[4])Input.Blend;
	float4x4 comb = (float4x4)0;

	for (int i = 0; i < 3; i++)
	{
		comb += Bones[Input.Index[i]] * w[i];
	}
	comb += Bones[Input.Index[3]] * (1.0f - w[0] - w[1] - w[2]);

	float4 normL = normalize(LightPos); // 光源ベクトル(単位ベクトル)
	float4 normN = normalize(float4(Input.Normal, 0.1f)); // 法線ベクトル(単位ベクトル)
	float  L = LightBrightness * dot(normN, normL);       // 光の強さ

	Output.Normal = Diffuse * max(0, L);      // ディフューズ色

	
	Output.Position = mul(Input.Position, comb);
	Output.Position = mul(Output.Position, WorldViewProjection);

	Output.Texcoord = Input.Texcoord;

	return Output;
}
