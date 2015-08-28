//载入model模块
#include "LoadModel.h"

//读取文件中的一行
char *readPlxFileLine(char *buffer, int maxLength, FILE *fp)
{
	int index = 0;//索引
	int length = 0;//长度
	
	while (1)
	{
		if (!fgets(buffer, maxLength, fp))//文件读取到末尾
		{
			return NULL;
		}

		//计算空格数
		for (length = strlen(buffer), index = 0; isspace(buffer[index]); index++);
		//printf("strlen-->%d   %d\n", strlen(buffer),index);
		if (index >= length || buffer[index] == '#')
			continue;
		return &buffer[index];
	}//end while
	
}

//判断字符是否为空格
int isspace(char c)
{
	return c == 13 || c == 10 || c == 32;
}

//计算物体最大包裹半径  及 平均半径
int computeObjectRadius(Object1 *obj)
{
	float totalRadius = 0;
	float maxRadius = 0;
	for (int i = 0; i < obj->numVertices; i++)
	{
		float r = sqrt((obj->vList[i].x)*(obj->vList[i].x) +
			(obj->vList[i].y)*(obj->vList[i].y) + (obj->vList[i].z)*(obj->vList[i].z));
		if (r>maxRadius)
		{
			maxRadius = r;
		}
		totalRadius += r;
	}//end for i
	obj->maxRadius = maxRadius;//
	obj->avgRadius = totalRadius / obj->numVertices;

	return SUCCESS;
}

