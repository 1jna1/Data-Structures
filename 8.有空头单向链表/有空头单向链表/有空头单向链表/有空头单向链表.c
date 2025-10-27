#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int iData;
	struct Node* pNext;
};

//β���
void AddToTail(struct Node *stHead,int iData);
//�ͷ�����
void FreeList(struct Node* stHead);
//��������
void Look(struct Node stHead);
//ͷ���
void AddToHead(struct Node* stHead, int iData);
//��ָ�������ݺ������
void AddDataByPosData(struct Node* stHead, int iPosData, int iData);
//��ָ�����±�λ���������
void AddByIndex(struct Node* stHead, int iPosIndex, int iData);
//��ָ�����±�λ�����һЩ����
void AddSomeByIndex(struct Node* stHead, int iPosIndex,int iCount, int iData);
//ͨ�������ҵ��ڵ�
struct Node* FindNodeByData(struct Node* stHead, int iData);
//ͨ���±��ҵ��ڵ�
struct Node* FindNodeByIndex(struct Node* stHead, int iIndex);
//ͨ���±��޸Ľڵ�
void ChangeByIndex(struct Node* stHead, int iIndex, int iValue);
//ͨ�������޸Ľڵ�(�޸�������ͬ����)
void ChangeByData(struct Node* stHead, int Data, int iValue);
//ͨ���±�ɾ���ڵ�
void DeleteByIndex(struct Node* stHead,int iIndex);
//ͨ������ɾ���ڵ�(ɾ��������ͬ����)
void DeleteByData(struct Node* stHead, int iValue);
//ȥ�� **************************************(�в�����)
void DeleteSame(struct Node* stHead);



