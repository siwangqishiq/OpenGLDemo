#include "Geass.h"

//��ӡ3d��
void printPoint3D(const Point3D * pPoint3D)
{
	printf("%f %f %f \n", pPoint3D->x, pPoint3D->y, pPoint3D->z);
}

//��ӡ4d��
void printPoint4D(const Point4D * pPoint4D)
{
	printf("%f %f %f %f\n", pPoint4D->x, pPoint4D->y, pPoint4D->z, pPoint4D->w);
}


//�����ӡ
void printMatirx(const Matrix *pMatrix)
{
	printf("\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%5f  ",pMatrix->data[i][j]);
		}//end for j
		printf("\n");
	}//end for i
	printf("\n");
}

//Vector��ʾ
void printVector(Vector4D *pVect)
{
	printf("%5f  ", pVect->x);
	printf("%5f  ", pVect->y);
	printf("%5f  ", pVect->z);
	printf("%5f  ", pVect->w);
	printf("\n");
}

//src���� ������ distVector����
void vector4DCopy(Vector4D *srcVector, Vector4D *distVector)
{
	distVector->x = srcVector->x;
	distVector->y = srcVector->y;
	distVector->z = srcVector->z;
	distVector->w = srcVector->w;
}

//��4x4�������
int multiMatrix(Matrix *ret, const Matrix *left, const Matrix *right)
{
	if (ret == NULL || left == NULL || right == NULL)
	{
		return ERROR;
	}
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				float temp = left->data[i][k] * right->data[k][j];
				ret->data[i][j] += temp;
			}//end for k
		}//end for j
	}//end for i

	return SUCCESS;
}

//4D ������4X4������� ������ص�Ret��
int vectorMultiMatrix(Vector4D *pV, Matrix *pMatrix, Vector4D *pRet)
{
	pRet->x = pV->x * pMatrix->data[0][0] + pV->y* pMatrix->data[1][0] + pV->z* pMatrix->data[2][0]+ pV->w* pMatrix->data[3][0];
	pRet->y = pV->x * pMatrix->data[0][1] + pV->y* pMatrix->data[1][1] + pV->z* pMatrix->data[2][1] + pV->w* pMatrix->data[3][1];
	pRet->z = pV->x * pMatrix->data[0][2] + pV->y* pMatrix->data[1][2] + pV->z* pMatrix->data[2][2] + pV->w* pMatrix->data[3][2];
	pRet->w = pV->x * pMatrix->data[0][3] + pV->y* pMatrix->data[1][3] + pV->z* pMatrix->data[2][3] + pV->w* pMatrix->data[3][3];

	return SUCCESS;
}

//3D����4X4������� ������ص�Ret��
int vectorMultiMatrix(Point3D *pV, Matrix *pMatrix, Point3D *pRet)
{
	pRet->x = pV->x * pMatrix->data[0][0] + pV->y* pMatrix->data[1][0] + pV->z* pMatrix->data[2][0];
	pRet->y = pV->x * pMatrix->data[0][1] + pV->y* pMatrix->data[1][1] + pV->z* pMatrix->data[2][1];
	pRet->z = pV->x * pMatrix->data[0][2] + pV->y* pMatrix->data[1][2] + pV->z* pMatrix->data[2][2];

	return SUCCESS;
}

//4D����4X4������� ������ص�Ret��
int point4DMultiMatrix(Point4D *pV, Matrix *pMatrix, Point4D *pRet)
{
	pRet->x = pV->x * pMatrix->data[0][0] + pV->y* pMatrix->data[1][0] + pV->z* pMatrix->data[2][0] + pV->w* pMatrix->data[3][0];
	pRet->y = pV->x * pMatrix->data[0][1] + pV->y* pMatrix->data[1][1] + pV->z* pMatrix->data[2][1] + pV->w* pMatrix->data[3][1];
	pRet->z = pV->x * pMatrix->data[0][2] + pV->y* pMatrix->data[1][2] + pV->z* pMatrix->data[2][2] + pV->w* pMatrix->data[3][2];
	pRet->w = pV->x * pMatrix->data[0][3] + pV->y* pMatrix->data[1][3] + pV->z* pMatrix->data[2][3] + pV->w* pMatrix->data[3][3];

	return SUCCESS;
}

