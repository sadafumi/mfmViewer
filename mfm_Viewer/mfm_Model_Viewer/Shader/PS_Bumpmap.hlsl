

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

// ��
float4		g_diffuse		: register(c0);					// �f�B�t���[�Y
float4		g_emmisive		: register(c1);					// �G�~�b�V�u
float4		g_ambient		: register(c2);					// ����
float4		g_specular		: register(c3);					// �X�y�L�����[��
float3		g_light_dir 	: register(c4);				// ���s�����̕���
// �}�e���A��
float4		g_diffuse_mat	: register(c5);				// �f�B�t���[�Y��
float4		g_emmisive_mat	: register(c6);				// �G�~�b�V�u��
float4		g_ambient_mat	: register(c7);				// ����
float4		g_specular_mat	: register(c8);				// �X�y�L�����[
float		g_power			: register(c9);					// �X�y�L�����[���̃p���[�l

// �X�y�L�������̌v�Z�p	
float4		g_camerapos		: register(c10);				// �J�����ʒu

sampler2D g_Texture : register(s0);
sampler2D g_Bump_map : register(s1);

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float2 Texcoord	: TEXCOORD0;
	float3 Posforps	: TEXCOORD2;
	float3 Normal	: NORMAL;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT Input) : SV_TARGET
{
	float4 out_Color;
	float4 tex_color = tex2D(g_Texture, Input.Texcoord);
	float4 Bump_Color = tex2D(g_Bump_map, Input.Texcoord);

	float3	N;		// ���[���h��ԏ�̖@���x�N�g��
	float3	L;		// ���̍������ޕ���
	float3	P;		// ���[���h��ԏ�̒��_���W
	float3	V;		// �i�J�������W�[���_���W�j�x�N�g��
	float3  H;		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j

	P = Input.Posforps;
	// ���[���h��Ԃł̖@���x�N�g���i���K�����K�v�j
	N = normalize((float3)(Bump_Color));
	//N = normalize((float3)(Bump_Color) + Input.Normal);
	//N = normalize(Input.Normal);

	// ���s���̍������ޕ���	�P�ʃx�N�g����
	L = normalize(g_light_dir);

	// �����x�N�g�������߂違���K��
	V = normalize(g_camerapos.xyz - P);

	// �n�[�t�x�N�g�������߂�
	H = normalize(V + L);

	// �o�̓J���[�����߂�
	float4 diffuse = g_ambient * g_ambient_mat + g_diffuse * g_diffuse_mat * max(0.0, dot(L, N));


	// �X�y�L�����[���ɂ��F���v�Z
	float4 specular = g_specular * g_specular_mat * pow(max(0.0, dot(N, H)), 50);

	out_Color = saturate(diffuse * tex_color + specular);

	return out_Color;
}

