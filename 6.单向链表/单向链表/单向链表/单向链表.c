#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct Node
{
	int iValue;
	struct Node* pNext;
};


//添加节点
void AddtoEnd(struct Node** pHead, struct Node** pEnd, int iData);

//添加头节点
void AddtoHead(struct Node** pHead, struct Node** pEnd, int iData);

//添加节点(不使用尾指针)
void AddtoEndNopEnd(struct Node** pHead, int iData);

//清空链表中的数据
void FreeList(struct Node* pHead);

//释放链表
void FreeListNULL(struct Node** pHead, struct Node** pEnd);

//输出数据
void look(struct Node* pHead);

//通过下标找到节点
struct Node* FindNodeByIndex(struct Node* pHead, int Index);

//通过下标插入节点
void InsertNodebyIndex(struct Node** pHead, struct Node** pEnd, int Index, int data);

//增加指定数量的节点
void AddSomeNode(struct Node** pHead, struct Node** pEnd, int Num, int iData);

//通过数据找到节点
struct Node* FindNodeByData(struct Node* pHead, int iData);

//修改节点中的数据
void ChangeData(struct Node* pHead, int old_data, int new_data);

//修改多个节点中的数据(相同的数据)
void ChangeSameData(struct Node* pHead, int old_data, int new_data);

//修改多个节点中的数据(相同的数据) 方法2
void ChangeSameData_test(struct Node* pHead, int old_data, int new_data);

//删除头节点
void DeleteHead(struct Node** pHead, struct Node** pEnd);

//删除尾节点
void DeleteEnd(struct Node** pHead, struct Node** pEnd);

//通过数据删除一个节点
struct Node* DeleteOneDataByData(struct Node** pHead, struct Node** pEnd, int data);

//通过数据删除同样数据的节点
void DeleteAllSameData(struct Node** pHead, struct Node** pEnd, int data);

//通过下标删除节点
void DeleteNodeByIndex(struct Node** pHead, struct Node** pEnd, int Index);

//交换节点中的数据
void SwapDataByData(struct Node* pHead, int data1, int data2);

//通过下标交换数据
void SwapDataByIndex(struct Node* pHead, int Index1, int Index2);

//通过交换节点来交换数据(下标)
void SwapByChangePoint(struct Node** pHead, struct Node** pEnd, int Index1, int Index2);

//翻转链表
void ReverseByIndex(struct Node* pHead);

//获取节点数
int GetNodeCount(struct Node* pHead);

//通过节点下标翻转链表
void ReverseListByIndex(struct Node** pHead, struct Node** pEnd);

//通过空间辅助翻转链表
void ReverseByHelpSpace(struct Node** pHead, struct Node** pEnd);

int main(void)
{
	struct Node* pHead=NULL;
	struct Node* pEnd = NULL;

	AddtoEnd(&pHead, &pEnd, 3);
	AddtoEnd(&pHead, &pEnd, 7);
	AddtoEnd(&pHead, &pEnd, 4);
	AddtoEnd(&pHead, &pEnd, 9);
	AddtoEnd(&pHead, &pEnd, 10);
	AddtoEnd(&pHead, &pEnd, 5);

	DeleteNodeByIndex(&pHead,&pEnd,5);
	AddtoEnd(&pHead, &pEnd, 1);

	//ReverseByIndex(pHead);
	//ReverseListByIndex(&pHead, &pEnd);
	//ReverseByHelpSpace(&pHead, &pEnd);

	//AddtoHead(&pHead, &pEnd,5);

	//SwapByChangePoint(&pHead,&pEnd,0,1);

	//AddtoEndNopEnd(&pHead, 9);

	//AddSomeNode(&pHead,&pEnd,6,6);

	//SwapDataByData(pHead, 4, 3);
	//SwapDataByIndex(pHead, 1, 3);
	//SwapDataByData(pHead, 7, 9);

	//DeleteNodeByIndex(&pHead, &pEnd, 0);
	//DeleteNodeByIndex(&pHead, &pEnd, 1);

	//DeleteAllSameData(&pHead, &pEnd, 4);

    //DeleteOneDataByData(&pHead, &pEnd, 4);
	//DeleteHead(&pHead, &pEnd);
	//DeleteEnd(&pHead, &pEnd);


	//ChangeData(pHead, 2, 8);
	//ChangeSameData(pHead, 5, 8);

	//AddSomeNode(&pHead, &pEnd, 2, 8);

	//InsertNodebyIndex(&pHead, &pEnd, 0, 9);
	//InsertNodebyIndex(&pHead, &pEnd, 1, 8);

	/*struct Node* pTemp = FindNodeByIndex(pHead, 2);
	if (pTemp != NULL)
	{
		printf("该节点数据为:%d\n", pTemp->iValue);
	}*/

	//ChangeSameData_test(pHead, 5, 8);

	look(pHead);

	//AddtoEndNopEnd(&pHead, 4);
	//AddtoEndNopEnd(&pHead, 5);
	//AddtoEndNopEnd(&pHead, 2);

	/*FreeList(pHead);
	pHead = NULL;
	pEnd = NULL;*/

	FreeListNULL(&pHead,&pEnd);

	system("pause>0");
	return 0;
}

