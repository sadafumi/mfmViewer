

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------

// 光
float4		g_diffuse		: register(c0);					// ディフューズ
float4		g_emmisive		: register(c1);					// エミッシブ
float4		g_ambient		: register(c2);					// 環境光
float4		g_specular		: register(c3);					// スペキュラー光
float3		g_light_dir 	: register(c4);				// 平行光源の方向
// マテリアル
float4		g_diffuse_mat	: register(c5);				// ディフューズ光
float4		g_emmisive_mat	: register(c6);				// エミッシブ光
float4		g_ambient_mat	: register(c7);				// 環境光
float4		g_specular_mat	: register(c8);				// スペキュラー
float		g_power			: register(c9);					// スペキュラー光のパワー値

// スペキュラ光の計算用	
float4		g_camerapos		: register(c10);				// カメラ位置

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

	float3	N;		// ワールド空間上の法線ベクトル
	float3	L;		// 光の差し込む方向
	float3	P;		// ワールド空間上の頂点座標
	float3	V;		// （カメラ座標ー頂点座標）ベクトル
	float3  H;		//  ハーフベクトル（視線ベクトルと光の方向ベクトル）

	P = Input.Posforps;
	// ワールド空間での法線ベクトル（正規化が必要）
	N = normalize((float3)(Bump_Color));
	//N = normalize((float3)(Bump_Color) + Input.Normal);
	//N = normalize(Input.Normal);

	// 平行光の差し込む方向	単位ベクトル化
	L = normalize(g_light_dir);

	// 視線ベクトルを求める＆正規化
	V = normalize(g_camerapos.xyz - P);

	// ハーフベクトルを求める
	H = normalize(V + L);

	// 出力カラーを決める
	float4 diffuse = g_ambient * g_ambient_mat + g_diffuse * g_diffuse_mat * max(0.0, dot(L, N));


	// スペキュラー光による色を計算
	float4 specular = g_specular * g_specular_mat * pow(max(0.0, dot(N, H)), 50);

	out_Color = saturate(diffuse * tex_color + specular);

	return out_Color;
}