//��Ⱦ�б���� ָ������仯�����б�
void transformRenderList(RenderPolyList *pRendList, Matrix *pMatrix, int coordSelect)
{
	switch (coordSelect)
	{
	case TRANSFORM_LOCAL_ONLY://����ñ�������
		for (int i = 0; i < pRendList->numPolys; i++)
		{
			Poly1 *pPoly = pRendList->polyPtrs[i];
			if ((pPoly == NULL) ||
				!(pPoly->state & POLY_STATE_ACTIVE) ||
				(pPoly->state & POLY_STATE_CLIPPED) ||
				(pPoly->state & POLY_STATE_BACKFACE))
			{
				continue;
			}

			for (int vertex = 0; vertex < 3; vertex++)
			{
				Point4D result = {0};
				point4DMultiMatrix(&pPoly->local_points[vertex], pMatrix, &result);
				vector4DCopy(&pPoly->local_points[vertex], &result);
				//pPoly->pvList[vertex] = result;
			}//end for vertex
		}//end for i
		break;
	case TRANSFORM_TRANS_ONLY:
		for (int i = 0; i < pRendList->numPolys; i++)
		{
			Poly1 *pPoly = pRendList->polyPtrs[i];
			if ((pPoly == NULL) ||
				!(pPoly->state & POLY_STATE_ACTIVE) ||
				(pPoly->state & POLY_STATE_CLIPPED) ||
				(pPoly->state & POLY_STATE_BACKFACE))
			{
				continue;
			}

			for (int vertex = 0; vertex < 3; vertex++)
			{
				Point4D result = { 0 };
				point4DMultiMatrix(&pPoly->transform_points[vertex], pMatrix, &result);
				vector4DCopy(&pPoly->transform_points[vertex], &result);
				//pPoly->pvList[vertex] = result;
			}//end for vertex
		}//end for i
		break;
		break;
	case TRANSFORM_LOCAL_TO_TRANS:
		for (int i = 0; i < pRendList->numPolys; i++)
		{
			Poly1 *pPoly = pRendList->polyPtrs[i];
			if ((pPoly == NULL) ||
				!(pPoly->state & POLY_STATE_ACTIVE) ||
				(pPoly->state & POLY_STATE_CLIPPED) ||
				(pPoly->state & POLY_STATE_BACKFACE))
			{
				continue;
			}

			for (int vertex = 0; vertex < 3; vertex++)
			{
				point4DMultiMatrix(&pPoly->transform_points[vertex], 
					pMatrix, &pPoly->transform_points[vertex]);
				//pPoly->pvList[vertex] = result;
			}//end for vertex
		}//end for i
		break;
	}//end switch
}

//�������ݾ����ö����б���
//pObj ����ָ��
//pMatrix �任����ָ��
//coordSelect ָ��������������б��
//transformBasis �Ƿ�Գ����������б任
void transformObject(Object1 *pObj, Matrix *pMatrix, int coordSelect, int transformBasis)
{
	switch (coordSelect)
	{
	case TRANSFORM_LOCAL_ONLY: 
		for (int vIndex = 0; vIndex < pObj->numVertices; vIndex++)
		{
			Point4D result = { 0 };
			point4DMultiMatrix(&pObj->vList[vIndex], pMatrix, &result);
			vector4DCopy(&result, &pObj->vList[vIndex]);
		}//end for vIndex
		break;
	case TRANSFORM_TRANS_ONLY:
		for (int vIndex = 0; vIndex < pObj->numVertices; vIndex++)
		{
			Point4D result = { 0 };
			point4DMultiMatrix(&pObj->tvList[vIndex], pMatrix, &result);
			vector4DCopy(&result, &pObj->tvList[vIndex]);
		}//end for vIndex
		break;
	case TRANSFORM_LOCAL_TO_TRANS:
		for (int vIndex = 0; vIndex < pObj->numVertices; vIndex++)
		{
			Point4D result = { 0 };
			point4DMultiMatrix(&pObj->vList[vIndex], pMatrix, &pObj->tvList[vIndex]);
		}//end for vIndex
		break;
	}//end switch
}


