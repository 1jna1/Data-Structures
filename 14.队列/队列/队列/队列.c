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

//创建队列    //头添加,尾删除
struct Node* Queue();
//判断队列是否为空
bool IsEmpty(struct Node* pQueue);
//找到队头
struct Node* Front(struct Node* pQueue);
//找到队尾
struct Node* Back(struct Node* pQueue);
//头添加
void Push(struct Node* pQueue, int iData);
//尾删除
void Pop(struct Node* pQueue);
//释放队列
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

//释放队列
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
		//记录当前节点
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext; //向下走一个
		free(pT); //释放当前节点
		
	} while (pTemp!=(*pQueue));
	*pQueue = NULL;
}

//尾删除
void Pop(struct Node* pQueue)
{
	if (IsEmpty(pQueue))
	{
		return;
	}
	//记录要删除的节点
	struct Node* pTemp = pQueue->pPre;
	pTemp->pPre->pNext = pQueue;
	pQueue->pPre = pTemp->pPre;
	free(pTemp);
}

//头添加
void Push(struct Node* pQueue, int iData)
{
	if (NULL == pQueue)
	{
		return;
	}

	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));

	if (pTemp == NULL)
	{
		return;
	}
	//节点成员赋值
	pTemp->iData = iData;
	pTemp->pNext = NULL;
	pTemp->pPre = NULL;
	//新节点连接到链表上
	pTemp->pNext = pQueue->pNext;
	pTemp->pPre = pQueue;

	pQueue->pNext->pPre = pTemp;
	pQueue->pNext = pTemp;
}

//找到队头
struct Node* Front(struct Node* pQueue)
{
	if (IsEmpty(pQueue))
	{
		return NULL;
	}
	return pQueue->pPre;
}

//找到队尾
struct Node* Back(struct Node* pQueue)
{
	if (IsEmpty(pQueue))
	{
		return NULL;
	}
	return pQueue->pNext;
}

//判断队列是否为空
bool IsEmpty(struct Node* pQueue)
{
	if (NULL == pQueue || pQueue->pNext == pQueue)
	{
		return true;
	}
	return false;
}

//创建队列
struct Node* Queue()
{
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp == NULL)
		return NULL;
	pTemp->iData = -1;
	pTemp->pNext = pTemp;
	pTemp->pPre = pTemp;
	return pTemp;
}