#ifndef _DRAWOPENGL_H_
#define _DRAWOPENGL_H_

#include <gl\glut.h>

#define SCR_WDITH       800      //��Ļ���
#define SCR_HEIGHT      600      //��Ļ�߶�

struct Color_TYPE{
	int r;
	int g;
	int b;
	int a;
};
typedef struct Color_TYPE Color;

//��(x,y)�㴦  ������ɫcolor
int drawPoint(float x, float y, const Color color);

//��(x,y)�㴦  ������ɫcolor
int drawPointInt(int x, int y, const Color color);

int drawLine(float x1, float y1, float x2, float y2, const Color color);

int drawLineInt(int x1, int y1, int x2, int y2, const Color color);

#endif