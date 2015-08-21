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

int isspace(char c)
{
	return c == 13 || c == 10 || c == 32;
}

//加载*.plx文件  到Object数据中
int loadObjectPlg(Object1 *pObj, const char *filename,
	Vector4D *scale, Vector4D *pos, Vector4D *rotate)
{

	return SUCCESS;
}

void main()
{
	char filename[128] = "assets/obj1_model.plg";
	Object1 cubeObj;
	memset(&cubeObj, 0, sizeof(Object1));

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
