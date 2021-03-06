#include "Geass.h"
#include "LoadModel.h"

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

void test2()
{
	Point4D pts[3] = { { 1, 1, 1, 1 }, { 1, 2, 3, 1 }, { 1, 2, 4, 1 } };
	
	Point4D *p = pts;
	p[2].x = 110;
	printf("%f %f %f %f", p[2].x, p[2].y, p[2].z, p[2].w);

}

void test3()
{
	Vector4D src = {1,2,3,1};
	Vector4D dst = {10,10,10,10};
	printVector(&src); 
	printVector(&dst);
	vector4DCopy(&src, &dst);
	printVector(&src);
	printVector(&dst);

}

//Matrix Test
void testTransfromMatrix()
{
	Matrix m1;
	setMatrixValues(&m1,1,2,3,4,
						1,2,3,4,
						2,3,4,5,
						1,2,3,4);

	printMatirx(&m1);

	Vector4D pos = {11,13,17,1};
	Matrix m2;
	buildTransformMatrix(&pos, &m2);
	printMatirx(&m2);


}

//全局变量
char filename[128] = "assets/obj1_model.plg";
Object1 cubeObj;


void testModelToWorld()
{
	printf("原来的顶点位置:\n");
	//printPoint4D(&cubeObj.worldPos);
	for (int i = 0; i < cubeObj.numVertices; i++)
	{
		printPoint4D(&cubeObj.tvList[i]);
	}//end for i
	modelToWorldObject(&cubeObj);
	printf("ModelToWorld后的顶点位置:\n");
	for (int i = 0; i < cubeObj.numVertices; i++)
	{
		printPoint4D(&cubeObj.tvList[i]);
	}//end for i
}

void testModelToWorldMatrix()
{
	printf("原来的顶点位置:\n");
	//printPoint4D(&cubeObj.worldPos);
	for (int i = 0; i < cubeObj.numVertices; i++)
	{
		printPoint4D(&cubeObj.tvList[i]);
	}//end for i

	modelToWorldObjectWithMatrix(&cubeObj);

	printf("ModelToWorld后的顶点位置:\n");
	for (int i = 0; i < cubeObj.numVertices; i++)
	{
		printPoint4D(&cubeObj.tvList[i]);
	}//end for i
}


int init()
{
	//test();			  
	//test2();			  
	Vector4D scale = { 1, 1, 1, 1 };
	Vector4D pos = { 100, 100, 100, 1 };
	Vector4D rotate = { 0, 0, 0, 1 };

	if (loadObjectPlg(&cubeObj, filename, &scale, &pos, &rotate) != SUCCESS){
		printf("\nread Object ERROR");
		return 0;
	}
	printf("\nread Object SUCCESS!\n");

	glClearColor(1,1,1,1);
	//资源载入
	//test3();
	//testTransfromMatrix();
	//testModelToWorld();
	testModelToWorldMatrix();
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

//处理输入
void handleKeyInput(unsigned char key, int x, int y)
{
	//printf("key is %d",key);
	if (key == 27){
		exit(0);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCR_WDITH, SCR_HEIGHT);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Hello World");
	glutDisplayFunc(render);
	glutKeyboardFunc(handleKeyInput);
	init();
	glutMainLoop();

	return 0;
}