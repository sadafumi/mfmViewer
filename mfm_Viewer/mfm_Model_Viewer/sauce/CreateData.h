#ifndef __CREATEDATA_H__
#define __CREATEDATA_H__

#include"Include.h"



void CreateVerTex(VERTEXDATA *InOut,LPSTR TeXCFileName, std::vector<VERTEX3D> *vtx, std::vector<WORD> *index);
//�`��ɕK�v�Ȓ��_�f�[�^�쐬�����̃f�[�^�̍\���̃|�C���^��Ԃ�
void CreateMesh(MESHDATA *InOut,LPSTR TeXCFileName);
//�`��ɕK�v�ȃ��b�V���f�[�^�쐬�����̃f�[�^�̍\���̃|�C���^��Ԃ�
void CreateMFMMesh(MFMMESHDATA *InOut, LPSTR TeXCFileName);
//�`��ɕK�v�ȃ��b�V���f�[�^�쐬�����̃f�[�^�̍\���̃|�C���^��Ԃ�
void CreateMeshField(VERTEXDATA *InOut,LPSTR TeXCFileName, int w, int h);
//�`��ɕK�v�ȃ��b�V���f�[�^�쐬�����̃f�[�^�̍\���̃|�C���^��Ԃ�
void CreateMeshBoard(VERTEXDATA *InOut, LPSTR TeXCFileName);
//�`��ɕK�v�ȃ��b�V���f�[�^�쐬�����̃f�[�^�̍\���̃|�C���^��Ԃ�
void CreateFramDataMesh(FRAMEDATA *InOut, LPSTR TeXCFileName);
//�`��ɕK�v�ȃA�j���[�V�����̓��������b�V����ǂݍ��ލ쐬�����̃f�[�^�̍\���̃|�C���^��Ԃ�
void CreateMeshAnimationBoard(VERTEXDATA *InOut, LPSTR TeXCFileName);
int EditPath(TCHAR *OutPath, TCHAR *InPath, TCHAR *AddPath);
int CutPath(TCHAR *Out, TCHAR *In);



#endif//__CREATEDATA_H__


