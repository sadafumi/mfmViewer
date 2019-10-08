#include "SystemKeyBoard.h"
#include "InputKeyboard.h"
//-----------------------------------------------------------------------------
// キーボード
// AT12A242 宗貞史樹　
//-----------------------------------------------------------------------------

#define LINES (13)
#define INCHARPOSX (300)
#define INCHARPOSY (130)
#define KEYBOARDPOSX (100)
#define KEYBOARDPOSY (200)
#define CHARSIZEW (40)
#define CHARSIZEH (40)
#define WHITE (D3DXVECTOR4(255.0f, 255.0f, 255.0f, 255.0f))
#define BLACK (D3DXVECTOR4(0.0f, 0.0f, 0.0f, 255.0f))


#define KEYBFLASH (5.0f)

void SystemKeyBoard::InitKeyBorad(void)
{
	BoardX = 0;
	BoardY = 0;
	BoardType = SystemKeyBoard::HIRAGANA_A;
	InCharCunt = 0;
	KeyBFlash = 0;
	EndInName = false;
	for (size_t i = 0; i < INCHARMAX; i++)
	{
		Newinchar[i].type = NONE;
		Newinchar[i].x = 0;
		Newinchar[i].y = 0;
		Newinchar[i].Empty = true;
	}
}

void SystemKeyBoard::UninitKeyBorad(void)
{
}