//加载*.plx文件  到Object数据中
int loadObjectPlg(Object1 *obj, const char *filename,
	Vector4D *scale, Vector4D *pos, Vector4D *rotate)
{
	if (obj == NULL){
		printf("Obejct is NULL\n");
		return ERROR;
	}

	FILE *fp;//问价指针
	char buffer[BUF_MAX];//缓冲区
	char *token_string;

	memset(obj, 0, sizeof(Object1));//清空原有数据

	obj->state = OBJECT_STATE_ACTIVE | OBJECT_STATE_VISIBLE;//设置物体状态

	//设置物体位置 
	obj->worldPos.x = pos->x;
	obj->worldPos.y = pos->y;
	obj->worldPos.z = pos->z;
	obj->worldPos.w = pos->w;

	//打开文件
	if (!(fp = fopen(filename, "r")))
	{
		//文件打开失败
		printf("PLG file %s open error\n",filename);
		return ERROR;
	}

	//读取第一行描述
	if (!(token_string = readPlxFileLine(buffer, BUF_MAX, fp)))
	{
		printf("%s PLG file description error\n",filename);
		fclose(fp);//关闭文件
		return ERROR;
	}
	//printf("object description:%s \n",token_string);
	sscanf(token_string, "%s %d %d", obj->name, &obj->numVertices, &obj->numPolys);
	printf("\n object name: %s \nvertex num = %d  \npoly num = %d \n", 
		obj->name,obj->numVertices,obj->numPolys);
	//加载顶点列表
	for (int vIndex = 0; vIndex < obj->numVertices; vIndex++)
	{
		//读取列表行
		if (!(token_string = readPlxFileLine(buffer, BUF_MAX, fp)))
		{
			printf("read %s vertex list error\n", filename);
			fclose(fp);//关闭文件
			return ERROR;
		}
		//printf("object vertex:%s ", token_string);
		sscanf(token_string, "%f %f %f",
			&obj->vList[vIndex].x, &obj->vList[vIndex].y, &obj->vList[vIndex].z);

		obj->vList[vIndex].x *= scale->x;
		obj->vList[vIndex].y *= scale->y;
		obj->vList[vIndex].z *= scale->z;
		obj->vList[vIndex].w = 1;

		printf("\n vertex %d:%f %f %f", vIndex, obj->vList[vIndex].x, obj->vList[vIndex].y,
			obj->vList[vIndex].z);
	}//end for vIndex

	//计算半径
	computeObjectRadius(obj);
	printf("\n%s object max radius = %f     average radius = %f",obj->name,obj->maxRadius,obj->avgRadius);

	//加载多边形列表
	int poly_surface_desc = 0;//每个多边形的 多边形描述符
	int poly_vertex_num = 3;//多边形顶点个数
	char temp_desc[8];//多边形描述字符串
	for (int polyIndex = 0; polyIndex < obj->numPolys; polyIndex++)
	{
		//读取列表行
		if (!(token_string = readPlxFileLine(buffer, BUF_MAX, fp)))
		{
			printf("read %s poly list error\n", filename);
			fclose(fp);//关闭文件
			return ERROR;
		}
		//printf("%s",token_string);

		printf("\n Poly : %d",polyIndex);
		sscanf(token_string, "%s %d %d %d %d", temp_desc, &poly_vertex_num
			, &obj->pList[polyIndex].vIndex[0], &obj->pList[polyIndex].vIndex[1],
			&obj->pList[polyIndex].vIndex[2]);//变量赋值
		
		if (temp_desc[0] == '0' && temp_desc[1] == 'x')//16进制
		{
			sscanf(temp_desc,"%x",&poly_surface_desc);
		}
		else//10进制输入
		{
			poly_surface_desc = atoi(temp_desc);
		}//end if

		obj->pList[polyIndex].pvList = obj->vList;//多边形顶点列表设置为物体的顶点列表

		printf("\n Surface Desc = 0x%4x,num_vertex = %d,vert_inicates[%d %d %d]",
			poly_surface_desc, poly_vertex_num,
			obj->pList[polyIndex].vIndex[0], obj->pList[polyIndex].vIndex[1], obj->pList[polyIndex].vIndex[2]);
		
		//提取每个字段位  设置多边形属性
		if (poly_surface_desc & PLX_2SIDED_FLAG)
		{
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_2SIDED);
		}
		//printf("--->%4x",obj->pList[polyIndex].attr);

		//设置颜色模式
		if (poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG)
		{
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_RGB16);

			//提取r g b颜色值
			int red = ((poly_surface_desc & 0x0f00) >> 8);
			int green = ((poly_surface_desc & 0x00f0) >> 4);
			int blue = (poly_surface_desc & 0x000f);

			obj->pList[polyIndex].color = _RGB16BIT565(red * 16, green * 16, blue * 16);
			//printf("\n RGB color = [%d %d %d]",red,green,blue);
		}
		else//索引颜色模式
		{
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_8BITCOLOR);
			obj->pList[polyIndex].color = (poly_surface_desc & 0x00ff);
		}

		//设置着色模式
		int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);
		switch (shade_mode)
		{
		case PLX_SHADE_MODE_PURE_FLAG://固定着色
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_PURE);
			break;
		case PLX_SHADE_MODE_FLAT_FLAG://填充模式着色
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_FLAT);
			break;
		case PLX_SHADE_MODE_GOURAUD_FLAG://gouraud着色
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_GOURAUDE);
			break;
		case PLX_SHADE_MODE_PHONG_FLAG://phong着色
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_PHONG);
			break;
		default:
			break;
		}//end switch shade Mode

		obj->pList[polyIndex].state = POLY_STATE_ACTIVE;
	}//end for polyIndex

	fclose(fp);//关闭文件
	//printf("name:%s   vertex num:%d   polynum:%d \n",obj->name,obj->numVertices,obj->numPolys);

	return SUCCESS;
}

void main_load_test()
{
	

	/*
	FILE *fp = fopen(filename, "r");
	if (fp == NULL){
		printf("read file error %s \n",filename);
		system("pause");
		return;
	}
	char buffer[512];
	char *string = readPlgFileLine(buffer,512,fp);
	
	printf(":%s",string);
	string = readPlgFileLine(buffer, 512, fp);
	printf(":%s", string);
	string = readPlgFileLine(buffer, 512, fp);
	printf(":%s", string);


	fclose(fp);*/



	system("pause");
}
