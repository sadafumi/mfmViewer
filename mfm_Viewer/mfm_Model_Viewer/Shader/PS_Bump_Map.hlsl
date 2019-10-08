

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

// ��
// �}�e���A��
float4	m_LightDir : register(c0);
// �X�y�L�������̌v�Z�p	
float4 m_Ambient		: register(c1);       //����
float  m_Specular		: register(c2);      //�n�C���C�g�͈̔�
float  m_SpecularPower	: register(c3);  //�n�C���C�g�̋��x

sampler2D g_Texture : register(s0);
sampler2D g_Bump	: register(s1);        //�@���}�b�v

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float2 Texcoord : TEXCOORD0;
	float3 Eye : TEXCOORD1; //���_���W�n�ł̎��������x�N�g��
	float3 Light : TEXCOORD2; //���_���W�n�ł̒��_ �� ���C�g�ʒu�x�N�g��
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
