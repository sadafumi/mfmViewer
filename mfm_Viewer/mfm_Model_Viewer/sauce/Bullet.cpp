#include "Include.h"

#define BULLET_SPEED (3.0f)
#define BULLET_HEIGHT (0)
#define BOARD ("tree_b.png")

typedef struct
{
	D3DXVECTOR3 g_Pos; //ã ÇÃèÍèä
	D3DXVECTOR3 g_Move; //ã ÇÃèÍèä
	bool g_bBullet;	//ã Ç™î≠éÀÇ≥ÇÍÇΩÇ©
	RenderBillBoard *billboard ;
	int Life;
}BULLET;

BULLET g_Bullet[BULLET_MAX];
VERTEXDATA BulletVerTex;


void InitBullet(void)
{
	CreateMeshBoard(&BulletVerTex, BOARD);
	int i;
	for (i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].billboard = new RenderBillBoard;
		g_Bullet[i].billboard->SetRendData(&BulletVerTex);
	}

}
void UninitBullet(void)
{
	BulletVerTex.Destroy();
	int i;
	for (i = 0; i < BULLET_MAX; i++)
	{
		delete g_Bullet[i].billboard;
	}
	
}
void UpdateBullet(void)
{
	int i;
	for (i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].g_bBullet)
		{
			g_Bullet[i].g_Pos -= g_Bullet[i].g_Move * 0.5;
			if (g_Bullet[i].g_Pos.x >= 18 || g_Bullet[i].g_Pos.x <= -18)
			{			
				g_Bullet[i].g_bBullet = false;
				CreateExplosion(g_Bullet[i].g_Pos); 
				DestroyBullet(i);
			}
			if (g_Bullet[i].g_Pos.z >= 18 || g_Bullet[i].g_Pos.z <= -18)
			{
				g_Bullet[i].g_bBullet = false;
				CreateExplosion(g_Bullet[i].g_Pos);
				DestroyBullet(i);
			}
			g_Bullet[i].billboard->SetMtXPos(g_Bullet[i].g_Pos.x, g_Bullet[i].g_Pos.y,g_Bullet[i].g_Pos.z);
			g_Bullet[i].billboard->SetMtXView(GetViewMtx());
			g_Bullet[i].Life--;
		}
	}
}
void DrawBullet(void)
{
	int i;
	for (i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].g_bBullet)
		{
			g_Bullet[i].billboard->Draw();
		}
	}
}
void CreateBullet(D3DXVECTOR3 Pos, D3DXVECTOR3 Mae)
{
	int i;
	for (i = 0; i < BULLET_MAX; i++)
	{
		if (!g_Bullet[i].g_bBullet)
		{
			g_Bullet[i].g_Pos = Pos;
			g_Bullet[i].g_Move = Mae;
			g_Bullet[i].g_bBullet = true;
			g_Bullet[i].Life = 100;
			break;
		}
	}
}
bool IsBullet(int BullCon)
{
	return g_Bullet[BullCon].g_bBullet;
}
void DestroyBullet(int index)
{
	g_Bullet[index].g_bBullet = false;

}
