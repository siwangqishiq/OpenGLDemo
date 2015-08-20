#ifndef _DRAWOPENGL_H_
#define _DRAWOPENGL_H_

#include <gl\glut.h>

#define SCR_WDITH       800      //屏幕宽度
#define SCR_HEIGHT      600      //屏幕高度

struct Color_TYPE{
	int r;
	int g;
	int b;
	int a;
};
typedef struct Color_TYPE Color;

//在(x,y)点处  绘制颜色color
int drawPoint(float x, float y, const Color color);

//在(x,y)点处  绘制颜色color
int drawPointInt(int x, int y, const Color color);

int drawLine(float x1, float y1, float x2, float y2, const Color color);

int drawLineInt(int x1, int y1, int x2, int y2, const Color color);

#endif