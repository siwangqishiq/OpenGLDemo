#include "GL/glut.h"
#include <math.h>
#include <stdio.h>

// Rotation amounts

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SpecialKeys(int key, int x, int y);
void ChangeSize2(GLsizei w, GLsizei h);
void DrawAxis();
void SetupRC2();

void RenderScene2()
{
	//�����ɫ��������������ɫ�� glClearColor( 0, 0.0, 0.0, 1 ); ָ��Ϊ��ɫ

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save matrix state and do the rotation

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	DrawAxis();


	//����̫��

	glColor3f(1.0f, 1.0f, 1.0f);//��ɫ

	glutSolidSphere(50.f, 15, 15);

	//���Ƶ���

	static GLfloat earthAngle = 0;
	const GLfloat RADIUS = 100.f;
	glRotatef(earthAngle, 0, 0, 1);
	glTranslatef(RADIUS, RADIUS, 0);
	glColor3f(0.0f, 1.0f, 0.0f);//��ɫ

	glutSolidSphere(20.f, 15, 15);

	// ���ƻ�ɫ�ġ�������

	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(earthAngle / 30.0*360.0 - earthAngle / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(RADIUS / 2, 0.0f, 0.0f);
	glutSolidSphere(7, 20, 20);

	earthAngle += 1;
	if (earthAngle >= 360)
	{
		earthAngle -= 360;
	}

	printf("Angle:%f\n", earthAngle);

	// Restore transformations

	glPopMatrix();

	glutSwapBuffers();
}

int main_drawrect(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Triangles Example");
	glutDisplayFunc(RenderScene2);
	glutIdleFunc(RenderScene2); //glutIdleFunc ��ʾ��CPU���е�ʱ�����ĳһ����

	glutReshapeFunc(ChangeSize2);
	glutSpecialFunc(SpecialKeys);
	SetupRC2();
	glutMainLoop();

	return 1;
}


void SetupRC2()
{
	glClearColor(0, 0.0, 0.0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);//����ס�Ĳ��ֲ�����

}


void ChangeSize2(GLsizei w, GLsizei h)
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

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (xRot > 356.0f)
		xRot = 0.0f;

	if (xRot < -1.0f)
		xRot = 355.0f;

	if (yRot > 356.0f)
		yRot = 0.0f;

	if (yRot < -1.0f)
		yRot = 355.0f;

	// Refresh the Window

	glutPostRedisplay();// this will refresh the window, so, it works the same to call RenderScene() directly 

}


void DrawAxis()
{
	//����x��y��z������

	{
		glColor3f(0.0f, 0.0f, 1.0f);//ָ���ߵ���ɫ,��ɫ

		glBegin(GL_LINES);
		{
			// x-axis

			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(200.0f, 0.0f, 0.0f);

			// x-axis arrow

			glVertex3f(200.0f, 0.0f, 0.0f);
			glVertex3f(193.0f, 3.0f, 0.0f);
			glVertex3f(200.0f, 0.0f, 0.0f);
			glVertex3f(193.0f, -3.0f, 0.0f);
		}
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);//ָ���ߵ���ɫ,��ɫ

		glBegin(GL_LINES);
		{
			// y-axis

			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 200.0f, 0.0f);
			glVertex3f(0.0f, 200.0f, 0.0f);
			glVertex3f(3.0f, 193.0f, 0.0f);
			glVertex3f(0.0f, 200.0f, 0.0f);
			glVertex3f(-3.0f, 193.0f, 0.0f);
		}
		glEnd();


		glColor3f(1.0f, 0.0f, 0.0f);//ָ���ߵ���ɫ,��ɫ

		glBegin(GL_LINES);
		{
			// z-axis

			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 200.0f);
			glVertex3f(0.0f, 0.0f, 200.0f);
			glVertex3f(0.0f, 3.0f, 193.0f);
			glVertex3f(0.0f, 0.0f, 200.0f);
			glVertex3f(0.0f, -3.0f, 193.0f);
		}
		glEnd();
	}
}