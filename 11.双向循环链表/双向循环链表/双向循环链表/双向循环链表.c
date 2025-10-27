#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;
	struct Node* pNext;
	struct Node* pPre;
};

//尾添加
void AddToEnd(struct Node* stHead, int* pCount, int iData);
//遍历链表
void Look(struct Node* stHead, int* pCount);
//释放链表
void FreeList(struct Node* stHead, int* pCount);
//头添加
void AddToHead(struct Node* stHead, int* pCount, int iData);
//根据下标查找节点
struct Node* GetNodeByIndex(struct Node* stHead, int* pCount, int iIndex);
//根据数据查找节点
struct Node* GetNodeByData(struct Node* stHead,int iData);
//通过下标在指定位置插入一个节点
void InsertByIndex(struct Node* stHead, int* pCount, int iIndex, int iData);
//通过数据在指定位置插入一个节点
void InsertByData(struct Node* stHead, int* pCount, int iValue, int iData);
//通过下标在指定位置插入多个节点
void InsertSomeByIndex(struct Node* stHead, int* pCount, int iIndex, int iData,int iNodeCount);
//根据下标删除指定节点
void DeleteByIndex(struct Node* stHead, int* pCount, int iIndex);
//根据下标删除指定范围的节点
void DeleteSomeByIndex(struct Node* stHead, int* pCount, int iIndex1, int iIndex2);
//根据数据删除指定节点
void DeleteByData(struct Node* stHead, int* pCount, int iData);
//删除相同数据的节点
void DeleteSameByData(struct Node* stHead, int* pCount, int iData);

//有空头双向循环链表
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

//删除相同数据的节点
void DeleteSameByData(struct Node* stHead, int* pCount, int iData)
{
	//参数合法性检测
	if (NULL == stHead || *pCount <= 0)
	{
		return;
	}
	
	while (1)
	{
		//找到该节点
		struct Node* pTemp = GetNodeByData(stHead, iData);

		if (pTemp == NULL)
		{
			return;
		}
		//删除节点
		pTemp->pPre->pNext = pTemp->pNext;
		pTemp->pNext->pPre = pTemp->pPre;
		free(pTemp);
		(*pCount)--;
	}
}

//根据数据删除指定节点
void DeleteByData(struct Node* stHead, int* pCount, int iData)
{
	//参数合法性检测
	if (NULL == stHead || *pCount <= 0)
	{
		return;
	}
	//找到该节点
	struct Node* pTemp= GetNodeByData(stHead,iData);
	if (pTemp == NULL)
	{
		return;
	}
	//删除节点
	pTemp->pPre->pNext = pTemp->pNext;
	pTemp->pNext->pPre = pTemp->pPre;
	free(pTemp);
	(*pCount)--;
}

//根据下标删除指定范围的节点
void DeleteSomeByIndex(struct Node* stHead, int* pCount, int iIndex1, int iIndex2)
{
	for (int i = iIndex1; i <= iIndex2; i++)
	{
		DeleteByIndex(stHead,pCount,iIndex1);
	}
}

//根据下标删除指定节点
void DeleteByIndex(struct Node* stHead, int* pCount, int iIndex)
{
	//调用查找函数已经进行参数合法性检测,因此这里不写了
	//找到该节点
	struct Node* pTemp= GetNodeByIndex(stHead,pCount,iIndex);
	if (pTemp == NULL)
	{
		return;
	}
	//删除
	pTemp->pPre->pNext = pTemp->pNext;
	pTemp->pNext->pPre = pTemp->pPre;
	free(pTemp);
	(*pCount)--;
}

//通过下标在指定位置插入多个节点
void InsertSomeByIndex(struct Node* stHead, int* pCount, int iIndex, int iData, int iNodeCount)
{
	for (int i = 0; i <iNodeCount; i++)
	{
		InsertByIndex(stHead,pCount,iIndex,iData);
	}
}

