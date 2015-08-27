#include "Geass.h"

//打印3d点
void printPoint3D(const Point3D * pPoint3D)
{
	printf("%f %f %f \n", pPoint3D->x, pPoint3D->y, pPoint3D->z);
}


//矩阵打印
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

//Vector显示
void printVector(Vector4D *pVect)
{
	printf("%5f  ", pVect->x);
	printf("%5f  ", pVect->y);
	printf("%5f  ", pVect->z);
	printf("%5f  ", pVect->w);
	printf("\n");
}

//两4x4矩阵相乘
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

//4D 向量与4X4矩阵相乘 结果返回到Ret中
int vectorMultiMatrix(Vector4D *pV, Matrix *pMatrix, Vector4D *pRet)
{
	pRet->x = pV->x * pMatrix->data[0][0] + pV->y* pMatrix->data[1][0] + pV->z* pMatrix->data[2][0]+ pV->w* pMatrix->data[3][0];
	pRet->y = pV->x * pMatrix->data[0][1] + pV->y* pMatrix->data[1][1] + pV->z* pMatrix->data[2][1] + pV->w* pMatrix->data[3][1];
	pRet->z = pV->x * pMatrix->data[0][2] + pV->y* pMatrix->data[1][2] + pV->z* pMatrix->data[2][2] + pV->w* pMatrix->data[3][2];
	pRet->w = pV->x * pMatrix->data[0][3] + pV->y* pMatrix->data[1][3] + pV->z* pMatrix->data[2][3] + pV->w* pMatrix->data[3][3];

	return SUCCESS;
}

//渲染列表根据 指定矩阵变化顶点列表
void transformRenderList(RenderPolyList *pRendList, Matrix *pMatrix, int coordSelect)
{
	switch (coordSelect)
	{
	case TRANSFORM_LOCAL_ONLY:
		break;
	case TRANSFORM_TRANS_ONLY:
		break;
	case TRANSFORM_LOCAL_TO_TRANS:
		break;
	}//end switch
}


