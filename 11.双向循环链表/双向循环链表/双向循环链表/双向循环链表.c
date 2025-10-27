#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;
	struct Node* pNext;
	struct Node* pPre;
};

//β���
void AddToEnd(struct Node* stHead, int* pCount, int iData);
//��������
void Look(struct Node* stHead, int* pCount);
//�ͷ�����
void FreeList(struct Node* stHead, int* pCount);
//ͷ���
void AddToHead(struct Node* stHead, int* pCount, int iData);
//�����±���ҽڵ�
struct Node* GetNodeByIndex(struct Node* stHead, int* pCount, int iIndex);
//�������ݲ��ҽڵ�
struct Node* GetNodeByData(struct Node* stHead,int iData);
//ͨ���±���ָ��λ�ò���һ���ڵ�
void InsertByIndex(struct Node* stHead, int* pCount, int iIndex, int iData);
//ͨ��������ָ��λ�ò���һ���ڵ�
void InsertByData(struct Node* stHead, int* pCount, int iValue, int iData);
//ͨ���±���ָ��λ�ò������ڵ�
void InsertSomeByIndex(struct Node* stHead, int* pCount, int iIndex, int iData,int iNodeCount);
//�����±�ɾ��ָ���ڵ�
void DeleteByIndex(struct Node* stHead, int* pCount, int iIndex);
//�����±�ɾ��ָ����Χ�Ľڵ�
void DeleteSomeByIndex(struct Node* stHead, int* pCount, int iIndex1, int iIndex2);
//��������ɾ��ָ���ڵ�
void DeleteByData(struct Node* stHead, int* pCount, int iData);
//ɾ����ͬ���ݵĽڵ�
void DeleteSameByData(struct Node* stHead, int* pCount, int iData);

//�п�ͷ˫��ѭ������
int main(void)
{
	struct Node stHead;
	stHead.iData = 0;
	stHead.pNext = &stHead;
	stHead.pPre = &stHead;
	int iCount = 0;

	AddToEnd(&stHead, &iCount, 1);
	AddToEnd(&stHead, &iCount, 2);
	AddToEnd(&stHead, &iCount, 3);
	AddToEnd(&stHead, &iCount, 4);

	/*InsertSomeByIndex(&stHead, &iCount, 1, 5, 5);*/

	//DeleteSameByData(&stHead, &iCount,3);

	/*DeleteByData(&stHead, &iCount,1);*/

	//DeleteSomeByIndex(&stHead, &iCount, 1, 3);

	/*DeleteByIndex(&stHead, &iCount, 3);*/

	/*InsertSomeByIndex(&stHead, &iCount,1,9,3);*/

	//InsertByIndex(&stHead,&iCount,4,5);
	//InsertByData(&stHead, &iCount,1,5);


	/*struct Node* pT = GetNodeByIndex(&stHead, &iCount, 2);
	pT = GetNodeByData(&stHead,5);*/
	/*AddToHead(&stHead, &iCount, 5);
	AddToHead(&stHead, &iCount, 6);*/

	Look(&stHead,&iCount);

	FreeList(&stHead, &iCount);

	system("pause>0");
	return 0;
}

//ɾ����ͬ���ݵĽڵ�
void DeleteSameByData(struct Node* stHead, int* pCount, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || *pCount <= 0)
	{
		return;
	}
	
	while (1)
	{
		//�ҵ��ýڵ�
		struct Node* pTemp = GetNodeByData(stHead, iData);

		if (pTemp == NULL)
		{
			return;
		}
		//ɾ���ڵ�
		pTemp->pPre->pNext = pTemp->pNext;
		pTemp->pNext->pPre = pTemp->pPre;
		free(pTemp);
		(*pCount)--;
	}
}

//��������ɾ��ָ���ڵ�
void DeleteByData(struct Node* stHead, int* pCount, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || *pCount <= 0)
	{
		return;
	}
	//�ҵ��ýڵ�
	struct Node* pTemp= GetNodeByData(stHead,iData);
	if (pTemp == NULL)
	{
		return;
	}
	//ɾ���ڵ�
	pTemp->pPre->pNext = pTemp->pNext;
	pTemp->pNext->pPre = pTemp->pPre;
	free(pTemp);
	(*pCount)--;
}

//�����±�ɾ��ָ����Χ�Ľڵ�
void DeleteSomeByIndex(struct Node* stHead, int* pCount, int iIndex1, int iIndex2)
{
	for (int i = iIndex1; i <= iIndex2; i++)
	{
		DeleteByIndex(stHead,pCount,iIndex1);
	}
}

//�����±�ɾ��ָ���ڵ�
void DeleteByIndex(struct Node* stHead, int* pCount, int iIndex)
{
	//���ò��Һ����Ѿ����в����Ϸ��Լ��,������ﲻд��
	//�ҵ��ýڵ�
	struct Node* pTemp= GetNodeByIndex(stHead,pCount,iIndex);
	if (pTemp == NULL)
	{
		return;
	}
	//ɾ��
	pTemp->pPre->pNext = pTemp->pNext;
	pTemp->pNext->pPre = pTemp->pPre;
	free(pTemp);
	(*pCount)--;
}

