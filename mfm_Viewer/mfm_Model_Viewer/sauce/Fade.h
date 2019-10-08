#ifndef _FADE_H_
#define _FADE_H_

#include "Include.h"

enum FADE_MODE
{
	FADE_NONE = -1,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
};

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void Fade( FADE_MODE , D3DCOLOR);
bool IsFadeIN();
bool IsFadeOUT();

#endif//_FADE_H_