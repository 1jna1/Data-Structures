#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ջ��ʵ����һ�ֶ����Ա�Ĳ�������,��ͬһ�˽��в���ɾ������
:ͷ���/ɾ��  β���/ɾ��*/


//˫��ѭ������ʵ��ջ
struct Node
{
	int iData;
	struct Node* pNext;
	struct Node* pPre;
};

//������ͷ
struct Node* Stack(void);
//�ж��Ƿ�Ϊ��ջ    //���ǿ��Ƿ�Ϊ������
bool IsEmpty(struct Node* pStack);
//ѹջ       //��ʵ����β���
void Push(struct Node* pStack, int iData);
//�ͷ�ջ         //�ͷ�����(����д�İ����ͷſ�ͷ)
void FreeStack(struct Node** pStack);
//��ȡջ����           //��ʵ�����ҵ�β�ڵ�
struct Node* Top(struct Node* pStack);
//ɾ��ջ���������
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

	//��ת����
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

//ɾ��ջ���������
void Pop(struct Node* pStack)
{
	//�ȼ��ջ�Ƿ�Ϊ��
	if (IsEmpty(pStack))
	{
		return NULL;
	}

	struct Node* pTemp = pStack->pPre; //��¼Ҫɾ���Ľڵ�
	pTemp->pPre->pNext = pStack;
	pStack->pPre = pTemp->pPre;   //��������
	free(pTemp);   //ɾ��ջ����
}

//��ȡջ����           //��ʵ�����ҵ�β�ڵ�
struct Node* Top(struct Node* pStack)
{
	//�ȼ��ջ�Ƿ�Ϊ��
	if (IsEmpty(pStack))
	{
		return NULL;
	}
	return pStack->pPre;
}

//�ͷ�ջ
//���ﴫ����ָ���ԭ����:�ͷ����ͷ�Ժ�,Ҫ�ı�pStack��ָ��,����ָ���
void FreeStack(struct Node** pStack)
{
	//�����Ϸ��Լ��
	if (NULL == *pStack)
	{
		return;
	}
	struct Node* pTemp = *pStack;
	//������Ҫ�ͷſ�ͷ,����������do-whileѭ��,Ϊ��������һ��,����ʹ��
	//whileѭ����ֱ������ѭ��
	do
	{
		//��¼��ǰ�ڵ�
		struct Node* pT = pTemp;
		pTemp = pTemp->pNext;
		free(pT);

	} while (pTemp != (*pStack));
	*pStack = NULL;
}

//ѹջ
void Push(struct Node* pStack, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == pStack)
	{
		return;
	}
	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)      //����ռ�ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;
		//�ڵ����ӵ�������
		pTemp->pNext = pStack;
		pTemp->pPre = pStack->pPre;
		pStack->pPre->pNext = pTemp;
		pStack->pPre = pTemp;
	}
}

//������ͷ
struct Node* Stack(void)
{
	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp == NULL)
	{
		return NULL;
	}

	//�ڵ��Ա��ֵ
	pTemp->iData = -1;
	pTemp->pNext = pTemp;
	pTemp->pPre = pTemp;

	return pTemp;
}

//�ж��Ƿ�Ϊ��ջ
bool IsEmpty(struct Node* pStack)
{
	if (NULL==pStack || pStack->pNext == pStack)
	{
		return true;
	}
	return false;
}