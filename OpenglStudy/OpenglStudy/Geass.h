#ifndef _GEASS_H_
#define _GEASS_H_

#include <stdio.h>
#include <gl\glut.h>

#define SCR_WDITH       800      //��Ļ���
#define SCR_HEIGHT      600      //��Ļ�߶�

struct _Point3D{
	float x;
	float y;
	float z;
};

typedef struct _Point3D Point3D;

struct _Color{
	int r;
	int g;
	int b;
	int a;
};
typedef struct _Color Color;

//�ڿ���̨��ӡ3D������
void printPoint3D(const Point3D * pPoint3D);

//��(x,y)�㴦  ������ɫcolor
int drawPoint(float x, float y, const Color color);

//��(x,y)�㴦  ������ɫcolor
int drawPointInt(int x, int y, const Color color);

int drawLine(float x1, float y1,float x2, float y2, const Color color);

int drawLineInt(int x1, int y1, int x2, int y2, const Color color);

#endif