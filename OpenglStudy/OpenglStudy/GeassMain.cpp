#include "GL/glut.h"

#include "Geass.h"


int init()
{
	glClearColor(1,1,1,1);
	//资源载入

	return 0;
}

//画面渲染
void render()
{
	//清空颜色缓冲区，填充的颜色由 glClearColor( 0, 0.0, 0.0, 1 ); 指定为黑色
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(2);//指定点的大小
	Color color = {0,0,255};
	
	drawLine(0, 0, 100, 100,color);

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCR_WDITH, SCR_HEIGHT);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Hello World");
	glutDisplayFunc(render);
	init();
	glutMainLoop();
	return 1;
}