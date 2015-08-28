#define _CRT_SECURE_NO_WARNINGS

#ifndef _GEASS_H_
#define _GEASS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "DrawOpenGL.h"

#define SUCCESS      0
#define ERROR       -1

//����5 5 5��ʽ��16λ��ɫֵ
#define _RGB16BIT555(r,g,b)    ((b&31)+((g&31)<<5)+((r&31)<<10))

//����5 6 5��ʽ��16λ��ɫֵ
#define _RGB16BIT565(r,g,b)    ((b&31)+((g&63)<<5)+((r&31)<<11))

//����8 8 8��ʽ��24λ��ɫֵ
#define _RGB24BIT(a,r,g,b)	   ((b)+((g)<<8)+((r)<<18))

//����A 8 8 8��ʽ��32λ��ɫֵ
#define _RGB32BIT(a,r,g,b)	   ((b)+((g)<<8)+((r)<<16)+((a)<<24))

//λ����
#define SET_BIT(word,bit_flag)   ((word) = ((word)|(bit_flag)))
#define RESET_BIT(word,bit_flag)   ((word) = ((word)&(~bit_flag)))

//����xy֮��������
#define RAND_RANGE(x,y)   ((x)+(rand()%((y)-(x)+1)))

struct _Point3D{
	float x;
	float y;
	float z;
};

typedef struct _Point3D Point3D;
typedef Point3D Vector3D;

//4x4���� 
typedef struct{
	float data[4][4];
} Matrix;


//4D��
typedef struct
{
	float x;
	float y;
	float z;
	float w;
} Point4D;

//3Dƽ��
struct Plane3D_Type
{
	Point3D p0;
	Vector3D n;
};

typedef struct Plane3D_Type Plane3D;

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

	Point4D local_points[3];//�ڲ��洢��
	Point4D transform_points[3]; //��ú�ĵ�
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

#define   OBJECT_STATE_ACTIVE      0x0001//����״̬
#define   OBJECT_STATE_VISIBLE     0x0002//����Ϊ�ɼ�״̬

//�����������
#define  POLY_ATTR_2SIDED        0x0001

#define  POLY_ATTR_TRANSPANT     0x0002
#define  POLY_ATTR_8BITCOLOR     0x0004
#define  POLY_ATTR_RGB16         0x0008
#define  POLY_ATTR_RGB24         0x0010
//�������ɫģʽ
#define  POLY_ATTR_SHADE_MODE_PURE      0x0020
#define  POLY_ATTR_SHADE_MODE_FLAT      0x0040
#define  POLY_ATTR_SHADE_MODE_GOURAUDE  0x0080
#define  POLY_ATTR_SHADE_MODE_PHONG     0x0100

//�����״ֵ̬
#define  POLY_STATE_ACTIVE     0x0001
#define  POLY_STATE_CLIPPED    0x0002
#define  POLY_STATE_BACKFACE   0x0004


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

#define RENDER_LIST_MAX_NUM    400

//�������Ⱦ�б�
struct RenderPolyList_Type
{
	int state;//��Ⱦ�б�״̬
	int attr;//��Ⱦ�б�����
	Poly1 *polyPtrs[RENDER_LIST_MAX_NUM];//�����ָ���б�
	Poly1 polyData[RENDER_LIST_MAX_NUM];//����������б�
	int numPolys;//��Ⱦ�б��ڵĶ��������
};

typedef RenderPolyList_Type RenderPolyList;

//������ݽṹ
struct Camera_Type
{
	int state;//���״̬
	int attr;//�������
	Point4D pos;//��������������е�λ��
	Vector4D dir;//���ע�ӷ���
	//UVN��� ����
	Vector4D u;
	Vector4D v;
	Vector4D n;
	Point4D target;//Ŀ��λ��

	float viewDistH;//ˮƽ�Ӿ�
	float viewDistV;//��ֱ�Ӿ�
	float fov;//ˮƽ�����봹ֱ�������Ұ
	float near_clip_z;//���ü���
	float far_clip_z;//Զ�ü���

	float viewplane_width;//��ƽ��Ŀ�
	float viewplane_height;//��ƽ��ĸ�

	float viewport_width;//��ƽ��Ŀ��
	float viewport_height;//��ƽ��߶�
	float viewport_center_x;
	float viewport_center_y;

	float aspect_ratio;//��Ļ��߱�

	Plane3D right_clip_plane;//�Ҳü���
	Plane3D left_clip_plane;//��ü���
	Plane3D top_clip_plane;//�ϲü���
	Plane3D bottom_clip_plane;//�²ü���
	
	Matrix mcam;//�������굽�������ı任����
	Matrix mper;//������굽͸������ı任����
	Matrix mscr;//͸�����굽��Ļ����
};



//�ڿ���̨��ӡ3D������
void printPoint3D(const Point3D * pPoint3D);

//��ӡ4d��
void printPoint4D(const Point4D * pPoint4D);

//Vector��ʾ
void printVector(Vector4D *pVect);

//��ӡ����
void printMatirx(const Matrix *pMatrix);

//��4x4����ֵ
void setMatrixValues(Matrix *pM, float m00, float m01, float m02, float m03, 
								 float m10, float m11,float m12, float m13,
								 float m20, float m21, float m22, float m23,
								 float m30, float m31, float m32, float m33);

//src���� ������ distVector����
void vector4DCopy(Vector4D *srcVector, Vector4D *distVector);

//���������
int multiMatrix(Matrix *ret, const Matrix *left, const Matrix *right);

//4D ������4X4������� ������ص�Ret��
int vectorMultiMatrix(Vector4D *pV, Matrix *pMatrix, Vector4D *pRet);

//3D����4X4������� ������ص�Ret��
int point3DMultiMatrix(Point3D *pV, Matrix *pMatrix, Point3D *pRet);

//4D����4X4������� ������ص�Ret��
int point4DMultiMatrix(Point4D *pV, Matrix *pMatrix, Point3D *pRet);

//����ƽ�ƾ���
int buildTransformMatrix(const Vector4D *pPos, Matrix *pMt);

#define TRANSFORM_LOCAL_ONLY     1//���Ա���������б��
#define TRANSFORM_TRANS_ONLY     2//����Ա�ú������
#define TRANSFORM_LOCAL_TO_TRANS   3//��������תΪ�������

//��Ⱦ�б�
void transformRenderList(RenderPolyList *pRendList,Matrix *pMatrix,int coordSelect);

//�������ݾ����ö����б���
//pObj ����ָ��
//pMatrix �任����ָ��
//coordSelect ָ��������������б��
//transformBasis �Ƿ�Գ����������б任
void transformObject(Object1 *pObj, Matrix *pMatrix, int coordSelect,int transformBasis);

//ģ����������������ת��
void modelToWorldObject(Object1 *pObj,int coodSelct = TRANSFORM_LOCAL_TO_TRANS);

//ģ����������������ת�� ����任ʵ��
void modelToWorldObjectWithMatrix(Object1 *pObj, int coodSelct = TRANSFORM_LOCAL_TO_TRANS);

//��Ⱦ�б����� �ֲ�����ת��������
void modelToWorldRenderList(RenderPolyList *pRenderList);

#endif