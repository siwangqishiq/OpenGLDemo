//����modelģ��
#include "LoadModel.h"

//��ȡ�ļ��е�һ��
char *readPlxFileLine(char *buffer, int maxLength, FILE *fp)
{
	int index = 0;//����
	int length = 0;//����
	
	while (1)
	{
		if (!fgets(buffer, maxLength, fp))//�ļ���ȡ��ĩβ
		{
			return NULL;
		}

		//����ո���
		for (length = strlen(buffer), index = 0; isspace(buffer[index]); index++);
		//printf("strlen-->%d   %d\n", strlen(buffer),index);
		if (index >= length || buffer[index] == '#')
			continue;
		return &buffer[index];
	}//end while
	
}

//�ж��ַ��Ƿ�Ϊ�ո�
int isspace(char c)
{
	return c == 13 || c == 10 || c == 32;
}

//���������������뾶  �� ƽ���뾶
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

//����*.plx�ļ�  ��Object������
int loadObjectPlg(Object1 *obj, const char *filename,
	Vector4D *scale, Vector4D *pos, Vector4D *rotate)
{
	if (obj == NULL){
		printf("Obejct is NULL\n");
		return ERROR;
	}

	FILE *fp;//�ʼ�ָ��
	char buffer[BUF_MAX];//������
	char *token_string;

	memset(obj, 0, sizeof(Object1));//���ԭ������

	obj->state = OBJECT_STATE_ACTIVE | OBJECT_STATE_VISIBLE;//��������״̬

	//��������λ�� 
	obj->worldPos.x = pos->x;
	obj->worldPos.y = pos->y;
	obj->worldPos.z = pos->z;
	obj->worldPos.w = pos->w;

	//���ļ�
	if (!(fp = fopen(filename, "r")))
	{
		//�ļ���ʧ��
		printf("PLG file %s open error\n",filename);
		return ERROR;
	}

	//��ȡ��һ������
	if (!(token_string = readPlxFileLine(buffer, BUF_MAX, fp)))
	{
		printf("%s PLG file description error\n",filename);
		fclose(fp);//�ر��ļ�
		return ERROR;
	}
	//printf("object description:%s \n",token_string);
	sscanf(token_string, "%s %d %d", obj->name, &obj->numVertices, &obj->numPolys);
	printf("\n object name: %s \nvertex num = %d  \npoly num = %d \n", 
		obj->name,obj->numVertices,obj->numPolys);
	//���ض����б�
	for (int vIndex = 0; vIndex < obj->numVertices; vIndex++)
	{
		//��ȡ�б���
		if (!(token_string = readPlxFileLine(buffer, BUF_MAX, fp)))
		{
			printf("read %s vertex list error\n", filename);
			fclose(fp);//�ر��ļ�
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

	//����뾶
	computeObjectRadius(obj);
	printf("\n%s object max radius = %f     average radius = %f",obj->name,obj->maxRadius,obj->avgRadius);

	//���ض�����б�
	int poly_surface_desc = 0;//ÿ������ε� �����������
	int poly_vertex_num = 3;//����ζ������
	char temp_desc[8];//����������ַ���
	for (int polyIndex = 0; polyIndex < obj->numPolys; polyIndex++)
	{
		//��ȡ�б���
		if (!(token_string = readPlxFileLine(buffer, BUF_MAX, fp)))
		{
			printf("read %s poly list error\n", filename);
			fclose(fp);//�ر��ļ�
			return ERROR;
		}
		//printf("%s",token_string);

		printf("\n Poly : %d",polyIndex);
		sscanf(token_string, "%s %d %d %d %d", temp_desc, &poly_vertex_num
			, &obj->pList[polyIndex].vIndex[0], &obj->pList[polyIndex].vIndex[1],
			&obj->pList[polyIndex].vIndex[2]);//������ֵ
		
		if (temp_desc[0] == '0' && temp_desc[1] == 'x')//16����
		{
			sscanf(temp_desc,"%x",&poly_surface_desc);
		}
		else//10��������
		{
			poly_surface_desc = atoi(temp_desc);
		}//end if

		obj->pList[polyIndex].pvList = obj->vList;//����ζ����б�����Ϊ����Ķ����б�

		printf("\n Surface Desc = 0x%4x,num_vertex = %d,vert_inicates[%d %d %d]",
			poly_surface_desc, poly_vertex_num,
			obj->pList[polyIndex].vIndex[0], obj->pList[polyIndex].vIndex[1], obj->pList[polyIndex].vIndex[2]);
		
		//��ȡÿ���ֶ�λ  ���ö��������
		if (poly_surface_desc & PLX_2SIDED_FLAG)
		{
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_2SIDED);
		}
		//printf("--->%4x",obj->pList[polyIndex].attr);

		//������ɫģʽ
		if (poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG)
		{
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_RGB16);

			//��ȡr g b��ɫֵ
			int red = ((poly_surface_desc & 0x0f00) >> 8);
			int green = ((poly_surface_desc & 0x00f0) >> 4);
			int blue = (poly_surface_desc & 0x000f);

			obj->pList[polyIndex].color = _RGB16BIT565(red * 16, green * 16, blue * 16);
			//printf("\n RGB color = [%d %d %d]",red,green,blue);
		}
		else//������ɫģʽ
		{
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_8BITCOLOR);
			obj->pList[polyIndex].color = (poly_surface_desc & 0x00ff);
		}

		//������ɫģʽ
		int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);
		switch (shade_mode)
		{
		case PLX_SHADE_MODE_PURE_FLAG://�̶���ɫ
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_PURE);
			break;
		case PLX_SHADE_MODE_FLAT_FLAG://���ģʽ��ɫ
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_FLAT);
			break;
		case PLX_SHADE_MODE_GOURAUD_FLAG://gouraud��ɫ
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_GOURAUDE);
			break;
		case PLX_SHADE_MODE_PHONG_FLAG://phong��ɫ
			SET_BIT(obj->pList[polyIndex].attr, POLY_ATTR_SHADE_MODE_PHONG);
			break;
		default:
			break;
		}//end switch shade Mode

		obj->pList[polyIndex].state = POLY_STATE_ACTIVE;
	}//end for polyIndex

	fclose(fp);//�ر��ļ�
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
