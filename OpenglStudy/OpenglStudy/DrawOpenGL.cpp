#include "DrawOpenGL.h"

//在(x,y)点处  绘制颜色color
int drawPoint(float x, float y, const Color color)
{
	glColor3f(color.r / 255, color.g / 255, color.b / 255);//指定点的颜色
	//计算Opengl坐标
	x = 2 * x / SCR_WDITH - 1;
	y = 2 * y / SCR_HEIGHT - 1;
	glBegin(GL_POINTS);//开始画点
	glVertex3f(x, y, 0); //绘制点
	glEnd();//结束画点
	return 0;
}
//在(x,y)点处  绘制颜色color
int drawPointInt(int x, int y, const Color color)
{
	return drawPoint((float)x, (float)y, color);
}

//画线
int drawLine(float x1, float y1, float x2, float y2, const Color color)
{
	x1 = 2 * x1 / SCR_WDITH - 1;
	y1 = 2 * y1 / SCR_HEIGHT - 1;

	x2 = 2 * x2 / SCR_WDITH - 1;
	y2 = 2 * y2 / SCR_HEIGHT - 1;

	glColor3f(color.r / 255, color.g / 255, color.b / 255);//指定颜色
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glEnd();

	return 0;
}

int drawLineInt(int x1, int y1, int x2, int y2, const Color color)
{
	return drawLine((float)x1, (float)y1, (float)x2, (float)y2, color);
}