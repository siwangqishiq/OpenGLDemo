#include "GL/glut.h"

#include "Geass.h"


int init()
{
	glClearColor(1,1,1,1);
	//��Դ����

	return 0;
}

//������Ⱦ
void render()
{
	//�����ɫ��������������ɫ�� glClearColor( 0, 0.0, 0.0, 1 ); ָ��Ϊ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(2);//ָ����Ĵ�С
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