//通过空间辅助翻转链表
void ReverseByHelpSpace(struct Node** pHead, struct Node** pEnd)
{
	if (*pHead == NULL)
	{
		return;
	}
	if ((*pHead)->pNext == NULL)
	{
		return;
	}
	struct Node* pTemp = *pHead;
	//新链表的头尾
	struct Node* pNewHead = NULL;
	struct Node* pNewEnd = NULL;

	while (pTemp != NULL)
	{
		AddtoHead(&pNewHead, &pNewEnd, pTemp->iValue);

		pTemp = pTemp->pNext;
	}
	//释放原链表
	FreeListNULL(pHead, pEnd);
	//原头尾指针指向新链表
	*pHead = pNewHead;
	*pEnd = pNewEnd;
}

//通过节点翻转链表
void ReverseListByIndex(struct Node** pHead, struct Node** pEnd)
{
	if (*pHead == NULL)
	{
		return;
	}
	if ((*pHead)->pNext  == NULL)
	{
		return;
	}
	int iCount = GetNodeCount(*pHead);
	for (int i = 0, j = iCount - 1; i < j; i++, j--)
	{
		SwapByChangePoint(pHead,pEnd,i,j);
	}
}

//获取节点数
int GetNodeCount(struct Node* pHead)
{
	int i = 0;
	while (pHead != NULL)
	{
		i++;
		pHead = pHead->pNext;
	}

	return i;
}

//翻转链表   //首先要获取链表节点数
void ReverseByIndex(struct Node* pHead)
{
	int iCount;
	if (pHead == NULL)
	{
		return;
	}
	if (pHead->pNext == NULL)
	{
		return;
	}
	iCount=GetNodeCount(pHead);
	for (int i = 0, j = iCount-1; i < j; i++, j--)
	{
		SwapDataByIndex(pHead,i,j);
	}
}

