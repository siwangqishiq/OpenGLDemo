#include "GL/glut.h"

#define SRC_WDITH       800
#define SRC_HEIGHT      600

void RenderScene()
{
	//清空颜色缓冲区，填充的颜色由 glClearColor( 0, 0.0, 0.0, 1 ); 指定为黑色

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);//指定点的大小，9个像素单位
	glColor3f(1.0f, 0.0f, 0.0f);//指定点的颜色
	glBegin(GL_POINTS);//开始画点
	{
		glVertex3f(0.0f, 0.0f, 0.0f); // 在坐标为(0,0,0)的地方绘制了一个点
	}
	glEnd();//结束画点

	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1);//以RGB(0,0,0)即黑色来清空颜色缓冲区

	glColor3f(1.0f, 0.0f, 0.0f);//以RGB(1,0,0)即红色来绘制图形

}


void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 200.0f;

	// Prevent a divide by zero

	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions

	glViewport(0, 0, w, h);

	// Reset projection matrix stack

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SRC_WDITH, SRC_HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Hello Point");
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 1;
}