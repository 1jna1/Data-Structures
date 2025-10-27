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

//尾添加
void AddToEnd(struct Node* stHead, int iData);
//释放链表
void FreeList(struct Node* stHead);
//快慢指针
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

	//不变成环
	//先记录尾节点
	struct Node* pEnd = stHead.pPre;
	stHead.pPre->pNext= NULL;
	stHead.pPre = NULL;


	//变成环
	//stHead.pPre->pNext = stHead.pNext->pNext->pNext;

	bool res = QuickSlow(&stHead);

	FreeList(&stHead);

	system("pause>0");
	return 0;
}

//快慢指针
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
	//参数合法性检测
	if (NULL == stHead)
	{
		return;
	}
	//创建链表
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //申请空间成功
	{
		//节点成员赋值
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;
		//添加到链表上
		pTemp->pNext = stHead;
		pTemp->pPre = stHead->pPre;
		stHead->pPre->pNext = pTemp;
		stHead->pPre = pTemp;
	}
}

//释放链表
void FreeList(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead)
	{
		return;
	}
	//释放
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