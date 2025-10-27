#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;
	struct Node* pNext;
};

//尾添加
void AddToTail(struct Node *stHead,int iData);
//释放链表
void FreeList(struct Node* stHead);
//遍历链表
void Look(struct Node stHead);
//头添加
void AddToHead(struct Node* stHead, int iData);
//在指定的数据后面添加
void AddDataByPosData(struct Node* stHead, int iPosData, int iData);
//在指定的下标位置添加数据
void AddByIndex(struct Node* stHead, int iPosIndex, int iData);
//在指定的下标位置添加一些数据
void AddSomeByIndex(struct Node* stHead, int iPosIndex,int iCount, int iData);
//通过数据找到节点
struct Node* FindNodeByData(struct Node* stHead, int iData);
//通过下标找到节点
struct Node* FindNodeByIndex(struct Node* stHead, int iIndex);
//通过下标修改节点
void ChangeByIndex(struct Node* stHead, int iIndex, int iValue);
//通过数据修改节点(修改所有相同数据)
void ChangeByData(struct Node* stHead, int Data, int iValue);
//通过下标删除节点
void DeleteByIndex(struct Node* stHead,int iIndex);
//通过数据删除节点(删除所有相同数据)
void DeleteByData(struct Node* stHead, int iValue);
//去重 **************************************(有操作性)
void DeleteSame(struct Node* stHead);



int main(void)
{
	//创建空头
	struct Node stHead = { 0,NULL };  //空头中的数据用来记录节点个数
	

	AddToTail(&stHead, 1);
	AddToTail(&stHead, 9);
	AddToTail(&stHead, 7);
	AddToTail(&stHead, 8);
	AddToTail(&stHead, 6);
	AddToTail(&stHead, 3);
	Look(stHead);


	/*DeleteSame(&stHead);
	Look(stHead);
	AddToTail(&stHead, 1);
	AddToTail(&stHead, 6);
	Look(stHead);*/
	/*DeleteByData(&stHead,9);
	AddToTail(&stHead, 5);
	AddToHead(&stHead, 7);
	AddDataByPosData(&stHead, 5, 8);
	Look(stHead);*/

	/*DeleteByIndex(&stHead,2);
	Look(stHead);*/
	/*ChangeByData(&stHead,6,5);
    Look(stHead);*/

	/*ChangeByIndex(&stHead, -1, 2);
	Look(stHead);*/
	/*struct Node* pT = FindNodeByIndex(&stHead, 1);
	if (pT != NULL)
	{
		printf("%d ", pT->iData);
	}
	else
	{
		printf("很抱歉，未找到该节点!\n");
	}*/
	/*struct Node* pT = FindNodeByData(&stHead, 8);
	Look(stHead);
	if (pT != NULL)
	{
		printf("%d ", pT->iData);
	}
	else
	{
		printf("很抱歉，未找到该节点!\n");
	}*/
	//AddSomeByIndex(&stHead,0,3,5);
	//AddSomeByIndex(&stHead,4,2,6);  //5 5 5 1 6 6 3 
	//AddToHead(&stHead, 7);

	//AddToTail(&stHead, 2);

	//AddDataByPosData(&stHead, 2, 8);

	//AddToHead(&stHead, 5);

	//AddDataByPosData(&stHead, 2, 6);   // 5  7  1  3  2  6  8

 //   AddByIndex(&stHead,3,9);
	FreeList(&stHead);

	system("pause>0");
	return 0;
}

//去重
void DeleteSame(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 1)
	{
		return;
	}

	//循环链表,去重(双重循环)
	struct Node* pWai = stHead;
	while (pWai->pNext != NULL)
	{
		struct Node* pNei = pWai;
		while (pNei->pNext != NULL)
		{
			if (pWai->iData == pNei->pNext->iData)
			{
				//找到了该节点,删除节点
				struct Node* pTemp = pNei->pNext;
				pNei->pNext = pTemp->pNext;
				free(pTemp);
				stHead->iData -= 1;
				continue;  //如果不结束,那么指针往下移一个会漏掉当前节点
			}

			pNei = pNei->pNext;
		}

		pWai = pWai->pNext;
	}
}

//通过数据删除节点(删除所有相同数据)
void DeleteByData(struct Node* stHead, int iValue)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0)
	{
		return;
	}
	//循环找到节点
	struct Node* pTemp = stHead;
	while (pTemp->pNext != NULL)
	{
		if (pTemp->pNext->iData == iValue)
		{
			//记录当前节点,准备删除
			struct Node* pT = pTemp->pNext;
			pTemp->pNext = pT->pNext;
			free(pT);   //删除节点
			stHead->iData -= 1;
			continue;
		}
		pTemp = pTemp->pNext;
	}
}

//通过下标删除节点
void DeleteByIndex(struct Node* stHead, int iIndex)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0 || iIndex<0 || iIndex>stHead->iData - 1)
	{
		return;
	}
	//循环找到节点前一个位置
	struct Node* pTemp = stHead;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	//记录该节点位置,准备释放
	struct Node* pT = pTemp->pNext;
	pTemp->pNext = pT->pNext;
	free(pT);
	stHead->iData -= 1;
}

