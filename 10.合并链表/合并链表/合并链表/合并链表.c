#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;  //����
	struct Node* pNext;   //�����һ���ڵ�ĵ�ַ
	struct Node* pPre;    //�����һ���ڵ�ĵ�ַ
};


//β���
void AddToEnd(struct Node** pHead,struct Node** pEnd,int* pCount,int iData);
//�ͷ�����
void FreeList(struct Node** pHead, struct Node** pEnd,int* pCount);
//�����������
void LookZheng(struct Node* pHead, int* pCount);
//ͷɾ��
struct Node* GetHead(struct Node** pHead, struct Node** pEnd, int* pCount);
//�ϲ�����
void HeBing(struct Node** g_A_pHead, struct Node** g_A_pEnd, int* g_A_iNodeCount, struct Node** g_B_pHead, struct Node** g_B_pEnd, int* g_B_iNodeCount);

int main(void)
{	
	struct Node* g_A_pHead = NULL;    //��ʼ��ͷָ��
	struct Node* g_A_pEnd = NULL;    //��ʼ��βָ��
	int g_A_iNodeCount = 0;    //��¼�ڵ�����

	struct Node* g_B_pHead = NULL;    //��ʼ��ͷָ��
	struct Node* g_B_pEnd = NULL;    //��ʼ��βָ��
	int g_B_iNodeCount = 0;    //��¼�ڵ�����

	//1 5 2 8 10
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 1);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 5);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 2);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 8);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 10);
	//2 6 9
	AddToEnd(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount, 2);
	AddToEnd(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount, 6);
	AddToEnd(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount, 9);

	HeBing(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, &g_B_pHead, &g_B_pEnd, &g_B_iNodeCount);

	LookZheng(g_A_pHead, &g_A_iNodeCount);
	LookZheng(g_B_pHead, &g_B_iNodeCount);

	FreeList(&g_A_pHead,&g_A_pEnd, &g_A_iNodeCount);
	FreeList(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount);

	system("pause>0");
	return 0;
}

//�ϲ�����
void HeBing(struct Node** g_A_pHead, struct Node** g_A_pEnd, int* g_A_iNodeCount, struct Node** g_B_pHead, struct Node** g_B_pEnd, int* g_B_iNodeCount)
{
	//�����Ϸ��Լ��
	if (NULL == g_A_pHead || NULL == *g_A_pHead || NULL == g_B_pHead || NULL == *g_B_pHead)
	{
		return;
	}
	while (1)
	{
		//��ȡA�����ͷ
		struct Node* pTemp= GetHead(g_A_pHead, g_A_pEnd, g_A_iNodeCount);
		if (pTemp == NULL)
		{
			break;
		}
		//��A������ȡ������ͷ�ڵ㰴�մ�С������B������
		//��Bͷ�ڵ�С(ͷ���)
		if (pTemp->iData <= (*g_B_pHead)->iData)
		{
			pTemp->pNext = *g_B_pHead;
			(*g_B_pHead)->pPre = pTemp;
			*g_B_pHead = pTemp;
			(*g_B_iNodeCount)++;
		}
		//��Bβ�ڵ��(β���)
		else if (pTemp->iData >= (*g_B_pEnd)->iData)
		{
			(*g_B_pEnd)->pNext = pTemp;
			pTemp->pPre = *g_B_pEnd;
			*g_B_pEnd = pTemp;
			(*g_B_pEnd)->pNext = NULL;
			(*g_B_iNodeCount)++;
		}
		else
		{
			struct Node* pT = *g_B_pHead;
			while (pT->pNext != NULL)
			{
				//�м�
				if (pTemp->iData >= pT->iData && pTemp->iData <= pT->pNext->iData)
				{
					//�½ڵ������ڵ�����
					pTemp->pNext = pT->pNext;
					pT->pNext->pPre = pTemp;
					//�½ڵ���ǰ��ڵ�����
					pT->pNext = pTemp;
					pTemp->pPre = pT;
					//�ڵ�����++
					(*g_B_iNodeCount)++;
					break;
				}
				pT = pT->pNext;
			}
		}
	}
}

//ͷɾ��
struct Node* GetHead(struct Node** pHead, struct Node** pEnd, int* pCount)
{
	//�����Ϸ��Լ��
	if (NULL == pHead || NULL == *pHead)
	{
		return NULL;
	}
	//��¼��ǰͷ�ڵ�
	struct Node* pTemp = *pHead;
	//ɾ��ͷ  
	if (*pHead == *pEnd)     //ֻ��һ���ڵ�
	{
		*pHead = NULL;
		*pEnd = NULL;
		(*pCount)--;
	}
	else
	{
		*pHead = (*pHead)->pNext;
		(*pCount)--;
	}
	return pTemp;
}

//�����������
void LookZheng(struct Node* pHead, int* pCount)
{
	if (pHead == NULL)
	{
		return;
	}
	printf("����%d���ڵ�:", *pCount);
	//ѭ����������
	struct Node* pTemp = pHead;
	while (pTemp != NULL)
	{
		printf("%d ", pTemp->iData);

		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

//�ͷ�����
void FreeList(struct Node** pHead, struct Node** pEnd, int* pCount)
{
	if (NULL == *pHead)
	{
		return;
	}
	//�����м����
	struct Node* pTemp = *pHead;
	//��������,����ͷ�
	while (pTemp != NULL)
	{
		//��¼��ǰ�ڵ�
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);
		*pCount = 0;//��ռ���
	}
	*pHead = NULL;
	*pEnd = NULL;
}

//β���
void AddToEnd(struct Node** pHead, struct Node** pEnd, int* pCount, int iData)
{
	//�����Ϸ��Լ��
	if (*pCount < 0)
	{
		return;
	}
	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)   //�����ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;

		//����ʱΪ������  //ǰ��ڵ���ǿ�,ͷβһ�����
		if (*pHead == NULL)
		{
			*pHead = pTemp;
			*pEnd = pTemp;
		}
		//���ǿ�����,ֱ��β���
		else
		{
			(*pEnd)->pNext = pTemp;
			pTemp->pPre = *pEnd;   //2�д�����˼Ϊǰ����,����ǰ
			*pEnd = pTemp;  //βָ�����λ��
		}
		//�ڵ�����++;
		(*pCount)++;
	}
}