void SystemKeyBoard::UpdateKeyBorad(void)
{
	bool Fast, Second, Third, Line, Afra, Ex1, Ex2;
	static int cou = 0;
	static bool bFlip = true;
	if (bFlip)
	{
		KeyBFlash += KEYBFLASH;
		if (KeyBFlash >= 255)
		{
			bFlip = false;
		}
	}
	else
	{
		KeyBFlash += -KEYBFLASH;
		if (KeyBFlash <= 0)
		{
			bFlip = true;
		}
	}
	
	if (InputKeyboard::GetKeyboardTrigger(DIK_S) || InputKeyboard::GetKeyboardTrigger(DIK_J))
	{
		BoardY++;
		if (BoardType != ROMAJI_A)
		{
			if (BoardY == 2)
			{
				if ((BoardX == 4) || (BoardX == 6))
				{
					BoardY++;
				}
			}
		}
	}
	if (InputKeyboard::GetKeyboardTrigger(DIK_W) || InputKeyboard::GetKeyboardTrigger(DIK_U))
	{
		BoardY--;
		if (BoardType != ROMAJI_A)
		{
			if (BoardY == 2)
			{
				if ((BoardX == 4) || (BoardX == 6))
				{
					BoardY--;
				}
			}
		}
	}
	if (InputKeyboard::GetKeyboardTrigger(DIK_A))
	{
		BoardX--;
		if (BoardType != ROMAJI_A)
		{
			if (BoardY == 2)
			{
				if ((BoardX == 4) || (BoardX == 6))
				{
					BoardX--;
				}
			}
		}
	}
	if (InputKeyboard::GetKeyboardTrigger(DIK_D))
	{
		BoardX++;
		if (BoardType != ROMAJI_A)
		{
			if (BoardY == 2)
			{
				if ((BoardX == 4) || (BoardX == 6))
				{
					BoardX++;
				}
			}
		}
	}
	if (BoardX < 0)
	{
		BoardX = KEYBOARDX - 1;
	}
	if (BoardY < 0)
	{
		BoardY = KEYBOARDY - 1;
	}
	BoardX = BoardX % KEYBOARDX;
	BoardY = BoardY % KEYBOARDY;
	if ((InputKeyboard::GetKeyboardTrigger(DIK_RETURN) || InputKeyboard::GetKeyboardTrigger(DIK_K)) && cou > 3)
	{
		if (BoardX != 10)
		{
			if (InCharCunt < INCHARMAX)
			{
				Newinchar[InCharCunt].type = BoardType;
				Newinchar[InCharCunt].x = BoardX;
				Newinchar[InCharCunt].y = BoardY;
				Newinchar[InCharCunt].Empty = false;
				InCharCunt++;
			}
		}
		else
		{
			if (BoardY == 0)
			{
				if (BoardType == HIRAGANA_A)
				{
					BoardType = KATAKANA_A;
				}
				else if (BoardType == KATAKANA_A)
				{
					BoardType = ROMAJI_A;
				}
				else if (BoardType == ROMAJI_A)
				{
					BoardType = HIRAGANA_A;
				}
			}
			if (BoardY == 1)
			{
				InCharCunt--;
				if (BoardType != ROMAJI_A)
				{
					if (!Newinchar[InCharCunt].Empty)
					{
						Fast = (Newinchar[InCharCunt].x > 4 && Newinchar[InCharCunt].y == 0);
						Second = (Newinchar[InCharCunt].x < 5 && Newinchar[InCharCunt].y == 1);
						Third = (Newinchar[InCharCunt].x < 5 && Newinchar[InCharCunt].y == 2);
						Line = (Newinchar[InCharCunt].x < 5 && Newinchar[InCharCunt].y == 3);
						if (Fast || Second || Third || Line)
						{
							if (Newinchar[InCharCunt].type == HIRAGANA_A)
							{
								Newinchar[InCharCunt].type = HIRAGANA_B;
							}
							else if (Newinchar[InCharCunt].type == KATAKANA_A)
							{
								Newinchar[InCharCunt].type = KATAKANA_B;
							}
							else if (Newinchar[InCharCunt].type == HIRAGANA_B)
							{
								Newinchar[InCharCunt].type = HIRAGANA_A;
							}
							else if (Newinchar[InCharCunt].type == KATAKANA_B)
							{
								Newinchar[InCharCunt].type = KATAKANA_A;
							}
						}
					}
				}
				InCharCunt++;
			}
			if (BoardY == 2)
			{
				InCharCunt--;
				Fast = (Newinchar[InCharCunt].x < 5 && Newinchar[InCharCunt].y == 0);
				Third = (Newinchar[InCharCunt].x > 4 && Newinchar[InCharCunt].y == 2);
				Afra = ((Newinchar[InCharCunt].x < 6 && Newinchar[InCharCunt].y == 2) || Newinchar[InCharCunt].y == 0 || Newinchar[InCharCunt].y == 1);
				Ex1 = (Newinchar[InCharCunt].x == 2 && Newinchar[InCharCunt].y == 3);
				Ex2 = (Newinchar[InCharCunt].x == 5 && Newinchar[InCharCunt].y == 4);
				if (BoardType != ROMAJI_A)
				{
					if (!Newinchar[InCharCunt].Empty)
					{
						if (Fast || Third)
						{
							if (Newinchar[InCharCunt].type == HIRAGANA_A)
							{
								Newinchar[InCharCunt].type = HIRAGANA_B;
								if (Ex1)
								{
									Newinchar[InCharCunt].x = 6;
									Newinchar[InCharCunt].y = 2;
								}
								if (Ex2)
								{
									Newinchar[InCharCunt].x = 8;
									Newinchar[InCharCunt].y = 2;
								}
							}
							else if (Newinchar[InCharCunt].type == KATAKANA_A)
							{
								Newinchar[InCharCunt].type = KATAKANA_B;
								if (Ex1)
								{
									Newinchar[InCharCunt].x = 6;
									Newinchar[InCharCunt].y = 2;
								}
								if (Ex2)
								{
									Newinchar[InCharCunt].x = 8;
									Newinchar[InCharCunt].y = 2;
								}
							}
							else if (Newinchar[InCharCunt].type == HIRAGANA_B)
							{
								Newinchar[InCharCunt].type = HIRAGANA_A;
								if (Ex1)
								{
									Newinchar[InCharCunt].x = 2;
									Newinchar[InCharCunt].y = 3;
								}
								if (Ex2)
								{
									Newinchar[InCharCunt].x = 5;
									Newinchar[InCharCunt].y = 4;
								}
							}
							else if (Newinchar[InCharCunt].type == KATAKANA_B)
							{
								Newinchar[InCharCunt].type = KATAKANA_A;
								if (Ex1)
								{
									Newinchar[InCharCunt].x = 2;
									Newinchar[InCharCunt].y = 3;
								}
								if (Ex2)
								{
									Newinchar[InCharCunt].x = 5;
									Newinchar[InCharCunt].y = 4;
								}
							}
						}
						if (Afra)
						{
							if (Newinchar[InCharCunt].type == ROMAJI_A)
							{
								Newinchar[InCharCunt].type = ROMAJI_B;
							}
							else if (Newinchar[InCharCunt].type == ROMAJI_B)
							{
								Newinchar[InCharCunt].type = ROMAJI_A;
							}
						}
					}
				}
				InCharCunt++;
			}
			if (BoardY == 3)
			{
				if (InCharCunt > 0)
				{
					InCharCunt--;
					Newinchar[InCharCunt].type = NONE;
					Newinchar[InCharCunt].x = 0;
					Newinchar[InCharCunt].y = 0;
					Newinchar[InCharCunt].Empty = true;
				}
			}
			if (BoardY == 4)
			{
				if (InCharCunt != 0)
				{
					EndInName = true;
					for (size_t i = 0; i < INCHARMAX; i++)
					{
						//SetName(i, Newinchar[i]);
					}
				}
			}
		}
	}
	cou++;

}

