#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;  //数据
	struct Node* pNext;   //存放下一个节点的地址
	struct Node* pPre;    //存放上一个节点的地址
};


//尾添加
void AddToEnd(struct Node** pHead,struct Node** pEnd,int* pCount,int iData);
//释放链表
void FreeList(struct Node** pHead, struct Node** pEnd,int* pCount);
//正向遍历链表
void LookZheng(struct Node* pHead, int* pCount);
//头删除
struct Node* GetHead(struct Node** pHead, struct Node** pEnd, int* pCount);
//合并链表
void HeBing(struct Node** g_A_pHead, struct Node** g_A_pEnd, int* g_A_iNodeCount, struct Node** g_B_pHead, struct Node** g_B_pEnd, int* g_B_iNodeCount);

int main(void)
{	
	struct Node* g_A_pHead = NULL;    //初始化头指针
	struct Node* g_A_pEnd = NULL;    //初始化尾指针
	int g_A_iNodeCount = 0;    //记录节点数量

	struct Node* g_B_pHead = NULL;    //初始化头指针
	struct Node* g_B_pEnd = NULL;    //初始化尾指针
	int g_B_iNodeCount = 0;    //记录节点数量

	//1 5 2 8 10
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 1);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 5);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 2);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 8);
	AddToEnd(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, 10);
	//2 6 9
	AddToEnd(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount, 2);
	AddToEnd(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount, 6);
	AddToEnd(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount, 9);

	HeBing(&g_A_pHead, &g_A_pEnd, &g_A_iNodeCount, &g_B_pHead, &g_B_pEnd, &g_B_iNodeCount);

	LookZheng(g_A_pHead, &g_A_iNodeCount);
	LookZheng(g_B_pHead, &g_B_iNodeCount);

	FreeList(&g_A_pHead,&g_A_pEnd, &g_A_iNodeCount);
	FreeList(&g_B_pHead, &g_B_pEnd, &g_B_iNodeCount);

	system("pause>0");
	return 0;
}

//合并链表
void HeBing(struct Node** g_A_pHead, struct Node** g_A_pEnd, int* g_A_iNodeCount, struct Node** g_B_pHead, struct Node** g_B_pEnd, int* g_B_iNodeCount)
{
	//参数合法性检测
	if (NULL == g_A_pHead || NULL == *g_A_pHead || NULL == g_B_pHead || NULL == *g_B_pHead)
	{
		return;
	}
	while (1)
	{
		//获取A链表的头
		struct Node* pTemp= GetHead(g_A_pHead, g_A_pEnd, g_A_iNodeCount);
		if (pTemp == NULL)
		{
			break;
		}
		//把A链表中取下来的头节点按照大小连接在B链表中
		//比B头节点小(头添加)
		if (pTemp->iData <= (*g_B_pHead)->iData)
		{
			pTemp->pNext = *g_B_pHead;
			(*g_B_pHead)->pPre = pTemp;
			*g_B_pHead = pTemp;
			(*g_B_iNodeCount)++;
		}
		//比B尾节点大(尾添加)
		else if (pTemp->iData >= (*g_B_pEnd)->iData)
		{
			(*g_B_pEnd)->pNext = pTemp;
			pTemp->pPre = *g_B_pEnd;
			*g_B_pEnd = pTemp;
			(*g_B_pEnd)->pNext = NULL;
			(*g_B_iNodeCount)++;
		}
		else
		{
			struct Node* pT = *g_B_pHead;
			while (pT->pNext != NULL)
			{
				//中间
				if (pTemp->iData >= pT->iData && pTemp->iData <= pT->pNext->iData)
				{
					//新节点与后面节点相连
					pTemp->pNext = pT->pNext;
					pT->pNext->pPre = pTemp;
					//新节点与前面节点相连
					pT->pNext = pTemp;
					pTemp->pPre = pT;
					//节点数量++
					(*g_B_iNodeCount)++;
					break;
				}
				pT = pT->pNext;
			}
		}
	}
}

//头删除
struct Node* GetHead(struct Node** pHead, struct Node** pEnd, int* pCount)
{
	//参数合法性检测
	if (NULL == pHead || NULL == *pHead)
	{
		return NULL;
	}
	//记录当前头节点
	struct Node* pTemp = *pHead;
	//删除头  
	if (*pHead == *pEnd)     //只有一个节点
	{
		*pHead = NULL;
		*pEnd = NULL;
		(*pCount)--;
	}
	else
	{
		*pHead = (*pHead)->pNext;
		(*pCount)--;
	}
	return pTemp;
}

//正向遍历链表
void LookZheng(struct Node* pHead, int* pCount)
{
	if (pHead == NULL)
	{
		return;
	}
	printf("共有%d个节点:", *pCount);
	//循环遍历链表
	struct Node* pTemp = pHead;
	while (pTemp != NULL)
	{
		printf("%d ", pTemp->iData);

		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

//释放链表
void FreeList(struct Node** pHead, struct Node** pEnd, int* pCount)
{
	if (NULL == *pHead)
	{
		return;
	}
	//定义中间变量
	struct Node* pTemp = *pHead;
	//遍历链表,逐个释放
	while (pTemp != NULL)
	{
		//记录当前节点
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);
		*pCount = 0;//清空计数
	}
	*pHead = NULL;
	*pEnd = NULL;
}

//尾添加
void AddToEnd(struct Node** pHead, struct Node** pEnd, int* pCount, int iData)
{
	//参数合法性检测
	if (*pCount < 0)
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
		if (*pHead == NULL)
		{
			*pHead = pTemp;
			*pEnd = pTemp;
		}
		//不是空链表,直接尾添加
		else
		{
			(*pEnd)->pNext = pTemp;
			pTemp->pPre = *pEnd;   //2行代码意思为前连后,后连前
			*pEnd = pTemp;  //尾指针调整位置
		}
		//节点数量++;
		(*pCount)++;
	}
}