//通过交换节点来交换数据
void SwapByChangePoint(struct Node** pHead, struct Node** pEnd, int Index1, int Index2)
{
	//参数合法性检测
	if (*pHead == NULL || (*pHead)->pNext == NULL || Index1 == Index2 || Index1 < 0 || Index2 < 0)
	{
		return;
	}
	//确定大小关系
	int iMin = Index1;
	int iMax = Index2;
	if (Index1 > Index2)
	{
		iMin = Index2;
		iMax = Index1;
	}
	//根据下标找节点
	struct Node* pMin = FindNodeByIndex(*pHead, iMin);
	struct Node* pMax = FindNodeByIndex(*pHead, iMax);
	//找不到则终止
	if (pMin == NULL || pMax == NULL)
	{
		printf("查无此节点!\n");
		return;
	}
	//头尾交换
	if (pMin == *pHead && pMax == *pEnd)
	{
		if ((*pHead)->pNext == *pEnd)       //两个节点
		{
			(*pEnd)->pNext = *pHead;
			(*pHead)->pNext = NULL;
			//交换指向
			*pHead = *pEnd;
			*pEnd = (*pHead)->pNext;
		}
		else                                 //多个节点
		{
			//找到尾巴的前一个节点
			struct Node* pMaxPre= FindNodeByIndex(*pHead, iMax-1);
			//尾巴变头
			(*pEnd)->pNext = (*pHead)->pNext;
			//头变尾巴
			pMaxPre->pNext = *pHead;
			//头下一个为空
			(*pHead)->pNext = NULL;
			//交换指向
			*pHead = *pEnd;
			*pEnd = pMaxPre->pNext;
		}
	}
	//头与中间节点交换
	else if(pMin == *pHead && pMax != *pEnd)
	{
		//相邻
		if (pMin->pNext == pMax)
		{
			pMin->pNext = pMax->pNext;
			pMax->pNext = pMin;
			*pHead = pMax;
		}
		else                 //不相邻
		{
			//找到pMax的前一个节点
			struct Node* pMaxPre = FindNodeByIndex(*pHead, iMax - 1);
			//记录整个链表的第二个节点
			struct Node* pt = pMin->pNext;
			//头节点连在pMax的位置上
			pMin->pNext = pMax->pNext;
			pMaxPre->pNext = pMin;
			//把pMax变成头
			pMax->pNext = pt;
			//改变新的头
			*pHead = pMax;
		}
	}
	//中间节点与尾节点交换
	else if (pMin != *pHead && pMax == *pEnd)
	{
		//相邻
		if (pMin->pNext == pMax)
		{
			//找到pMin的前一个节点
			struct Node* pMinPre = FindNodeByIndex(*pHead, iMin - 1);
			//尾巴放到中间
			pMinPre->pNext = pMax;
			pMax->pNext = pMin;
			//尾指针下一个为NULL
			pMin->pNext = NULL;
			*pEnd = pMin;
		}
		else         //不相邻
		{
			//找到pMin的前一个节点
			struct Node* pMinPre = FindNodeByIndex(*pHead, iMin - 1);
			//找到pMax的前一个节点
			struct Node* pMaxPre = FindNodeByIndex(*pHead, iMax - 1);
			//把尾节点放中间
			pMinPre->pNext = pMax;
			pMax->pNext = pMin->pNext;
			//中间节点放到尾巴上
			pMaxPre->pNext = pMin;
			pMin->pNext = NULL;
			*pEnd = pMin;
		}
	}
    //均是中间节点进行交换
	else if (pMin != *pHead && pMax != *pEnd)
	{
		//相邻
		if (pMin->pNext == pMax)
		{
			//找到pMin的前一个节点
			struct Node* pMinPre = FindNodeByIndex(*pHead, iMin - 1);
			//把pMax拿下来
			pMin->pNext = pMax->pNext;
			pMinPre->pNext = pMax;
			pMax->pNext = pMin;
		}
		else
		{
			//找到pMin的前一个节点，后一个节点
			struct Node* pMinPre = FindNodeByIndex(*pHead, iMin - 1);
			struct Node* pMinNext = pMin->pNext;
			//找到pMax的前一个节点，后一个节点
			struct Node* pMaxPre = FindNodeByIndex(*pHead, iMax - 1);
			struct Node* pMaxNext = pMax->pNext;

			//将pMin装到pMax的位置
			pMaxPre->pNext = pMin;
			pMin->pNext = pMaxNext;

			//将pMax装到pMin的位置
			pMinPre->pNext = pMax;
			pMax->pNext = pMinNext;
		}
	}
}

void SwapDataByIndex(struct Node* pHead, int Index1, int Index2)
{
	if (pHead == NULL)
	{
		return;
	}
	//找节点
	struct Node* pTemp1 = FindNodeByIndex(pHead, Index1);
	struct Node* pTemp2 = FindNodeByIndex(pHead, Index2);
	//判断是否找到了
	if (pTemp1 != NULL && pTemp2 != NULL)
	{
		//交换数据
		int temp = pTemp1->iValue;
		pTemp1->iValue = pTemp2->iValue;
		pTemp2->iValue = temp;
	}
	else
	{
		printf("未找到该数据!\n");
	}
}

void SwapDataByData(struct Node* pHead, int data1,int data2)
{
	if (pHead == NULL)
	{
		return;
	}
	//找节点
	struct Node* pTemp1=FindNodeByData(pHead,data1);
	struct Node* pTemp2= FindNodeByData(pHead,data2);
	//判断是否找到了
	if (pTemp1 != NULL && pTemp2 != NULL)
	{
		//交换数据
		int temp = pTemp1->iValue;
		pTemp1->iValue = pTemp2->iValue;
		pTemp2->iValue = temp;

		//不是很明白
		/*在这段代码中， pTemp2 是一个指针，它指向一个内存地址，通过这个指针
		可以访问和修改所指向的内存空间中的数据。而 & pt 是取 pt 变量的地址，
		它得到的是 pt 在内存中的存储位置。具体来说， pTemp2 可以被赋值为不同的地址，
		以指向不同的对象，并且可以通过对 pTemp2 进行解引用（如 * pTemp2 ）来操作它所指向的对象。
		而 & pt 代表的是 pt 这个变量本身在内存中的固定地址，不能被重新赋值为其他地址，
		它是用于获取pt 的地址以便在需要传递地址的地方使用，比如作为函数参数或者赋值给其他指针变量。*/
		/*
		struct Node pt = *pTemp2;       
		memcpy(pTemp2, pTemp1, 4);
		memcpy(pTemp1, &pt, 4);
		*/
	}
	else
	{
		printf("未找到该数据!\n");
	}

}

