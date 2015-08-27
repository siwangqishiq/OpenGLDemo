#ifndef _LOADMODEL_H_
#define _LOADMODEL_H_

//载入model模块
#include "Geass.h"
#include <string.h>

#define SHOW_LOG 1;

#define   BUF_MAX      256

//掩码
#define   PLX_RGB_MASK             0x8000
#define   PLX_SHADE_MODE_MASK      0x6000
#define   PLX_2SIDED_MASK          0x1000
#define   PLX_COLOR_MASK           0x0fff

//颜色模式
#define   PLX_COLOR_MODE_RGB_FLAG         0x8000//RGB颜色模式
#define   PLX_COLOR_MODE_INDEXED_FLAG	  0x0000//索引颜色模式

//多边形是否为双面 
#define   PLX_2SIDED_FLAG     0x1000//双面
#define   PLX_1SIDED_FLAG     0x0000//单面

//着色模式
#define   PLX_SHADE_MODE_PURE_FLAG       0x0000//多边形使用固定颜色
#define   PLX_SHADE_MODE_FLAT_FLAG       0x2000//填充模式
#define   PLX_SHADE_MODE_GOURAUD_FLAG    0x4000//gouraud着色
#define   PLX_SHADE_MODE_PHONG_FLAG      0x8000//phong着色

//判断字符是否为空格 或 换行
int isspace(char c);
//读取PLG文件一行
char *readPlxFileLine(char *buffer,int maxLength,FILE *fp);

//加载PLX文件
int loadObjectPlg(Object1 *pObj, const char *filename,
	Vector4D *scale, Vector4D *pos, Vector4D *rotate);

//计算物体平均半径 及 最大半径
int computeObjectRadius(Object1 *obj);

#endif