void SystemKeyBoard::DrawKeyBorad(void)
{
	if (InCharCunt < 5)
	{
		KeyBoradRender.SetRendData(&KeyBorad_Fade, 1, 1);
		KeyBoradRender.SetColor(D3DXVECTOR4(255.0f, 255.0f, 255.0f, KeyBFlash));
		//KeyBoradRender.SetPositon( D3DXVECTOR3(INCHARPOSX + (CHARSIZEW * (float)InCharCunt), INCHARPOSY, CHARSIZEW, CHARSIZEH) );
		KeyBoradRender.SetPositon(D3DXVECTOR2(INCHARPOSX + (CHARSIZEW * (float)InCharCunt), INCHARPOSY));
		KeyBoradRender.Draw();
	}
	KeyBoradRender.SetRendData(&KeyBorad_Fade, 1, 1);
	KeyBoradRender.SetColor(D3DXVECTOR4(255.0f, 255.0f, 10.0f, 255.0f));
	//KeyBoradRender.SetPositon(D3DXVECTOR3((KEYBOARDPOSX + CHARSIZEW * (float)BoardX) + LINES * BoardX, (KEYBOARDPOSY + CHARSIZEH * (float)BoardY) + LINES * BoardY, CHARSIZEW, CHARSIZEH));
	KeyBoradRender.SetPositon(D3DXVECTOR2((KEYBOARDPOSX + CHARSIZEW * (float)BoardX) + LINES * BoardX, (KEYBOARDPOSY + CHARSIZEH * (float)BoardY) + LINES * BoardY));
	if (BoardX == 10)
	{
		//KeyBoradRender.SetPositon(D3DXVECTOR3((KEYBOARDPOSX + CHARSIZEW * (float)BoardX) + LINES * BoardX, (KEYBOARDPOSY + CHARSIZEH * (float)BoardY) + LINES * BoardY, CHARSIZEW * 2, CHARSIZEH));
		KeyBoradRender.SetPositon(D3DXVECTOR2((KEYBOARDPOSX + CHARSIZEW * (float)BoardX) + LINES * BoardX, (KEYBOARDPOSY + CHARSIZEH * (float)BoardY) + LINES * BoardY));
	}
	KeyBoradRender.Draw();

	for (size_t i = 0; i < INCHARMAX; i++)
	{
		KeyBoradRender.SetRendData(&KeyBorad_Fade, KEYBOARDX - 1, KEYBOARDY);
		//KeyBoradRender.SetTexAnimation(Newinchar[i].y * (KEYBOARDX - 1) + Newinchar[i].x, KEYBOARDX - 1, KEYBOARDY);
		KeyBoradRender.SetAnimationNum(Newinchar[i].y * (KEYBOARDX - 1) + Newinchar[i].x);
		KeyBoradRender.SetColor(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 10.0f));
		if (!Newinchar[i].Empty)
		{
			if (Newinchar[i].type == HIRAGANA_A)
			{
				KeyBoradRender.SetRendData(&KeyBorad_Hira_A, KEYBOARDX - 1, KEYBOARDY);
			}
			if (Newinchar[i].type == KATAKANA_A)
			{
				KeyBoradRender.SetRendData(&KeyBorad_Kata_A, KEYBOARDX - 1, KEYBOARDY);
			}
			if (Newinchar[i].type == ROMAJI_A)
			{
				KeyBoradRender.SetRendData(&KeyBorad_Roma_A, KEYBOARDX - 1, KEYBOARDY);
			}
			if (Newinchar[i].type == HIRAGANA_B)
			{
				KeyBoradRender.SetRendData(&KeyBorad_Hira_B, KEYBOARDX - 1, KEYBOARDY);
			}
			if (Newinchar[i].type == KATAKANA_B)
			{
				KeyBoradRender.SetRendData(&KeyBorad_Kata_B, KEYBOARDX - 1, KEYBOARDY);
			}
			if (Newinchar[i].type == ROMAJI_B)
			{
				KeyBoradRender.SetRendData(&KeyBorad_Roma_B, KEYBOARDX - 1, KEYBOARDY);
			}
			KeyBoradRender.SetColor(BLACK);
		}
		//KeyBoradRender.SetPositon(D3DXVECTOR3(INCHARPOSX + CHARSIZEW * (float)i, INCHARPOSY, CHARSIZEW, CHARSIZEH));
		KeyBoradRender.SetPositon(D3DXVECTOR2(INCHARPOSX + CHARSIZEW * (float)i, INCHARPOSY));
		KeyBoradRender.Draw();
	}
	for (size_t i = 0; i < KEYBOARDX; i++)
	{
		for (size_t j = 0; j < KEYBOARDY; j++)
		{
			if (i != 10)
			{
				//KeyBoradRender.SetTexAnimation(j * (KEYBOARDX - 1) + i, KEYBOARDX - 1, KEYBOARDY);
				KeyBoradRender.SetAnimationNum(j * (KEYBOARDX - 1) + i);
				if (BoardType == HIRAGANA_A)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Hira_A, KEYBOARDX - 1, KEYBOARDY);
				}
				if (BoardType == KATAKANA_A)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Kata_A, KEYBOARDX - 1, KEYBOARDY);
				}
				if (BoardType == ROMAJI_A)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Roma_A, KEYBOARDX - 1, KEYBOARDY);
				}
				if (BoardType == HIRAGANA_B)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Hira_B, KEYBOARDX - 1, KEYBOARDY);
				}
				if (BoardType == KATAKANA_B)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Kata_B, KEYBOARDX - 1, KEYBOARDY);
				}
				if (BoardType == ROMAJI_B)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Roma_B, KEYBOARDX - 1, KEYBOARDY);
				}
				KeyBoradRender.SetColor(BLACK);
				//KeyBoradRender.SetPositon((KEYBOARDPOSX + CHARSIZEW * (float)i) + LINES * i, (KEYBOARDPOSY + CHARSIZEH * (float)j) + LINES * j, CHARSIZEW, CHARSIZEH);
				KeyBoradRender.SetPositon(D3DXVECTOR2((KEYBOARDPOSX + CHARSIZEW * (float)i) + LINES * i, (KEYBOARDPOSY + CHARSIZEH * (float)j) + LINES * j));
				KeyBoradRender.Draw();
			}
			else
			{
				if (j == 0)
				{
					KeyBoradRender.SetRendData(&KeyBorad_Option_1, 1, 3);
					//KeyBoradRender.SetTexAnimation((BoardType + 1) % 3, 1, 3);
					KeyBoradRender.SetAnimationNum((BoardType + 1) % 3);
					//KeyBoradRender.SetPositon((KEYBOARDPOSX + CHARSIZEW * (float)i) + LINES * i, (KEYBOARDPOSY + CHARSIZEH * (float)j) + LINES * j, CHARSIZEW * 2, CHARSIZEH);
					KeyBoradRender.SetPositon(D3DXVECTOR2((KEYBOARDPOSX + CHARSIZEW * (float)i) + LINES * i, (KEYBOARDPOSY + CHARSIZEH * (float)j) + LINES * j));
					KeyBoradRender.SetColor(BLACK);
					KeyBoradRender.Draw();
				}
				else
				{
					KeyBoradRender.SetRendData(&KeyBorad_Option_2, 1, 1);
					//KeyBoradRender.SetPositon((KEYBOARDPOSX + CHARSIZEW * (float)i) + LINES * i, (KEYBOARDPOSY + CHARSIZEH * (float)1) + LINES * 1, CHARSIZEW * 2, CHARSIZEH * 5);
					KeyBoradRender.SetPositon(D3DXVECTOR2((KEYBOARDPOSX + CHARSIZEW * (float)i) + LINES * i, (KEYBOARDPOSY + CHARSIZEH * (float)1) + LINES * 1));
					KeyBoradRender.SetColor(BLACK);
					KeyBoradRender.Draw();
				}
			}
		}
	}

	KeyBoradRender.SetColor(WHITE);

}

bool SystemKeyBoard::EneKeyBorad()
{
	return EndInName;
}