//ͨ���±���ָ��λ�ò������ڵ�
void InsertSomeByIndex(struct Node* stHead, int* pCount, int iIndex, int iData, int iNodeCount)
{
	for (int i = 0; i <iNodeCount; i++)
	{
		InsertByIndex(stHead,pCount,iIndex,iData);
	}
}

//ͨ��������ָ��λ�ò���һ���ڵ�
void InsertByData(struct Node* stHead, int* pCount, int iValue, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->pNext == stHead || *pCount <= 0)
	{
		return;
	}
	struct Node* pTemp= GetNodeByData(stHead, iValue);
	if (pTemp == NULL)
	{
		return;
	}
	else
	{
		//�����ڵ�
		struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
		if (pT != NULL)		//����ռ�ɹ�
		{
			//�ڵ��Ա��ֵ
			pT->iData = iData;
			pT->pNext = NULL;
			pT->pPre = NULL;
			//�½ڵ�����������
			pT->pNext = pTemp;
			pT->pPre = pTemp->pPre;
			pTemp->pPre->pNext = pT;
			pTemp->pPre = pT;
			//�ڵ�����++
			(*pCount)++;
		}
	}
}

//ͨ���±���ָ��λ�ò���һ���ڵ�
void InsertByIndex(struct Node* stHead, int* pCount, int iIndex, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->pNext == NULL || iIndex<0 || iIndex>(*pCount))
	{
		return;
	}
	//�����Ϸ��Լ���Ѿ���֤��һ���ܹ��ҵ��ýڵ�
	struct Node* pTemp= GetNodeByIndex(stHead,pCount,iIndex);
	if (iIndex == *pCount)
	{
		AddToEnd(stHead, pCount, iData);
	}
	else
	{
		//�����ڵ�
		struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
		if (pT != NULL)     //����ռ�ɹ�
		{
			//�ڵ��Ա��ֵ
			pT->iData = iData;
			pT->pNext = NULL;
			pT->pPre = NULL;
			//�½ڵ����ӵ�������
			pT->pNext = pTemp;
			pT->pPre = pTemp->pPre;
			pTemp->pPre->pNext = pT;
			pTemp->pPre = pT;
			//�ڵ�����++
			(*pCount)++;
		}
	}
}

//�������ݲ��ҽڵ�
struct Node* GetNodeByData(struct Node* stHead, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->pNext == stHead)
	{
		return NULL;
	}
	//��������
	struct Node* pTemp = stHead->pNext;
	while (pTemp != stHead)
	{
		if (pTemp->iData == iData)
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
}

//�����±���ҽڵ�
struct Node* GetNodeByIndex(struct Node* stHead, int* pCount, int iIndex)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->pNext == stHead || *pCount <= 0 || iIndex<0 || iIndex >= (*pCount))
	{
		return NULL; 
	}
	//��������
	struct Node* pTemp = stHead->pNext;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//ͷ���
void AddToHead(struct Node* stHead, int* pCount, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead)
	{
		return;
	}
	//��������
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //����ռ�ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;
		//���½ڵ�����������
		pTemp->pNext = stHead->pNext;
		pTemp->pPre = stHead;
		stHead->pNext->pPre = pTemp;
		stHead->pNext = pTemp;
		//����++
		(*pCount)++;
	}
}

//�ͷ�����
void FreeList(struct Node* stHead, int* pCount)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->pNext == stHead)  //����˵���޽ڵ�
	{
		return;
	}
	struct Node* pTemp = stHead->pNext;
	while (pTemp != stHead)
	{
		//��¼��ǰ�ڵ�
		struct Node* pT = pTemp;
		//������һ��
		pTemp = pTemp->pNext;
		//�ͷŵ�ǰ�ڵ�
		free(pT);
	}
	*pCount = 0;
	stHead->pNext = stHead;
	stHead->pPre = stHead;
}

//��������
void Look(struct Node* stHead, int* pCount)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->pNext == stHead)  //����˵���޽ڵ�
	{
		return;
	}
	printf("����%d���ڵ�: ", *pCount);
	struct Node* pTemp = stHead->pNext;
	while (pTemp != stHead)
	{
		printf("%d  ",pTemp->iData);
		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

//β���
void AddToEnd(struct Node* stHead, int* pCount, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead)
	{
		return;
	}
	//��������
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //����ռ�ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;
		//���½ڵ�����������
		pTemp->pPre = stHead->pPre;
		pTemp->pNext = stHead;
		stHead->pPre->pNext = pTemp;
		stHead->pPre = pTemp;
		//����++
		(*pCount)++;
	}
}