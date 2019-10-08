#include "Player.h"
#include "Flag.h"
#include "HitBox.h"
#include "Tower.h"

#define TowerModelPath ("resource\\model\\tower.x")
#define PLAYREMODEL ("resource\\model\\Player\\player.mfm")

static Player mainPlayer;
static Flag TestFlag;
Tower Test;
MESHDATA TowerData;
MFMMESHDATA dataPlayer;

void InitGameObject()
{
	CreateMFMMesh(&dataPlayer, PLAYREMODEL);
	CreateMesh(&TowerData, TowerModelPath);
	D3DXVECTOR3 TestPos = D3DXVECTOR3(50.0f,50.0f,50.0f);
	mainPlayer.Create(&dataPlayer);
	TestFlag.Create(Flag::TeamNone, TestPos);
	D3DXVECTOR3 Pos = D3DXVECTOR3(50.0f, 1.0f, 1.0f);
	D3DXVECTOR3 scale = D3DXVECTOR3(40.0f, 40.0f, 40.0f);
	D3DXVECTOR3 Roto = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Test.Create(&TowerData, Pos, Roto, scale);
}
void UnInitGameObject()
{
	mainPlayer.Destroy();
	dataPlayer.Destroy();
	TestFlag.Destroy();
	Test.Destroy();
	TowerData.Destroy();
}
void UpdateGameObject()
{
	Test.Update();
	mainPlayer.Updata();
	UpdateGameCamera();
	mainPlayer.SetCamera(GetGameCamera());
	TestFlag.SetCamera(GetGameCamera());
	TestFlag.Updata();
	if(JudgeSphere(&mainPlayer.GetSphereHitBox(), &TestFlag.GetSphereHitBox()))
	{

		int a = 0;
		a = a;
	}
}
void DrawGameObject()
{
	TestFlag.Draw();
	Test.Draw();
	mainPlayer.Draw();
}
Player* GetPlayer()
{
	return &mainPlayer;
}