int main(void)
{
	//������ͷ
	struct Node stHead = { 0,NULL };  //��ͷ�е�����������¼�ڵ����
	

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
		printf("�ܱ�Ǹ��δ�ҵ��ýڵ�!\n");
	}*/
	/*struct Node* pT = FindNodeByData(&stHead, 8);
	Look(stHead);
	if (pT != NULL)
	{
		printf("%d ", pT->iData);
	}
	else
	{
		printf("�ܱ�Ǹ��δ�ҵ��ýڵ�!\n");
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

//ȥ��
void DeleteSame(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 1)
	{
		return;
	}

	//ѭ������,ȥ��(˫��ѭ��)
	struct Node* pWai = stHead;
	while (pWai->pNext != NULL)
	{
		struct Node* pNei = pWai;
		while (pNei->pNext != NULL)
		{
			if (pWai->iData == pNei->pNext->iData)
			{
				//�ҵ��˸ýڵ�,ɾ���ڵ�
				struct Node* pTemp = pNei->pNext;
				pNei->pNext = pTemp->pNext;
				free(pTemp);
				stHead->iData -= 1;
				continue;  //���������,��ôָ��������һ����©����ǰ�ڵ�
			}

			pNei = pNei->pNext;
		}

		pWai = pWai->pNext;
	}
}

//ͨ������ɾ���ڵ�(ɾ��������ͬ����)
void DeleteByData(struct Node* stHead, int iValue)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 0)
	{
		return;
	}
	//ѭ���ҵ��ڵ�
	struct Node* pTemp = stHead;
	while (pTemp->pNext != NULL)
	{
		if (pTemp->pNext->iData == iValue)
		{
			//��¼��ǰ�ڵ�,׼��ɾ��
			struct Node* pT = pTemp->pNext;
			pTemp->pNext = pT->pNext;
			free(pT);   //ɾ���ڵ�
			stHead->iData -= 1;
			continue;
		}
		pTemp = pTemp->pNext;
	}
}

//ͨ���±�ɾ���ڵ�
void DeleteByIndex(struct Node* stHead, int iIndex)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 0 || iIndex<0 || iIndex>stHead->iData - 1)
	{
		return;
	}
	//ѭ���ҵ��ڵ�ǰһ��λ��
	struct Node* pTemp = stHead;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	//��¼�ýڵ�λ��,׼���ͷ�
	struct Node* pT = pTemp->pNext;
	pTemp->pNext = pT->pNext;
	free(pT);
	stHead->iData -= 1;
}

//ͨ�������޸Ľڵ�(�޸�������ͬ����)
void ChangeByData(struct Node* stHead, int Data, int iValue)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 0)
	{
		return;
	}
	//�ҵ�������
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

//ͨ���±��޸Ľڵ�
void ChangeByIndex(struct Node* stHead, int iIndex, int iValue)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 0 || iIndex<0 || iIndex>stHead->iData - 1)
	{
		return;
	}
	//ѭ���ҵ�ָ���±�Ľڵ�
	struct Node* pTemp = stHead->pNext;
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	//�ҵ���,�޸�����
	pTemp->iData = iValue;
}

//ͨ���±��ҵ��ڵ�
struct Node* FindNodeByIndex(struct Node* stHead, int iIndex)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 0 || iIndex<0 || iIndex>stHead->iData - 1)
	{
		return NULL;
	}
	struct Node* pTemp = stHead->pNext;
	//�ҵ����±�(��������������Ѿ�����,����һ�����ҵ�)
	for (int i = 0; i < iIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

//ͨ�������ҵ��ڵ�
struct Node* FindNodeByData(struct Node* stHead, int iData)
{
	//�����Ϸ��Լ��
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

//��ָ�����±�λ�����һЩ����
void AddSomeByIndex(struct Node* stHead, int iPosIndex, int iCount, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || iPosIndex<0 || iPosIndex >stHead->iData)
	{
		return;
	}

	//�ҵ��ڵ�  (�Ҳ�������������Ѿ�������,���һ�����ҵ�)
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

//��ָ�����±�λ���������
void AddByIndex(struct Node* stHead, int iPosIndex, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || iPosIndex<0 || iPosIndex >stHead->iData)
	{
		return;
	}

	//�ҵ��ڵ�  (�Ҳ�������������Ѿ�������,���һ�����ҵ�)
	struct Node* pTemp = stHead;
	for (int i = 0; i < iPosIndex; i++)
	{
		pTemp = pTemp->pNext;
	}
	AddToHead(pTemp, iData);
	pTemp->iData -= 1;
	stHead->iData += 1;
}

//��ָ�������ݺ������
void AddDataByPosData(struct Node* stHead, int iPosData, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData <= 0)
	{
		return;
	}

	//���������ҵ�������λ��
	struct Node* pTemp = stHead->pNext;
	while (pTemp != NULL)
	{
		if (pTemp->iData == iPosData)
		{
			break;
		}
		pTemp = pTemp->pNext;
	}
	//û�ҵ�
	if (NULL == pTemp)
	{
		printf("���޴˽ڵ�!\n");
	}
	else  //�ҵ���
	{
		AddToHead(pTemp, iData);
		pTemp->iData -= 1;
		stHead->iData += 1;
	}
}

//ͷ���
void AddToHead(struct Node* stHead, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead)
	{
		return;
	}
	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (pTemp != NULL)    //�ڵ㴴���ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;
		//�ѽڵ���������
		pTemp->pNext = stHead->pNext;
		stHead->pNext = pTemp;
		//�ڵ�����++
		stHead->iData++;
	}
}

//��������
void Look(struct Node stHead)
{
	struct Node* pTemp = stHead.pNext;
	printf("����%d������:", stHead.iData);
	while (pTemp != NULL)
	{
		printf("%d  ", pTemp->iData);

		pTemp = pTemp->pNext;
	}
	putchar('\n');
}

void AddToTail(struct Node* stHead, int iData)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || stHead->iData  < 0)
	{
		return;
	}

	//�����ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));

	if (pTemp != NULL)     //�����ڵ�ɹ�
	{
		//�ڵ��Ա��ֵ
		pTemp->iData = iData;
		pTemp->pNext = NULL;

		//�ѽڵ�������
		struct Node* pT = stHead;   //��ͷ������ָ����һ������Ȼ�Ҳ�����
		while (pT->pNext != NULL)
		{
			pT = pT->pNext;
		}

		pT->pNext = pTemp;
		//������++
		stHead->iData++;
	}
}

//�ͷ�����
void FreeList(struct Node* stHead)
{
   //�����Ϸ��Լ��
   if (NULL == stHead || stHead->iData <= 0)
   {
	 return;
   }
   //�ͷŸ����ڵ�
   struct Node* pTemp = stHead->pNext;
   while (pTemp != NULL )
   {
	   //��¼��ǰ�ڵ�
	   struct Node* pT = pTemp;
	   //�ڵ�����
	   pTemp = pTemp->pNext;
	   //�ͷŵ�ǰ�ڵ�
	   free(pT);
   }
   stHead->iData  = 0;
   stHead->pNext = NULL;
}