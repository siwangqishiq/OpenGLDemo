#define _CRT_SECURE_NO_WARNINGS

#ifndef _GEASS_H_
#define _GEASS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "DrawOpenGL.h"

#define SUCCESS      0
#define ERROR       -1

//生成5 5 5格式的16位颜色值
#define _RGB16BIT555(r,g,b)    ((b&31)+((g&31)<<5)+((r&31)<<10))

//生成5 6 5格式的16位颜色值
#define _RGB16BIT565(r,g,b)    ((b&31)+((g&63)<<5)+((r&31)<<11))

//生成8 8 8格式的24位颜色值
#define _RGB24BIT(a,r,g,b)	   ((b)+((g)<<8)+((r)<<18))

//生成A 8 8 8格式的32位颜色值
#define _RGB32BIT(a,r,g,b)	   ((b)+((g)<<8)+((r)<<16)+((a)<<24))

//位运算
#define SET_BIT(word,bit_flag)   ((word) = ((word)|(bit_flag)))
#define RESET_BIT(word,bit_flag)   ((word) = ((word)&(~bit_flag)))

//产生xy之间的随机数
#define RAND_RANGE(x,y)   ((x)+(rand()%((y)-(x)+1)))

struct _Point3D{
	float x;
	float y;
	float z;
};

typedef struct _Point3D Point3D;
typedef Point3D Vector3D;

//4x4矩阵 
typedef struct{
	float data[4][4];
} Matrix;


//4D点
typedef struct
{
	float x;
	float y;
	float z;
	float w;
} Point4D;

//3D平面
struct Plane3D_Type
{
	Point3D p0;
	Vector3D n;
};

typedef struct Plane3D_Type Plane3D;

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

	Point4D local_points[3];//内部存储点
	Point4D transform_points[3]; //变幻后的点
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

#define   OBJECT_STATE_ACTIVE      0x0001//激活状态
#define   OBJECT_STATE_VISIBLE     0x0002//物体为可见状态

//多边形面属性
#define  POLY_ATTR_2SIDED        0x0001

#define  POLY_ATTR_TRANSPANT     0x0002
#define  POLY_ATTR_8BITCOLOR     0x0004
#define  POLY_ATTR_RGB16         0x0008
#define  POLY_ATTR_RGB24         0x0010
//多边形着色模式
#define  POLY_ATTR_SHADE_MODE_PURE      0x0020
#define  POLY_ATTR_SHADE_MODE_FLAT      0x0040
#define  POLY_ATTR_SHADE_MODE_GOURAUDE  0x0080
#define  POLY_ATTR_SHADE_MODE_PHONG     0x0100

//多边形状态值
#define  POLY_STATE_ACTIVE     0x0001
#define  POLY_STATE_CLIPPED    0x0002
#define  POLY_STATE_BACKFACE   0x0004


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

#define RENDER_LIST_MAX_NUM    400

//多边形渲染列表
struct RenderPolyList_Type
{
	int state;//渲染列表状态
	int attr;//渲染列表属性
	Poly1 *polyPtrs[RENDER_LIST_MAX_NUM];//多边形指针列表
	Poly1 polyData[RENDER_LIST_MAX_NUM];//多边形数据列表
	int numPolys;//渲染列表内的多边形数量
};

typedef RenderPolyList_Type RenderPolyList;

//相机数据结构
struct Camera_Type
{
	int state;//相机状态
	int attr;//相机属性
	Point4D pos;//相机在世界坐标中的位置
	Vector4D dir;//相机注视方向
	//UVN相机 参数
	Vector4D u;
	Vector4D v;
	Vector4D n;
	Point4D target;//目标位置

	float viewDistH;//水平视距
	float viewDistV;//垂直视距
	float fov;//水平方向与垂直方向的视野
	float near_clip_z;//近裁剪面
	float far_clip_z;//远裁剪面

	float viewplane_width;//视平面的宽
	float viewplane_height;//视平面的高

	float viewport_width;//视平面的宽度
	float viewport_height;//视平面高度
	float viewport_center_x;
	float viewport_center_y;

	float aspect_ratio;//屏幕宽高比

	Plane3D right_clip_plane;//右裁剪面
	Plane3D left_clip_plane;//左裁剪面
	Plane3D top_clip_plane;//上裁剪面
	Plane3D bottom_clip_plane;//下裁剪面
	
	Matrix mcam;//世界坐标到相机坐标的变换矩阵
	Matrix mper;//相机坐标到透视坐标的变换矩阵
	Matrix mscr;//透视坐标到屏幕坐标
};



//在控制台打印3D点坐标
void printPoint3D(const Point3D * pPoint3D);

//打印4d点
void printPoint4D(const Point4D * pPoint4D);

//Vector显示
void printVector(Vector4D *pVect);

//打印矩阵
void printMatirx(const Matrix *pMatrix);

//给4x4矩阵赋值
void setMatrixValues(Matrix *pM, float m00, float m01, float m02, float m03, 
								 float m10, float m11,float m12, float m13,
								 float m20, float m21, float m22, float m23,
								 float m30, float m31, float m32, float m33);

//src向量 拷贝到 distVector向量
void vector4DCopy(Vector4D *srcVector, Vector4D *distVector);

//两矩阵相乘
int multiMatrix(Matrix *ret, const Matrix *left, const Matrix *right);

//4D 向量与4X4矩阵相乘 结果返回到Ret中
int vectorMultiMatrix(Vector4D *pV, Matrix *pMatrix, Vector4D *pRet);

//3D点与4X4矩阵相乘 结果返回到Ret中
int point3DMultiMatrix(Point3D *pV, Matrix *pMatrix, Point3D *pRet);

//4D点与4X4矩阵相乘 结果返回到Ret中
int point4DMultiMatrix(Point4D *pV, Matrix *pMatrix, Point3D *pRet);

//构建平移矩阵
int buildTransformMatrix(const Vector4D *pPos, Matrix *pMt);

#define TRANSFORM_LOCAL_ONLY     1//仅对本地坐标进行变幻
#define TRANSFORM_TRANS_ONLY     2//仅针对变幻后的坐标
#define TRANSFORM_LOCAL_TO_TRANS   3//本地坐标转为变幻坐标

//渲染列表
void transformRenderList(RenderPolyList *pRendList,Matrix *pMatrix,int coordSelect);

//物体依据矩阵变幻顶点列表函数
//pObj 物体指针
//pMatrix 变换矩阵指针
//coordSelect 指定对哪种坐标进行变幻
//transformBasis 是否对朝向向量进行变换
void transformObject(Object1 *pObj, Matrix *pMatrix, int coordSelect,int transformBasis);

//模型坐标向世界坐标转换
void modelToWorldObject(Object1 *pObj,int coodSelct = TRANSFORM_LOCAL_TO_TRANS);

//模型坐标向世界坐标转换 矩阵变换实现
void modelToWorldObjectWithMatrix(Object1 *pObj, int coodSelct = TRANSFORM_LOCAL_TO_TRANS);

//渲染列表多边形 局部坐标转世界坐标
void modelToWorldRenderList(RenderPolyList *pRenderList);

#endif