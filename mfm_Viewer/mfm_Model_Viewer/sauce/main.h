//-----------------------------------------------------------------------------
// ���C���w�b�_			�@�@
// AT12A242 �@��j���@2017/6/05 
//-----------------------------------------------------------------------------
#ifndef __MAIN_H__
#define __MAIN_H__

#define FVF_VERTEX_3D		( D3DFVF_XYZ | D3DFVF_NORMAL |D3DFVF_DIFFUSE | D3DFVF_TEX1 )//D3DFVF_XYZRHW������Ȃ�//3D�p��FVF

#define SCREEN_WIDTH		( 1280 )//���T�C�Y
#define SCREEN_HIEGTH		( 720 )//�c�T�C�Y
//#define SCREEN_WIDTH		( 1920 )//���T�C�Y
//#define SCREEN_HIEGTH		( 1080 )//�c�T�C�Y

#define _CRT_SECURE_NO_WARNINGS 1

#include "Animation.h"

LPDIRECT3DDEVICE9 GetD3DDevice(void);
HIERARCHYDERIVED* GetHierearchy(void);


#endif //__MAIN_H__