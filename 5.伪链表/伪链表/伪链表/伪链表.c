#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int val;
	struct Node* pNext;
};

void look(struct Node* pHead);
struct Node* FindbyData(struct Node* pHead, int data);
struct Node* FindbyIndex(struct Node* pHead, int Index);
void ShowData(struct Node* pNode);
int Count(struct Node* pHead, int data);
void GetNode(struct Node* pHead, struct Node* arr[4], int data);
void ChangebyData(struct Node* pHead, int used_data, int now_data);
void ChangebyIndex(struct Node* pHead, int Index, int now_data);

int main(void)
{
	struct Node a = { 3,NULL }, 
		        b = { 7,NULL }, 
		        c = { 5,NULL }, 
		        d = { 9,NULL };
	struct Node* arr[4] = { NULL };
	a.pNext = &b;
	b.pNext = &c;
	c.pNext = &d;
	//头添加
	//struct Node g = { 0,&a };
	//尾添加
	//struct Node h = { 4,NULL };
	//d.pNext = &h;
	//中间添加
	//struct Node f = { 35,NULL };
	//f.pNext = &d;
	//c.pNext = &f;

	//头删除
	//a.pNext = NULL;
	//尾删除
	//c.pNext = NULL;

	//删除中间节点
	//b.pNext = c.pNext;

	//ChangebyData(&a, 3, 8);
	ChangebyIndex(&a, 3, 8);
	look(&a);


	/*GetNode(&a,arr,7);
	for (int i = 0; i<4 && arr[i]!=NULL ; i++)
	{
		printf("数据:%d\n", arr[i]->val);
	}*/

	/*ShowData(FindbyData(&a, 8));
	ShowData(FindbyIndex(&a, 2));*/
	//printf("要查找的数据的数量:%d\n",Count(&a, 3));


	system("pause>0");
	return 0;
}

void ChangebyIndex(struct Node* pHead, int Index, int now_data)
{
	struct Node* pFind =FindbyIndex(pHead,Index);
	while (pHead != NULL)
	{
		if (pFind != NULL)
		{
			pFind->val = now_data;
		}
		pHead = pHead->pNext;
	}
}

void ChangebyData(struct Node* pHead, int used_data, int now_data)
{
	struct Node* pFind=FindbyData(pHead, used_data);
	while (pHead != NULL)
	{
		if (pFind!=NULL)
		{
			pFind->val = now_data;
		}
		pHead = pHead->pNext;
	}
}

void GetNode(struct Node* pHead, struct Node* arr[4], int data)
{
	int Index = 0;
	while (pHead != NULL)
	{
		if (pHead->val == data)
		{
			arr[Index] = pHead;
			Index++;
		}
		pHead = pHead->pNext;
	}
}

int Count(struct Node* pHead, int data)
{
	int Num = 0;
	while (pHead != NULL)
	{
		if (pHead->val == data)
		{
			Num++;
		}
		pHead = pHead->pNext;
	}
	return Num;
}

void ShowData(struct Node* pNode)
{
	if (pNode == NULL)
	{
		printf("查无此节点!\n");
	}
	else
	{
		printf("查有此节点,数据:%d\n", pNode->val);
	}
}

void look(struct Node* pHead)
{
	while (pHead != NULL)
	{
		printf("%d\n", pHead->val);
		pHead = pHead->pNext;
	}
}

struct Node* FindbyData(struct Node* pHead, int data)
{
	while (pHead != NULL)
	{
		if (pHead->val == data)
			return pHead;
		pHead = pHead->pNext;
	}
	return NULL;
}

struct Node* FindbyIndex(struct Node* pHead, int Index)
{
	int iNum = 0;
	while (pHead != NULL)
	{
		if (iNum == Index)
		{
			return pHead;
		}

		iNum++;
		pHead = pHead->pNext;
	}
	return NULL;
}