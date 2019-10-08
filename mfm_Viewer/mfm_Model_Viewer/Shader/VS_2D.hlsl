
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};

//float4  UV : register(c6);
float4	f4Frames : register(c4);
float4  Pos_Sca : register(c5);
float4	In_Color : register(c6);

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
	float4 vColor		: COLOR0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Input.vPosition.x = Pos_Sca.x + (Input.vPosition.x * Pos_Sca.z);
	Input.vPosition.y = Pos_Sca.y + (Input.vPosition.y * Pos_Sca.w);
	Output.vPosition = Input.vPosition;
	Output.vPosition = mul(Input.vPosition,  g_mWorldViewProjection);
	//Output.vNormal = mul(Input.vNormal, (float3x3)g_mWorld);
	Output.vNormal = Input.vNormal;
	Output.vTexcoord = Input.vTexcoord;
	Output.vColor = In_Color;

	Output.vTexcoord.xy += f4Frames.zw;
	float2 f2TotalFramesNoZero;
	f2TotalFramesNoZero.x = f4Frames.x;
	f2TotalFramesNoZero.x += f4Frames.x == 0;
	f2TotalFramesNoZero.y = f4Frames.y;
	f2TotalFramesNoZero.y += f4Frames.y == 0;
	Output.vTexcoord.xy /= f2TotalFramesNoZero.xy;

	return Output;
}
