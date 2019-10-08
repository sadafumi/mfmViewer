#include "Include.h"

#define EFFECT_SPEED (3.0f)
#define EFFECT_HEIGHT (0)
#define EFFECT_MAX (1000)
#define BOARDEFFECT ("Explosion.png")
#define MAXLIFE (64)
#define LIFESPEED (1)

typedef struct
{
	D3DXVECTOR3 g_Pos; //ã ÇÃèÍèä
	bool g_bEffect;	//ã Ç™î≠éÀÇ≥ÇÍÇΩÇ©
	RenderBillAnimation *Effect;
	int Life;
}EFFECT;

EFFECT g_Explosion[EFFECT_MAX];
VERTEXDATA ExplosionVerTex;


void InitExplosion(void)
{
	CreateMeshAnimationBoard(&ExplosionVerTex, BOARDEFFECT);
}
void UninitExplosion(void)
{
	ExplosionVerTex.Destroy();
}
void UpdateExplosion(void)
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Explosion[i].g_bEffect)
		{
			g_Explosion[i].Effect->SetMtXPos(g_Explosion[i].g_Pos.x, g_Explosion[i].g_Pos.y, g_Explosion[i].g_Pos.z);
			g_Explosion[i].Effect->SetMtXView(GetViewMtx());

			if(g_Explosion[i].Life == 0)
			{
				g_Explosion[i].g_bEffect = false;
			}
			g_Explosion[i].Life -= LIFESPEED;
		}
	}
}
void DrawExplosion(void)
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Explosion[i].g_bEffect)
		{
			g_Explosion[i].Effect->Draw();
		}
	}

	g_Explosion[0];
}
void CreateExplosion(D3DXVECTOR3 Pos)
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Explosion[i].g_bEffect)
		{
			g_Explosion[i].Effect = new RenderBillAnimation;
			g_Explosion[i].Effect->SetRendData(&ExplosionVerTex, MAXLIFE,8,8);
			g_Explosion[i].Effect->SetAnimationSpeed(LIFESPEED);
			g_Explosion[i].Effect->SetMtXScale(10,10,10);
			g_Explosion[i].g_Pos = Pos;
			g_Explosion[i].g_bEffect = true;
			g_Explosion[i].Life = MAXLIFE;
			break;
		}
	}
}
bool IsExplosion(int BullCon)
{
	return g_Explosion[BullCon].g_bEffect;
}
void DestroyExplosion(int index)
{
	g_Explosion[index].g_bEffect = false;
	delete g_Explosion[index].Effect;
}
