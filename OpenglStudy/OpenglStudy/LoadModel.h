#ifndef _LOADMODEL_H_
#define _LOADMODEL_H_

//����modelģ��
#include "Geass.h"
#include <string.h>

#define SHOW_LOG 1;

#define   BUF_MAX      256

//����
#define   PLX_RGB_MASK             0x8000
#define   PLX_SHADE_MODE_MASK      0x6000
#define   PLX_2SIDED_MASK          0x1000
#define   PLX_COLOR_MASK           0x0fff

//��ɫģʽ
#define   PLX_COLOR_MODE_RGB_FLAG         0x8000//RGB��ɫģʽ
#define   PLX_COLOR_MODE_INDEXED_FLAG	  0x0000//������ɫģʽ

//������Ƿ�Ϊ˫�� 
#define   PLX_2SIDED_FLAG     0x1000//˫��
#define   PLX_1SIDED_FLAG     0x0000//����

//��ɫģʽ
#define   PLX_SHADE_MODE_PURE_FLAG       0x0000//�����ʹ�ù̶���ɫ
#define   PLX_SHADE_MODE_FLAT_FLAG       0x2000//���ģʽ
#define   PLX_SHADE_MODE_GOURAUD_FLAG    0x4000//gouraud��ɫ
#define   PLX_SHADE_MODE_PHONG_FLAG      0x8000//phong��ɫ

//�ж��ַ��Ƿ�Ϊ�ո� �� ����
int isspace(char c);
//��ȡPLG�ļ�һ��
char *readPlxFileLine(char *buffer,int maxLength,FILE *fp);

//����PLX�ļ�
int loadObjectPlg(Object1 *pObj, const char *filename,
	Vector4D *scale, Vector4D *pos, Vector4D *rotate);

//��������ƽ���뾶 �� ���뾶
int computeObjectRadius(Object1 *obj);

#endif