//通过数据在指定位置插入一个节点
void InsertByData(struct Node* stHead, int* pCount, int iValue, int iData)
{
	//参数合法性检测
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
		//创建节点
		struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
		if (pT != NULL)		//申请空间成功
		{
			//节点成员赋值
			pT->iData = iData;
			pT->pNext = NULL;
			pT->pPre = NULL;
			//新节点与链表相连
			pT->pNext = pTemp;
			pT->pPre = pTemp->pPre;
			pTemp->pPre->pNext = pT;
			pTemp->pPre = pT;
			//节点数量++
			(*pCount)++;
		}
	}
}

//通过下标在指定位置插入一个节点
void InsertByIndex(struct Node* stHead, int* pCount, int iIndex, int iData)
{
	//参数合法性检测
	if (NULL == stHead || stHead->pNext == NULL || iIndex<0 || iIndex>(*pCount))
	{
		return;
	}
	//参数合法性检测已经保证了一定能够找到该节点
	struct Node* pTemp= GetNodeByIndex(stHead,pCount,iIndex);
	if (iIndex == *pCount)
	{
		AddToEnd(stHead, pCount, iData);
	}
	else
	{
		//创建节点
		struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
		if (pT != NULL)     //申请空间成功
		{
			//节点成员赋值
			pT->iData = iData;
			pT->pNext = NULL;
			pT->pPre = NULL;
			//新节点连接到链表上
			pT->pNext = pTemp;
			pT->pPre = pTemp->pPre;
			pTemp->pPre->pNext = pT;
			pTemp->pPre = pT;
			//节点数量++
			(*pCount)++;
		}
	}
}

//根据数据查找节点
struct Node* GetNodeByData(struct Node* stHead, int iData)
{
	//参数合法性检测
	if (NULL == stHead || stHead->pNext == stHead)
	{
		return NULL;
	}
	//遍历链表
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

//根据下标查找节点
struct Node* GetNodeByIndex(struct Node* stHead, int* pCount, int iIndex)
{
	//参数合法性检测
	if (NULL == stHead || stHead->pNext == stHead || *pCount <= 0 || iIndex<0 || iIndex >= (*pCount))
	{
		return NULL; 
	}
	//遍历链表
	struct Node* pTemp = stHead->pNext;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//头添加
void AddToHead(struct Node* stHead, int* pCount, int iData)
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
		//将新节点与链表连接
		pTemp->pNext = stHead->pNext;
		pTemp->pPre = stHead;
		stHead->pNext->pPre = pTemp;
		stHead->pNext = pTemp;
		//数量++
		(*pCount)++;
	}
}

//释放链表
void FreeList(struct Node* stHead, int* pCount)
{
	//参数合法性检测
	if (NULL == stHead || stHead->pNext == stHead)  //后面说明无节点
	{
		return;
	}
	struct Node* pTemp = stHead->pNext;
	while (pTemp != stHead)
	{
		//记录当前节点
		struct Node* pT = pTemp;
		//往下走一个
		pTemp = pTemp->pNext;
		//释放当前节点
		free(pT);
	}
	*pCount = 0;
	stHead->pNext = stHead;
	stHead->pPre = stHead;
}

//遍历链表
void Look(struct Node* stHead, int* pCount)
{
	//参数合法性检测
	if (NULL == stHead || stHead->pNext == stHead)  //后面说明无节点
	{
		return;
	}
	printf("共有%d个节点: ", *pCount);
	struct Node* pTemp = stHead->pNext;
	while (pTemp != stHead)
	{
		printf("%d  ",pTemp->iData);
		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

//尾添加
void AddToEnd(struct Node* stHead, int* pCount, int iData)
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
		//将新节点与链表连接
		pTemp->pPre = stHead->pPre;
		pTemp->pNext = stHead;
		stHead->pPre->pNext = pTemp;
		stHead->pPre = pTemp;
		//数量++
		(*pCount)++;
	}
}