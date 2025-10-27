#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM 10


struct Node
{
	int arr[NUM];
	int index;
};

//����ջ
struct Node* Stack(void);
//�ж��Ƿ�Ϊ��
bool IsEmpty(struct Node* pStack);
//ѹջ
void Push(struct Node* pStack, int iData);
//�ͷ�ջ
void FreeStack(struct Node** pStack);
//��ȡջ������
int Top(struct Node* pStack);
//ɾ��ջ������
void Pop(struct Node* pStack);

int main(void)
{
	struct Node* pStack = Stack();
	if (pStack == NULL)
		return 1;

	int arr[5] = { 2,3,4,5,6 };

	Push(pStack, arr[0]);
	Push(pStack, arr[1]);
	Push(pStack, arr[2]);
	Push(pStack, arr[3]);
	Push(pStack, arr[4]);

	arr[0]= Top(pStack);
	Pop(pStack);
	arr[1] = Top(pStack);
	Pop(pStack);
	arr[2] = Top(pStack);
	Pop(pStack);
	arr[3] = Top(pStack);
	Pop(pStack);
	arr[4] = Top(pStack);
	Pop(pStack);


	FreeStack(&pStack);
	system("pause>0");
	return 0;
}

//ɾ��ջ������
void Pop(struct Node* pStack)
{
	if (IsEmpty(pStack))
	{
		return;
	}
	(pStack->index)--;
}

//��ȡջ������
int Top(struct Node* pStack)
{
	if (IsEmpty(pStack))
	{
		return 0;
	}
	return pStack->arr[(pStack->index) - 1];
}

//�ͷ�ջ
void FreeStack(struct Node** pStack)
{
	free(*pStack);
	*pStack = NULL;
}

//ѹջ
void Push(struct Node* pStack, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == pStack || pStack->index < 0 || pStack->index>=NUM)
	{
		return;
	}

	//������ӵ�ջ������
	pStack->arr[pStack->index] = iData;
	(pStack->index)++;
}

//�ж��Ƿ�Ϊ��
bool IsEmpty(struct Node* pStack)
{
	if (pStack == NULL || pStack->index == 0)
	{
		return true;
	}
	return false;
}

struct Node* Stack(void)
{
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp == NULL)
	{
		return NULL;
	}
	pTemp->index = 0;
	return pTemp;
}