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

//4x4矩阵 
typedef struct{
	float data[4][4];
} Matrix;



//在控制台打印3D点坐标
void printPoint3D(const Point3D * pPoint3D);


//打印矩阵
void printMatirx(const Matrix *pMatrix);

//两矩阵相乘
int multiMatrix(Matrix *ret, const Matrix *left, const Matrix *right);

//4D点
typedef struct
{
	float x;
	float y;
	float z;
	float w;
} Point4D;

typedef Point4D Vector4D;

//基于顶点列表的多边形
//多边形结构体
struct Poly4DType_v1
{
	int state;//状态信息
	int attr;//多边形物理属性
	int color;//多边形颜色

	Point4D *pvList;//顶点列表
	int vIndex[3];//顶点索引
};
typedef struct Poly4DType_v1 Poly1;

//三角形面 数据结构
struct PolyFace4DType_v1
{
	int state;//状态信息
	int attr;//多边形物理属性
	int color;//多边形颜色

	Point4D vList[3];//原始顶点数据
	Point4D tvList[3];//变换后的顶点数据

	struct PolyFace4DType_v1 *prev;//前一个结点指针
	struct PolyFace4DType_v1 *nexr;//后一个结点指针
};
typedef struct PolyFace4DType_v1 PolyFace1;

#define POLY4DV1_ATTR_2SIDED       0x0001
#define POLY4DV1_ATTR_TRANSPANT    0x0002

//v1  物体
#define OBJECT_MAX_VERTICES         1024//物体最多顶点个数
#define OBJECT_MAX_POLYS             512//物体最多多边形个数
struct Object_4D_V1_Type
{
	int id;//物体唯一标示
	char name[64];//物体名称
	int state;//物体状态
	int attr;//物体属性
	float   avgRadius;//平均半径
	float   maxRadius;//最大半径

	Point4D worldPos;//在世界坐标中的位置
	Vector4D dir;//在局部坐标中的旋转角度
	Vector4D ux, uy, uz;//局部坐标抽

	int numVertices;//包含顶点个数
	Point4D vList[OBJECT_MAX_VERTICES];//局部原始坐标顶点列表
	Point4D tvList[OBJECT_MAX_VERTICES];//变换后的顶点列表
	int numPolys;//多边形个数
	Poly1 pList[OBJECT_MAX_POLYS];//多边形列表
};
typedef struct Object_4D_V1_Type Object1;

#endif