//通过数据修改节点(修改所有相同数据)
void ChangeByData(struct Node* stHead, int Data, int iValue)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0)
	{
		return;
	}
	//找到该数据
	struct Node* pTemp = stHead->pNext;
	while (pTemp != NULL)
	{
		if (pTemp->iData == Data)
		{
			pTemp->iData = iValue;
		}
		pTemp = pTemp->pNext;
	}
}

//通过下标修改节点
void ChangeByIndex(struct Node* stHead, int iIndex, int iValue)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0 || iIndex<0 || iIndex>stHead->iData - 1)
	{
		return;
	}
	//循环找到指定下标的节点
	struct Node* pTemp = stHead->pNext;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	//找到了,修改数据
	pTemp->iData = iValue;
}

//通过下标找到节点
struct Node* FindNodeByIndex(struct Node* stHead, int iIndex)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0 || iIndex<0 || iIndex>stHead->iData - 1)
	{
		return NULL;
	}
	struct Node* pTemp = stHead->pNext;
	//找到该下标(不存在情况上面已经考虑,所以一定能找到)
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//通过数据找到节点
struct Node* FindNodeByData(struct Node* stHead, int iData)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0)
	{
		return NULL;
	}
	struct Node* pTemp = stHead->pNext;
	while (pTemp != NULL)
	{
		if (pTemp->iData == iData)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//在指定的下标位置添加一些数据
void AddSomeByIndex(struct Node* stHead, int iPosIndex, int iCount, int iData)
{
	//参数合法性检测
	if (NULL == stHead || iPosIndex<0 || iPosIndex >stHead->iData)
	{
		return;
	}

	//找到节点  (找不到的情况上面已经考虑了,因此一定能找到)
	struct Node* pTemp = stHead;
	for (int i = 0; i < iPosIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	for (int i = 0; i < iCount; i++)
	{
		AddToHead(pTemp, iData);
		pTemp->iData -= 1;
		stHead->iData += 1;
	}
}

//在指定的下标位置添加数据
void AddByIndex(struct Node* stHead, int iPosIndex, int iData)
{
	//参数合法性检测
	if (NULL == stHead || iPosIndex<0 || iPosIndex >stHead->iData)
	{
		return;
	}

	//找到节点  (找不到的情况上面已经考虑了,因此一定能找到)
	struct Node* pTemp = stHead;
	for (int i = 0; i < iPosIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	AddToHead(pTemp, iData);
	pTemp->iData -= 1;
	stHead->iData += 1;
}

//在指定的数据后面添加
void AddDataByPosData(struct Node* stHead, int iPosData, int iData)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData <= 0)
	{
		return;
	}

	//遍历链表找到该数据位置
	struct Node* pTemp = stHead->pNext;
	while (pTemp != NULL)
	{
		if (pTemp->iData == iPosData)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	//没找到
	if (NULL == pTemp)
	{
		printf("查无此节点!\n");
	}
	else  //找到了
	{
		AddToHead(pTemp, iData);
		pTemp->iData -= 1;
		stHead->iData += 1;
	}
}

//头添加
void AddToHead(struct Node* stHead, int iData)
{
	//参数合法性检测
	if (NULL == stHead)
	{
		return;
	}
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //节点创建成功
	{
		//节点成员赋值
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		//把节点连接起来
		pTemp->pNext = stHead->pNext;
		stHead->pNext = pTemp;
		//节点数量++
		stHead->iData++;
	}
}

//遍历链表
void Look(struct Node stHead)
{
	struct Node* pTemp = stHead.pNext;
	printf("共有%d个数据:", stHead.iData);
	while (pTemp != NULL)
	{
		printf("%d  ", pTemp->iData);

		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

void AddToTail(struct Node* stHead, int iData)
{
	//参数合法性检测
	if (NULL == stHead || stHead->iData  < 0)
	{
		return;
	}

	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));

	if (pTemp != NULL)     //创建节点成功
	{
		//节点成员赋值
		pTemp->iData = iData;
		pTemp->pNext = NULL;

		//把节点连起来
		struct Node* pT = stHead;   //空头不能再指向下一个，不然找不到了
		while (pT->pNext != NULL)
		{
			pT = pT->pNext;
		}

		pT->pNext = pTemp;
		//计数器++
		stHead->iData++;
	}
}

//释放链表
void FreeList(struct Node* stHead)
{
   //参数合法性检测
   if (NULL == stHead || stHead->iData <= 0)
   {
	 return;
   }
   //释放各个节点
   struct Node* pTemp = stHead->pNext;
   while (pTemp != NULL )
   {
	   //记录当前节点
	   struct Node* pT = pTemp;
	   //节点下移
	   pTemp = pTemp->pNext;
	   //释放当前节点
	   free(pT);
   }
   stHead->iData  = 0;
   stHead->pNext = NULL;
}