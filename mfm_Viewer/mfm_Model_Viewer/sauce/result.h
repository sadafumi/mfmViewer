//=============================================================================
//
// リザルト画面処理 [result.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_X	(100)			//画像の左上のX座標
#define RESULT_Y	(100)			//画像の左上のY座標
#define RESULT_X_WIDTH	(600)		//画像の幅
#define RESULT_Y_HEIGHT	(400)		//画像の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

class ResultScene :public Scene
{
	void Init();
	void UnInit();
	void Updata();
	void Draw();
};

#endif
