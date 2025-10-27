#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;  //����
	struct Node* pNext;   //�����һ���ڵ�ĵ�ַ
	struct Node* pPre;    //�����һ���ڵ�ĵ�ַ
};

struct Node* g_pHead = NULL;    //��ʼ��ͷָ��
struct Node* g_pEnd = NULL;    //��ʼ��βָ��
int g_iNodeCount = 0;    //��¼�ڵ�����

//β���
void AddToEnd(int iData);
//�ͷ�����
void FreeList(void);
//�����������
void LookZheng(void);
//�����������
void LookFan(void);
//ͷ���
void AddToHead(int iData);
//ͨ���±����ָ������������
void InsertNodeByIndex(int iIndex, int Count, int iData);
//��ָ��������ǰ��������
void InsertNodeByData(int iValue, int iData);
//ͨ���±���ҽڵ�
struct Node* GetByIndex(int Index);
//ͨ�����ݲ��ҽڵ�
struct Node* GetByData(int iData);
//ͨ���±��޸Ľڵ�����
void ChangeByIndex(int iIndex,int iValue);
//ͨ�������޸Ľڵ�����
void ChangeByData(int iData,int iValue);
//ͨ���±�ɾ���ڵ�
void DeleteNodeByIndex(int iIndex);
//ɾ���ڵ�
void DeleteNode(struct Node* pTemp);
//ɾ��������ͬ���ݵĽڵ�
void DeleteNodeByData(int iValue);

int main(void)
{
	
	AddToEnd(1);
	AddToEnd(2);
	AddToEnd(3);
	InsertNodeByIndex(1, 2, 5);
	InsertNodeByIndex(0, 2, 9);
	InsertNodeByIndex(4, 2, 7);  // 6 9 9 1 5 7 7 5 2 3 4
	AddToHead(6);
	AddToEnd(4);
	InsertNodeByData(9,8);
	InsertNodeByData(6,10);
	InsertNodeByData(4,100);  // 10 6 8 9 9 1 5 7 7 5 2 3 100 4

	//DeleteNodeByIndex(3);

	DeleteNodeByData(2);
	

	/*ChangeByIndex(5,15);
	ChangeByData(9,10);*/

	/*struct Node* p1 = GetByIndex(15);
	struct Node* p2 = GetByData(0);*/

	LookZheng();
	LookFan();
	FreeList();
	system("pause>0");
	return 0;
}

//ɾ��������ͬ���ݵĽڵ�
void DeleteNodeByData(int iValue)
{
	struct Node* pTemp;
	while (NULL != (pTemp= GetByData(iValue)))
	{
		DeleteNode(pTemp);
	}
}

//ɾ���ڵ�
void DeleteNode(struct Node* pTemp)
{
	//ɾ������ͷ�ڵ�
	if (pTemp == g_pHead)
	{
		//ֻ��1���ڵ�
		if (g_iNodeCount == 1)
		{
			free(g_pHead);
			g_pHead = NULL;
			g_pEnd = NULL;
		}
		else    //����ڵ�
		{
			g_pHead = g_pHead->pNext;
			free(g_pHead->pPre);
			g_pHead->pPre = NULL;
		}
	}
	else if (pTemp == g_pEnd)    //ɾ��β�ڵ�
	{
		g_pEnd = g_pEnd->pPre;
		free(g_pEnd->pNext);
		g_pEnd->pNext = NULL;
	}
	else             //ɾ���м�
	{
		
		pTemp->pPre->pNext = pTemp->pNext;
		pTemp->pNext->pPre = pTemp->pPre;
		free(pTemp);
	}
	//�ڵ�����--
	g_iNodeCount--;
}

//ͨ���±�ɾ���ڵ�
void DeleteNodeByIndex(int iIndex)
{
	struct Node* pT= GetByIndex(iIndex);
	if (pT != NULL)
	{
		DeleteNode(pT);
	}
}

//ͨ�������޸Ľڵ�����
void ChangeByData(int iData1, int iValue)
{
	struct Node* p = GetByData(iData1);
	if (p != NULL)
	{
		p->iData = iValue;
	}
}

//ͨ���±��޸Ľڵ�����
void ChangeByIndex(int iIndex, int iValue)
{
	struct Node* p= GetByIndex(iIndex);
	if (p != NULL)
	{
		p->iData = iValue;
	}
}

