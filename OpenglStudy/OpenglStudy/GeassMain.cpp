#include "GL/glut.h"

#include "Geass.h"


void test()
{
	Matrix m1 = { 0 };
	m1.data[0][0] = 1;
	m1.data[0][1] = 2;
	m1.data[0][2] = 3;
	m1.data[0][3] = 4;
	
	m1.data[1][0] = 1;
	m1.data[1][1] = 2;
	m1.data[1][2] = 3;
	m1.data[1][3] = 4;

	m1.data[2][0] = 1;
	m1.data[2][1] = 2;
	m1.data[2][2] = 3;
	m1.data[2][3] = 4;
	
	m1.data[3][0] = 1;
	m1.data[3][1] = 2;
	m1.data[3][2] = 3;
	m1.data[3][3] = 4;

	Matrix m2 = { 0 };
	m2.data[0][0] = 4;
	m2.data[0][1] = 3;
	m2.data[0][2] = 2;
	m2.data[0][3] = 1;
	
	m2.data[1][0] = 4;
	m2.data[1][1] = 3;
	m2.data[1][2] = 2;
	m2.data[1][3] = 1;
	
	m2.data[2][0] = 4;
	m2.data[2][1] = 3;
	m2.data[2][2] = 2;
	m2.data[2][3] = 1;
	
	m2.data[3][0] = 4;
	m2.data[3][1] = 3;
	m2.data[3][2] = 2;
	m2.data[3][3] = 1;

	printMatirx(&m1);
	printMatirx(&m2);

	Matrix m3 = {0};
	printMatirx(&m3);

	multiMatrix(&m3, &m1, &m2);

	printMatirx(&m3);
}

int init()
{
	test();

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