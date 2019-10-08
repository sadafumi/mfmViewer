
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};

float4 m_EyePos   : register(c4);                //視点位置ベクトル
float4 m_LightDir : register(c5);              //平行光源の方向ベクトル
//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL; //法線ベクトル
	float2 Texcoord		: TEXCOORD;   //テクセル
};

struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float2 Texcoord	: TEXCOORD0;
	float3 Eye : TEXCOORD1; //頂点座標系での視線方向ベクトル
	float3 Light : TEXCOORD2; //頂点座標系での頂点 → ライト位置ベクトル
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorldViewProjection);		// 頂点座標（ローカル座標系）をワールド座標系に変換	

	Output.Texcoord = Input.Texcoord;

	//視線ベクトルを計算
	float3 Eye = normalize(m_EyePos.xyz - Input.Position.xyz);

	Input.Normal = normalize(Input.Normal);
	float3 Tangent = normalize(cross(Input.Normal, float3(0.0, 1.0, 0.0)));
	float3 Binormal = cross(Input.Normal,Tangent);

	//視線ベクトルを頂点座標系に変換する
	Output.Eye.x = dot(Eye, Tangent);
	Output.Eye.y = dot(Eye, Binormal);
	Output.Eye.z = dot(Eye, Input.Normal);
	Output.Eye = normalize(Output.Eye);

	//頂点座標 -> ライトの位置ベクトル
	float3 Light = -m_LightDir.xyz;

	//ライトベクトルを頂点座標系に変換する
	Output.Light.x = dot(Light, Tangent);
	Output.Light.y = dot(Light, Binormal);
	Output.Light.z = dot(Light, Input.Normal);
	Output.Light = normalize(Output.Light);

	return Output;
}