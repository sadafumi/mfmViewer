#ifndef _DEBUG_H_
#define _DEBUG_H_


void InitDebugText();
void UnInitDebugText();
void DebugText(int x,int y,const char* PFormat,...);

void DebugPolgon(int n,float x ,float y,float );
//（...）無限に引数が増やせる

#endif //_DEBUG_H_

