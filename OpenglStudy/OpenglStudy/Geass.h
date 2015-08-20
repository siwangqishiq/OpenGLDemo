#ifndef _GEASS_H_
#define _GEASS_H_

#include <stdio.h>
#include <stdlib.h>

#include "DrawOpenGL.h"

#define SUCCESS      0
#define ERROR       -1

struct _Point3D{
	float x;
	float y;
	float z;
};

typedef struct _Point3D Point3D;

//4x4���� 
typedef struct{
	float data[4][4];
} Matrix;



//�ڿ���̨��ӡ3D������
void printPoint3D(const Point3D * pPoint3D);


//��ӡ����
void printMatirx(const Matrix *pMatrix);

//���������
int multiMatrix(Matrix *ret, const Matrix *left, const Matrix *right);

//4D��
typedef struct
{
	float x;
	float y;
	float z;
	float w;
} Point4D;

typedef Point4D Vector4D;

//���ڶ����б�Ķ����
//����νṹ��
struct Poly4DType_v1
{
	int state;//״̬��Ϣ
	int attr;//�������������
	int color;//�������ɫ

	Point4D *pvList;//�����б�
	int vIndex[3];//��������
};
typedef struct Poly4DType_v1 Poly1;

//�������� ���ݽṹ
struct PolyFace4DType_v1
{
	int state;//״̬��Ϣ
	int attr;//�������������
	int color;//�������ɫ

	Point4D vList[3];//ԭʼ��������
	Point4D tvList[3];//�任��Ķ�������

	struct PolyFace4DType_v1 *prev;//ǰһ�����ָ��
	struct PolyFace4DType_v1 *nexr;//��һ�����ָ��
};
typedef struct PolyFace4DType_v1 PolyFace1;

#define POLY4DV1_ATTR_2SIDED       0x0001
#define POLY4DV1_ATTR_TRANSPANT    0x0002

//v1  ����
#define OBJECT_MAX_VERTICES         1024//������ඥ�����
#define OBJECT_MAX_POLYS             512//����������θ���
struct Object_4D_V1_Type
{
	int id;//����Ψһ��ʾ
	char name[64];//��������
	int state;//����״̬
	int attr;//��������
	float   avgRadius;//ƽ���뾶
	float   maxRadius;//���뾶

	Point4D worldPos;//�����������е�λ��
	Vector4D dir;//�ھֲ������е���ת�Ƕ�
	Vector4D ux, uy, uz;//�ֲ������

	int numVertices;//�����������
	Point4D vList[OBJECT_MAX_VERTICES];//�ֲ�ԭʼ���궥���б�
	Point4D tvList[OBJECT_MAX_VERTICES];//�任��Ķ����б�
	int numPolys;//����θ���
	Poly1 pList[OBJECT_MAX_POLYS];//������б�
};
typedef struct Object_4D_V1_Type Object1;

#endif