#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;  //数据
	struct Node* pNext;   //存放下一个节点的地址
	struct Node* pPre;    //存放上一个节点的地址
};

struct Node* g_pHead = NULL;    //初始化头指针
struct Node* g_pEnd = NULL;    //初始化尾指针
int g_iNodeCount = 0;    //记录节点数量

//尾添加
void AddToEnd(int iData);
//释放链表
void FreeList(void);
//正向遍历链表
void LookZheng(void);
//反向遍历链表
void LookFan(void);
//头添加
void AddToHead(int iData);
//通过下标插入指定数量的数据
void InsertNodeByIndex(int iIndex, int Count, int iData);
//在指定的数据前插入数据
void InsertNodeByData(int iValue, int iData);
//通过下标查找节点
struct Node* GetByIndex(int Index);
//通过数据查找节点
struct Node* GetByData(int iData);
//通过下标修改节点数据
void ChangeByIndex(int iIndex,int iValue);
//通过数据修改节点数据
void ChangeByData(int iData,int iValue);
//通过下标删除节点
void DeleteNodeByIndex(int iIndex);
//删除节点
void DeleteNode(struct Node* pTemp);
//删除所有相同数据的节点
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

//删除所有相同数据的节点
void DeleteNodeByData(int iValue)
{
	struct Node* pTemp;
	while (NULL != (pTemp= GetByData(iValue)))
	{
		DeleteNode(pTemp);
	}
}

//删除节点
void DeleteNode(struct Node* pTemp)
{
	//删除的是头节点
	if (pTemp == g_pHead)
	{
		//只有1个节点
		if (g_iNodeCount == 1)
		{
			free(g_pHead);
			g_pHead = NULL;
			g_pEnd = NULL;
		}
		else    //多个节点
		{
			g_pHead = g_pHead->pNext;
			free(g_pHead->pPre);
			g_pHead->pPre = NULL;
		}
	}
	else if (pTemp == g_pEnd)    //删除尾节点
	{
		g_pEnd = g_pEnd->pPre;
		free(g_pEnd->pNext);
		g_pEnd->pNext = NULL;
	}
	else             //删除中间
	{
		
		pTemp->pPre->pNext = pTemp->pNext;
		pTemp->pNext->pPre = pTemp->pPre;
		free(pTemp);
	}
	//节点数量--
	g_iNodeCount--;
}

//通过下标删除节点
void DeleteNodeByIndex(int iIndex)
{
	struct Node* pT= GetByIndex(iIndex);
	if (pT != NULL)
	{
		DeleteNode(pT);
	}
}

//通过数据修改节点数据
void ChangeByData(int iData1, int iValue)
{
	struct Node* p = GetByData(iData1);
	if (p != NULL)
	{
		p->iData = iValue;
	}
}

//通过下标修改节点数据
void ChangeByIndex(int iIndex, int iValue)
{
	struct Node* p= GetByIndex(iIndex);
	if (p != NULL)
	{
		p->iData = iValue;
	}
}

//通过数据查找节点
struct Node* GetByData(int iData)
{
	//参数合法性检测
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

//通过下标查找节点
struct Node* GetByIndex(int Index)
{
	//参数合法性检测
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

//在指定的数据前插入数据
void InsertNodeByData(int iValue, int iData)
{
	//参数合法性检测
	if (NULL == g_pHead)
	{
		return;
	}
	//找到指定的节点
	struct Node* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (pTemp->iData == iValue)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	//判断是否找到了
	if (pTemp != NULL)
	{
		//头添加
		if (pTemp == g_pHead)
		{
			AddToHead(iData);
		}
		//中间添加(因为是往前添加,所以不存在尾添加这种情况)
		else
		{
			//创建节点
			struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
			if (pT != NULL)    //申请空间成功
			{
				//节点成员赋值
				pT->iData = iData;
				pT->pNext = NULL;
				pT->pPre = NULL;

				//前一个节点与创建的节点相连
				pTemp->pPre->pNext = pT;
				pT->pPre = pTemp->pPre;
				//创建的节点与数据节点相连
				pT->pNext = pTemp;
				pTemp->pPre = pT;
				//节点数量++
				g_iNodeCount++;
			}

		}
	}
}

//通过下标插入指定数量的数据
void InsertNodeByIndex(int iIndex, int Count, int iData)
{
	//参数合法性检测
	if (NULL == g_pHead || iIndex < 0 || Count <= 0 || iIndex>g_iNodeCount)
	{
		return;
	}
	//找到该节点
	struct Node* pTemp = g_pHead;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	//把节点连接在链表上
	//头添加
	if (iIndex == 0)
	{
		for (int i = 0; i < Count; i++)
		{
			AddToHead(iData);
		}
	}
	//尾添加
	else if (iIndex == g_iNodeCount)
	{
		for (int i = 0; i < Count; i++)
		{
			AddToEnd(iData);
		}
	}
	else           //中间添加
	{
		for (int i = 0; i < Count; i++)
		{
			//创建节点
			struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
			if (pT != NULL)          //申请空间成功
			{
				//节点成员赋值
				pT->iData = iData;
				pT->pNext = NULL;
				pT->pPre = NULL;

				//链表连接
				//让前一个节点与创建的节点相连
				pTemp->pPre->pNext = pT;
				pT->pPre = pTemp->pPre;
				//创建的节点与指定下标的节点相连
				pT->pNext = pTemp;
				pTemp->pPre = pT;
			}
		}
		//数量++
		g_iNodeCount += Count;
	}
}

//头添加
void AddToHead(int iData)
{
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //申请内存空间成功
	{
		//节点成员赋值
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;

		//把节点与链表相连
		if (g_pHead == NULL)	//空链表
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
		//节点数量++
		g_iNodeCount++;
	}
}

//反向遍历链表
void LookFan(void)
{
	if (g_pHead == NULL)
	{
		return;
	}
	printf("共有%d个节点:", g_iNodeCount);
	//循环遍历链表
	struct Node* pTemp = g_pEnd;
	while (pTemp != NULL)
	{
		printf("%d ", pTemp->iData);

		pTemp = pTemp->pPre;
	}
	putchar('\n');
}

//正向遍历链表
void LookZheng(void)
{
	if (g_pHead == NULL)
	{
		return;
	}
	printf("共有%d个节点:", g_iNodeCount);
	//循环遍历链表
	struct Node* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		printf("%d ", pTemp->iData);

		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

//释放链表
void FreeList(void)
{
	if (NULL == g_pHead)
	{
		return;
	}
	//定义中间变量
	struct Node* pTemp = g_pHead;
	//遍历链表,逐个释放
	while (pTemp != NULL)
	{
		//记录当前节点
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);
		g_iNodeCount = 0;//清空计数
	}
	g_pHead = NULL;
	g_pEnd = NULL;
}

//尾添加
void AddToEnd(int iData)
{
	//参数合法性检测
	if (g_iNodeCount < 0)
	{
		return;
	}
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)   //创建成功
	{
		//节点成员赋值
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;

		//若此时为空链表  //前后节点均是空,头尾一空则空
		if (g_pHead == NULL)
		{
			g_pHead = pTemp;
			g_pEnd = pTemp;
		}
		//不是空链表,直接尾添加
		else
		{
			g_pEnd->pNext = pTemp;
			pTemp->pPre = g_pEnd;   //2行代码意思为前连后,后连前
			g_pEnd = pTemp;  //尾指针调整位置
		}
		//节点数量++;
		g_iNodeCount++;
	}
}