void DeleteNodeByIndex(struct Node** pHead, struct Node** pEnd, int Index)
{
	if (*pHead == NULL)
	{
		return;
	}
	if (Index == 0)
	{
		DeleteHead(pHead, pEnd);
	}
	else
	{
		//查找前一个节点  记录
		struct Node* pTemp = FindNodeByIndex(*pHead, Index - 1);
		if(pTemp != NULL)
		{
			if (pTemp->pNext == *pEnd)
			{
				DeleteEnd(pHead, pEnd);
			}
			else
			{
				struct Node* pt = pTemp->pNext;
				pTemp->pNext = pt->pNext;
				free(pt);
			}
		}
		else
		{
			printf("查无此节点!\n");
		}
	}
}

void DeleteAllSameData(struct Node** pHead, struct Node** pEnd, int data)
{
	if (*pHead == NULL)
	{
		return;
	}
	struct Node* pt = DeleteOneDataByData(pHead, pEnd, data);
	while (pt != NULL)
	{
		pt = DeleteOneDataByData(pHead, pEnd, data);
	}
}

struct Node*  DeleteOneDataByData(struct Node** pHead, struct Node** pEnd, int data)
{
	if (*pHead == NULL)
	{
		return NULL;
	}
	if ((*pHead)->iValue == data)
	{
		DeleteHead(pHead, pEnd);
		return *pHead;
	}
	else if ((*pEnd)->iValue == data)
	{
		DeleteEnd(pHead, pEnd);
		return *pHead;
	}
	else
	{
		//找到该节点的前一个
		struct Node* pTemp = *pHead;
		while (pTemp->pNext != NULL)
		{
			if (pTemp->pNext->iValue == data)
			{
				break;
			}
			pTemp = pTemp->pNext;
		}
		//判断是否找到
		if (pTemp->pNext != NULL)
		{
			struct Node* pt = pTemp->pNext;
			pTemp->pNext = pt->pNext;
			free(pt);
			return pTemp->pNext;
		}
		else
		{
			return NULL;
		}
	}
}

void DeleteEnd(struct Node** pHead, struct Node** pEnd)
{
	if (*pHead == NULL)
	{
		return;
	}
	if (*pHead == *pEnd)
	{
		free(*pHead);
		*pHead = NULL;
		*pEnd = NULL;
	}
	else
	{
		struct Node* pTemp = *pHead;
		while (pTemp->pNext != *pEnd)
		{
			pTemp = pTemp->pNext;
		}
		//找到了
		free(*pEnd);
		*pEnd = pTemp;
		(*pEnd)->pNext = NULL;
	}
}

void DeleteHead(struct Node** pHead, struct Node** pEnd)
{
	if (*pHead == NULL)
	{
		return;
	}
	if (*pHead == *pEnd)
	{
		free(*pHead);
		*pHead = NULL;
		*pEnd = NULL;
	}
	else
	{
		struct Node* pTemp = *pHead;
		*pHead = (*pHead)->pNext;
		free(pTemp);
	}
}

void ChangeSameData_test(struct Node* pHead, int old_data, int new_data)
{
	//参数合法性检测
	if (NULL == pHead)
	{
		printf("头指针为空!\n");
		return;
	}
	struct Node* pt = FindNodeByData(pHead, old_data);
	if (pt == NULL)
	{
		printf("查无此节点!\n");
		return;
	}
	else
	{
		pt->iValue = new_data;
	}
	while (pt != NULL)
	{
		pt = FindNodeByData(pHead, old_data);
       
		if (pt != NULL)
		{
			pt->iValue = new_data;
		}
		
	}
}

