#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* 栈其实就是一种对线性表的操作方法,在同一端进行插入删除操作
:头添加/删除  尾添加/删除*/


//双向循环链表实现栈
struct Node
{
	int iData;
	struct Node* pNext;
	struct Node* pPre;
};

//创建空头
struct Node* Stack(void);
//判断是否为空栈    //就是看是否为空链表
bool IsEmpty(struct Node* pStack);
//压栈       //其实就是尾添加
void Push(struct Node* pStack, int iData);
//释放栈         //释放链表(这里写的包括释放空头)
void FreeStack(struct Node** pStack);
//获取栈顶点           //其实就是找到尾节点
struct Node* Top(struct Node* pStack);
//删除栈顶点的数据
void Pop(struct Node* pStack);


int main(void)
{
	struct Node* pStack = Stack();

	/*Push(pStack, 1);
	Push(pStack, 2);
	Push(pStack, 3);
	Push(pStack, 4);
	Push(pStack, 5);*/


	/*struct Node* p=Top(pStack);
	Pop(pStack);
	p = Top(pStack);
	Pop(pStack);
	p = Top(pStack);
	Pop(pStack);*/

	//翻转数组
	int arry[5] = { 1,2,3,4,5 };
	//struct Node* p = Top(pStack);

	Push(pStack, arry[0]);
	Push(pStack, arry[1]);
	Push(pStack, arry[2]);
	Push(pStack, arry[3]);
	Push(pStack, arry[4]);

	arry[0] = Top(pStack)->iData;
	Pop(pStack);
	arry[1] = Top(pStack)->iData;
	Pop(pStack);
	arry[2] = Top(pStack)->iData;
	Pop(pStack);
	arry[3] = Top(pStack)->iData;
	Pop(pStack);
	arry[4] = Top(pStack)->iData;
	Pop(pStack);


	FreeStack(&pStack);
	system("pause>0");
	return 0;
}

//删除栈顶点的数据
void Pop(struct Node* pStack)
{
	//先检测栈是否为空
	if (IsEmpty(pStack))
	{
		return NULL;
	}

	struct Node* pTemp = pStack->pPre; //记录要删除的节点
	pTemp->pPre->pNext = pStack;
	pStack->pPre = pTemp->pPre;   //连接链表
	free(pTemp);   //删除栈顶点
}

//获取栈顶点           //其实就是找到尾节点
struct Node* Top(struct Node* pStack)
{
	//先检测栈是否为空
	if (IsEmpty(pStack))
	{
		return NULL;
	}
	return pStack->pPre;
}

//释放栈
//这里传二级指针的原因是:释放完空头以后,要改变pStack的指向,让它指向空
void FreeStack(struct Node** pStack)
{
	//参数合法性检测
	if (NULL == *pStack)
	{
		return;
	}
	struct Node* pTemp = *pStack;
	//由于需要释放空头,因此这里采用do-while循环,为了跳过第一步,否则使用
	//while循环会直接跳出循环
	do
	{
		//记录当前节点
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);

	} while (pTemp != (*pStack));
	*pStack = NULL;
}

//压栈
void Push(struct Node* pStack, int iData)
{
	//参数合法性检测
	if (NULL == pStack)
	{
		return;
	}
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)      //申请空间成功
	{
		//节点成员赋值
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;
		//节点连接到链表上
		pTemp->pNext = pStack;
		pTemp->pPre = pStack->pPre;
		pStack->pPre->pNext = pTemp;
		pStack->pPre = pTemp;
	}
}

//创建空头
struct Node* Stack(void)
{
	//创建节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp == NULL)
	{
		return NULL;
	}

	//节点成员赋值
	pTemp->iData = -1;
	pTemp->pNext = pTemp;
	pTemp->pPre = pTemp;

	return pTemp;
}

//判断是否为空栈
bool IsEmpty(struct Node* pStack)
{
	if (NULL==pStack || pStack->pNext == pStack)
	{
		return true;
	}
	return false;
}