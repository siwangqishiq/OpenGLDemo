#include <gl\glut.h>  
#include <stdio.h>


#define SCREEN_WIDTH     800
#define SCREEN_HEIGHT    800

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	printf("Hello OpenGL\n");
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);//窗口出现位置
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);//窗口大小
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();

	return 0;
}
