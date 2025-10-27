#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

struct Node
{
	int iData;
	struct Node* pPre;
	struct Node* pNext;
};

//β���
void AddToEnd(struct Node* stHead, int iData);
//�ͷ�����
void FreeList(struct Node* stHead);
//����ָ��
bool QuickSlow(struct Node* stHead);

int main(void)
{
	struct Node stHead;
	stHead.iData = -1;
	stHead.pNext = &stHead;
	stHead.pPre = &stHead;

	AddToEnd(&stHead, 1);
	AddToEnd(&stHead, 2);
	AddToEnd(&stHead, 3);
	AddToEnd(&stHead, 4);
	AddToEnd(&stHead, 5);
	AddToEnd(&stHead, 6);

	//����ɻ�
	//�ȼ�¼β�ڵ�
	struct Node* pEnd = stHead.pPre;
	stHead.pPre->pNext= NULL;
	stHead.pPre = NULL;


	//��ɻ�
	//stHead.pPre->pNext = stHead.pNext->pNext->pNext;

	bool res = QuickSlow(&stHead);

	FreeList(&stHead);

	system("pause>0");
	return 0;
}

//����ָ��
bool QuickSlow(struct Node* stHead)
{
	struct Node* quick = stHead->pNext;
	struct Node* slow = stHead->pNext;

	while (quick!=NULL && quick->pNext!=NULL)
	{
		quick = quick->pNext->pNext;
		slow = slow->pNext;

		if (quick == slow)
		{
			return true;
		}
	}
	return false;
}

void AddToEnd(struct Node* stHead, int iData)
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
		//��ӵ�������
		pTemp->pNext = stHead;
		pTemp->pPre = stHead->pPre;
		stHead->pPre->pNext = pTemp;
		stHead->pPre = pTemp;
	}
}

//�ͷ�����
void FreeList(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead)
	{
		return;
	}
	//�ͷ�
	struct Node* pTemp = stHead->pNext;

	while (pTemp != NULL)
	{
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);
	}
	stHead->pNext = stHead;
	stHead->pPre = stHead;
}