void ChangeSameData(struct Node* pHead, int old_data, int new_data)
{
	//参数合法性检测
	if (NULL == pHead)
	{
		printf("头指针为空!\n");
		return;
	}
	while (pHead != NULL)
	{
		if (pHead->iValue == old_data)
		{
			pHead->iValue = new_data;
		}

		pHead = pHead->pNext;
	}
}

void ChangeData(struct Node* pHead, int old_data, int new_data)
{
	struct Node* pRet = FindNodeByData(pHead, old_data);
	if (pRet == NULL)
	{
		printf("查无此节点!\n");
	}
	else
	{
		pRet->iValue=new_data;
	}
}

struct Node* FindNodeByData(struct Node* pHead, int iData)
{
	//参数合法性检测
	if (NULL == pHead)
	{
		return NULL;
	}
	while (pHead != NULL)
	{
		if (pHead->iValue == iData)
		{
			return pHead;
		}

		pHead = pHead->pNext;
	}

	return NULL;
}

void AddSomeNode(struct Node** pHead, struct Node** pEnd, int Num, int iData)
{
	for (int i = 0; i < Num; i++)
	{
		AddtoEnd(pHead, pEnd, iData);
	}
}

void InsertNodebyIndex(struct Node** pHead, struct Node** pEnd, int Index, int data)
{
	//检测参数合法性
	if (Index < 0)
	{
		printf("输入的下标数错误!\n");
		return;
	}
	if (Index == 0)  //头添加
	{
		AddtoHead(pHead,pEnd,data);
	}
	else    //循环链表 插入节点
	{
		struct Node* pt=FindNodeByIndex(*pHead,Index);  //找到该节点

		//创建节点
		struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
		//节点成员赋值
		if (pTemp != NULL)
		{
			pTemp->iValue = data;
			pTemp->pNext = NULL;
		}
		pTemp->pNext = pt->pNext;
		pt->pNext = pTemp;
	}
}

struct Node* FindNodeByIndex(struct Node* pHead, int Index)
{
	//参数合法性检测
	if (NULL == pHead || Index < 0)
	{
		printf("头指针为空/下标错误!\n");
		return NULL;
	}
	//循环链表
	int i = 0;
	while (pHead != NULL)
	{
		if (Index == i)
		{
			return pHead;
		}
		i++;

		pHead = pHead->pNext;
	}
	printf("下标数过大!\n");
	return NULL;
}

void AddtoHead(struct Node** pHead, struct Node** pEnd, int iData)
{
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (NULL != pTemp)
	{
		//给节点成员赋值
		pTemp->iValue = iData;
		pTemp->pNext = NULL;
		if (*pHead == NULL)  //空链表
		{
			//*pHead = pTemp;
			*pEnd = pTemp;
		}
		else
		{
			pTemp->pNext = *pHead;
			//*pHead = pTemp;
		}
		*pHead = pTemp;
	}
}

void FreeListNULL(struct Node** pHead, struct Node** pEnd)
{
	struct Node* pTemp = *pHead;
	while (pTemp != NULL)
	{
		struct Node* pt = pTemp;
		pTemp = pTemp->pNext;
		free(pt);
	}
	*pHead = NULL;
	*pEnd = NULL;
}

void look(struct Node* pHead)
{
	while (pHead != NULL)
	{
		printf("%d ", pHead->iValue);

		pHead = pHead->pNext;
	}
}

void FreeList(struct Node* pHead)
{
	while (pHead != NULL)
	{
		struct Node* pt = pHead;
		pHead = pHead->pNext;
		free(pt);
	}
}

void AddtoEndNopEnd(struct Node** pHead, int iData)
{
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)
	{
		//给节点成员赋值
		pTemp->iValue = iData;
		pTemp->pNext = NULL;
		if (NULL == *pHead)  //空链表
		{
			*pHead = pTemp;
		}
		else
		{
			struct Node* pt = *pHead;
			while (pt->pNext != NULL)
			{
				pt = pt->pNext;
			}
			pt->pNext = pTemp;
		}
	}

}

void AddtoEnd(struct Node** pHead, struct Node** pEnd, int iData)
{
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)
	{
	    //给节点赋值
		pTemp->iValue  = iData;
		pTemp->pNext = NULL;
		//连起来
		if (NULL == *pHead)  //空链表
		{
			*pHead = pTemp;
			//*pEnd = pTemp;
		}
		else
		{
			(*pEnd)->pNext = pTemp;
			//*pEnd = pTemp;
		}
		*pEnd = pTemp;
	}
	
}