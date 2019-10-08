#include "Include.h"


//----------------------------------------------------------------------------------------------------------------------------------------------------------
//�֐����@bool HitCircle(float x0, float y0, float r0, float x1, float y1, float r1)
//�@�q�b�g�{�b�N�X�@�~�`
//	�����@float x0		�|�C���gA��X�@
//	�����@float y0�@	�|�C���gA��Y
//	�����@float r0�@	�|�C���gA��r
//	�����@float x1�@	�|�C���gB��X
//	�����@float y1�@	�|�C���gB��Y
//	�����@float r1�@	�|�C���gB��r
//
//	�Ԃ�l�@�|�C���gA�{�|�C���gB�̔��a���|�C���gA�ƃ|�C���gB�̋���
//			�������ꍇ��True
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------
bool HitCircle(float x0, float y0, float r0, float x1, float y1, float r1)
{
	// x0 - x0 , y0 - y0 �N�_�ɂȂ邽�߂O�ɂȂ���
	float x = x1 - x0;
	float y = y1 - y0;

	float l = x * x + y * y;

	return l < (r0 + r1) * (r0 + r1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//�֐����@bool HItBox(float PosX0, float PosY0, int BoxWid0, int BoxHei0, float PosX1, float Posy1, int BoxWid1, int BoxHei1)
//�@�q�b�g�{�b�N�X�@��`
//�@�����@float PosX0    
//  �����@float PosY0
//  �����@int   BoxWid0
//  �����@int   BoxHei0
//  �����@float PosX1
//  �����@float Posy1
//  �����@int   BoxWid1
//  �����@int   BoxHei1
//
//	�Ԃ�l�@�|�C���gA�{�|�C���gB�̔��a���|�C���gA�ƃ|�C���gB�̋���
//			�������ꍇ��True
//
//----------------------------------------------------------------------------------------------------------------------------------------------------------
bool HitBox(float PosX0, float PosY0, int BoxWid0, int BoxHei0, float PosX1, float PosY1, int BoxWid1, int BoxHei1)
{

	bool Judg1 = PosX0 < PosX1 + BoxWid1;
	bool Judg2 = PosY0 < PosY1 + BoxHei1;
	bool Judg3 = PosX0 + BoxWid0 > PosX1;
	bool Judg4 = PosY0 + BoxHei0 > PosY1;
	if(Judg4 && Judg3 && Judg2 && Judg1){return true;}
	return false;
}
