#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

struct Node
{
	int iData;
	struct Node* pNext;
	struct Node* pPre;
};

//��������    //ͷ���,βɾ��
struct Node* Queue();
//�ж϶����Ƿ�Ϊ��
bool IsEmpty(struct Node* pQueue);
//�ҵ���ͷ
struct Node* Front(struct Node* pQueue);
//�ҵ���β
struct Node* Back(struct Node* pQueue);
//ͷ���
void Push(struct Node* pQueue, int iData);
//βɾ��
void Pop(struct Node* pQueue);
//�ͷŶ���
void FreeQueue(struct Node** pQueue);

int main(void)
{
	struct Node* pQueue= Queue();

	Push(pQueue, 1);
	Push(pQueue, 2);
	Push(pQueue, 3);
	Push(pQueue, 4);
	Push(pQueue, 5);

	Pop(pQueue);

	FreeQueue(&pQueue);
	
	system("pause>0");
	return 0;
}

//�ͷŶ���
void FreeQueue(struct Node** pQueue)
{
	if (IsEmpty(*pQueue))
	{
		free(*pQueue);
		*pQueue = NULL;
		return;
	}

	struct Node* pTemp = *pQueue;
	do
	{
		//��¼��ǰ�ڵ�
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext; //������һ��
		free(pT); //�ͷŵ�ǰ�ڵ�
		
	} while (pTemp!=(*pQueue));
	*pQueue = NULL;
}

//βɾ��
void Pop(struct Node* pQueue)
{
	if (IsEmpty(pQueue))
	{
		return;
	}
	//��¼Ҫɾ���Ľڵ�
	struct Node* pTemp = pQueue->pPre;
	pTemp->pPre->pNext = pQueue;
	pQueue->pPre = pTemp->pPre;
	free(pTemp);
}

//ͷ���
void Push(struct Node* pQueue, int iData)
{
	if (NULL == pQueue)
	{
		return;
	}

	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));

	if (pTemp == NULL)
	{
		return;
	}
	//�ڵ��Ա��ֵ
	pTemp->iData = iData;
	pTemp->pNext = NULL;
	pTemp->pPre = NULL;
	//�½ڵ����ӵ�������
	pTemp->pNext = pQueue->pNext;
	pTemp->pPre = pQueue;

	pQueue->pNext->pPre = pTemp;
	pQueue->pNext = pTemp;
}

//�ҵ���ͷ
struct Node* Front(struct Node* pQueue)
{
	if (IsEmpty(pQueue))
	{
		return NULL;
	}
	return pQueue->pPre;
}

//�ҵ���β
struct Node* Back(struct Node* pQueue)
{
	if (IsEmpty(pQueue))
	{
		return NULL;
	}
	return pQueue->pNext;
}

//�ж϶����Ƿ�Ϊ��
bool IsEmpty(struct Node* pQueue)
{
	if (NULL == pQueue || pQueue->pNext == pQueue)
	{
		return true;
	}
	return false;
}

//��������
struct Node* Queue()
{
	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp == NULL)
		return NULL;
	pTemp->iData = -1;
	pTemp->pNext = pTemp;
	pTemp->pPre = pTemp;
	return pTemp;
}