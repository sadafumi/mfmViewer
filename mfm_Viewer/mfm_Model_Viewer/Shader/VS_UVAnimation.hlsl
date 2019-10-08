
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);

		//	matrix		g_mWorld				: packoffset(c4);
};
//float4		f4Frames : register(c4);

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 vPosition	: POSITION;
	float4 vColor		: COLOR0;
	float3 vNormal		: NORMAL;
	float2 vTexcoord	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float3 vNormal		: NORMAL;
	float2 vTexcoord	: TEXCOORD0;
	float4 vPosition	: SV_POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorldViewProjection);
	//Output.vNormal = mul(Input.vNormal, (float3x3)g_mWorld);
	Output.vNormal = Input.vNormal;
	Output.vTexcoord = Input.vTexcoord;

	//Output.vTexcoord.xy += f4Frames.zw;
	//float2 f2TotalFramesNoZero;
	//f2TotalFramesNoZero.x = f4Frames.x;
	//f2TotalFramesNoZero.x += f4Frames.x == 0;
	//f2TotalFramesNoZero.y = f4Frames.y;
	//f2TotalFramesNoZero.x += f4Frames.y == 0;
	//Output.vTexcoord.xy /= f2TotalFramesNoZero.xy;

	return Output;
}
