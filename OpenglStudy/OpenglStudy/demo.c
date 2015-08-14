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
	glutInitWindowPosition(100, 100);//���ڳ���λ��
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);//���ڴ�С
	glutCreateWindow("��һ��OpenGL����");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();

	return 0;
}
