
//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};

float4 m_EyePos   : register(c4);                //���_�ʒu�x�N�g��
float4 m_LightDir : register(c5);              //���s�����̕����x�N�g��
//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL; //�@���x�N�g��
	float2 Texcoord		: TEXCOORD;   //�e�N�Z��
};

struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float2 Texcoord	: TEXCOORD0;
	float3 Eye : TEXCOORD1; //���_���W�n�ł̎��������x�N�g��
	float3 Light : TEXCOORD2; //���_���W�n�ł̒��_ �� ���C�g�ʒu�x�N�g��
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.Position = mul(Input.Position, g_mWorldViewProjection);		// ���_���W�i���[�J�����W�n�j�����[���h���W�n�ɕϊ�	

	Output.Texcoord = Input.Texcoord;

	//�����x�N�g�����v�Z
	float3 Eye = normalize(m_EyePos.xyz - Input.Position.xyz);

	Input.Normal = normalize(Input.Normal);
	float3 Tangent = normalize(cross(Input.Normal, float3(0.0, 1.0, 0.0)));
	float3 Binormal = cross(Input.Normal,Tangent);

	//�����x�N�g���𒸓_���W�n�ɕϊ�����
	Output.Eye.x = dot(Eye, Tangent);
	Output.Eye.y = dot(Eye, Binormal);
	Output.Eye.z = dot(Eye, Input.Normal);
	Output.Eye = normalize(Output.Eye);

	//���_���W -> ���C�g�̈ʒu�x�N�g��
	float3 Light = -m_LightDir.xyz;

	//���C�g�x�N�g���𒸓_���W�n�ɕϊ�����
	Output.Light.x = dot(Light, Tangent);
	Output.Light.y = dot(Light, Binormal);
	Output.Light.z = dot(Light, Input.Normal);
	Output.Light = normalize(Output.Light);

	return Output;
}