//ͨ�����ݲ��ҽڵ�
struct Node* GetByData(int iData)
{
	//�����Ϸ��Լ��
	if (NULL == g_pHead || g_iNodeCount<=0)
	{
		return NULL;
	}
	struct Node* pTemp = g_pHead;
	while(pTemp!=NULL)
	{
		if (pTemp->iData == iData)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//ͨ���±���ҽڵ�
struct Node* GetByIndex(int Index)
{
	//�����Ϸ��Լ��
	if (NULL == g_pHead || Index < 0 || Index >= g_iNodeCount)
	{
		return NULL;
	}
	struct Node* pTemp = g_pHead;
	for (int i = 0; i < Index; i++)
	{
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//��ָ��������ǰ��������
void InsertNodeByData(int iValue, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == g_pHead)
	{
		return;
	}
	//�ҵ�ָ���Ľڵ�
	struct Node* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (pTemp->iData == iValue)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	//�ж��Ƿ��ҵ���
	if (pTemp != NULL)
	{
		//ͷ���
		if (pTemp == g_pHead)
		{
			AddToHead(iData);
		}
		//�м����(��Ϊ����ǰ���,���Բ�����β����������)
		else
		{
			//�����ڵ�
			struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
			if (pT != NULL)    //����ռ�ɹ�
			{
				//�ڵ��Ա��ֵ
				pT->iData = iData;
				pT->pNext = NULL;
				pT->pPre = NULL;

				//ǰһ���ڵ��봴���Ľڵ�����
				pTemp->pPre->pNext = pT;
				pT->pPre = pTemp->pPre;
				//�����Ľڵ������ݽڵ�����
				pT->pNext = pTemp;
				pTemp->pPre = pT;
				//�ڵ�����++
				g_iNodeCount++;
			}

		}
	}
}

//ͨ���±����ָ������������
void InsertNodeByIndex(int iIndex, int Count, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == g_pHead || iIndex < 0 || Count <= 0 || iIndex>g_iNodeCount)
	{
		return;
	}
	//�ҵ��ýڵ�
	struct Node* pTemp = g_pHead;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	//�ѽڵ�������������
	//ͷ���
	if (iIndex == 0)
	{
		for (int i = 0; i < Count; i++)
		{
			AddToHead(iData);
		}
	}
	//β���
	else if (iIndex == g_iNodeCount)
	{
		for (int i = 0; i < Count; i++)
		{
			AddToEnd(iData);
		}
	}
	else           //�м����
	{
		for (int i = 0; i < Count; i++)
		{
			//�����ڵ�
			struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
			if (pT != NULL)          //����ռ�ɹ�
			{
				//�ڵ��Ա��ֵ
				pT->iData = iData;
				pT->pNext = NULL;
				pT->pPre = NULL;

				//��������
				//��ǰһ���ڵ��봴���Ľڵ�����
				pTemp->pPre->pNext = pT;
				pT->pPre = pTemp->pPre;
				//�����Ľڵ���ָ���±�Ľڵ�����
				pT->pNext = pTemp;
				pTemp->pPre = pT;
			}
		}
		//����++
		g_iNodeCount += Count;
	}
}

//ͷ���
void AddToHead(int iData)
{
	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //�����ڴ�ռ�ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;

		//�ѽڵ�����������
		if (g_pHead == NULL)	//������
		{
			g_pHead = pTemp;
			g_pEnd = pTemp;
		}
		else
		{
			pTemp->pNext = g_pHead;
			g_pHead->pPre = pTemp;
			g_pHead = pTemp;
		}
		//�ڵ�����++
		g_iNodeCount++;
	}
}

//�����������
void LookFan(void)
{
	if (g_pHead == NULL)
	{
		return;
	}
	printf("����%d���ڵ�:", g_iNodeCount);
	//ѭ����������
	struct Node* pTemp = g_pEnd;
	while (pTemp != NULL)
	{
		printf("%d ", pTemp->iData);

		pTemp = pTemp->pPre;
	}
	putchar('\n');
}

//�����������
void LookZheng(void)
{
	if (g_pHead == NULL)
	{
		return;
	}
	printf("����%d���ڵ�:", g_iNodeCount);
	//ѭ����������
	struct Node* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		printf("%d ", pTemp->iData);

		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

//�ͷ�����
void FreeList(void)
{
	if (NULL == g_pHead)
	{
		return;
	}
	//�����м����
	struct Node* pTemp = g_pHead;
	//��������,����ͷ�
	while (pTemp != NULL)
	{
		//��¼��ǰ�ڵ�
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);
		g_iNodeCount = 0;//��ռ���
	}
	g_pHead = NULL;
	g_pEnd = NULL;
}

//β���
void AddToEnd(int iData)
{
	//�����Ϸ��Լ��
	if (g_iNodeCount < 0)
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
		if (g_pHead == NULL)
		{
			g_pHead = pTemp;
			g_pEnd = pTemp;
		}
		//���ǿ�����,ֱ��β���
		else
		{
			g_pEnd->pNext = pTemp;
			pTemp->pPre = g_pEnd;   //2�д�����˼Ϊǰ����,����ǰ
			g_pEnd = pTemp;  //βָ�����λ��
		}
		//�ڵ�����++;
		g_iNodeCount++;
	}
}