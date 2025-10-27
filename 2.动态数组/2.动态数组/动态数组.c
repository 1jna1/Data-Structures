#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct DongShuZu
{
	int* pShuZuTou;
	unsigned int iRongliang;  //�����Ĵ�С
	unsigned int iShuliang;     //�Ѵ洢�����ݵ�����
};

void Init(struct DongShuZu* pDongShuZu);
void ShuChu(struct DongShuZu* pDongShuZu);
void Zengjia(struct DongShuZu* pDongShuZu, int data);
void ZengJiaZhong(struct DongShuZu* pDongShuZu, int data, unsigned int iXiaBiao);
void ZengJiaKongJian(struct DongShuZu* pDongShuZu);
void ShanChuWei(struct DongShuZu* pDongShuZu);
void DeleteAll(struct DongShuZu* pDongShuZu);
void ShiFangShuZu(struct DongShuZu* pDongShuZu);
void DeleteZhong(struct DongShuZu* pDongShuZu,unsigned int iWeiZhi);
	

int main(void)
{
	struct DongShuZu stShuZu;

	Init(&stShuZu);

	Zengjia(&stShuZu, 3);
	Zengjia(&stShuZu, 2);
	Zengjia(&stShuZu, 1);
	ZengJiaZhong(&stShuZu, 5, 8);
	DeleteZhong(&stShuZu, 4);

	ShuChu(&stShuZu);

	return 0;
}

void DeleteZhong(struct DongShuZu* pDongShuZu, unsigned int iWeiZhi)
{
	if (NULL == pDongShuZu || iWeiZhi>pDongShuZu->iShuliang )
	{
		printf("�������ݴ���\n");
		return;
	}
	//�����������ǰ��
	for (int i = iWeiZhi; i < pDongShuZu->iShuliang - 1; i++)
	{
		pDongShuZu->pShuZuTou[i] = pDongShuZu->pShuZuTou[i + 1];
	}
	//����--
	pDongShuZu->iShuliang--;
}

void ShiFangShuZu(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	pDongShuZu->iShuliang = 0;
	pDongShuZu->iRongliang = 0;
	free(pDongShuZu->pShuZuTou);
	pDongShuZu->pShuZuTou = NULL;
}

void DeleteAll(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	pDongShuZu->iShuliang = 0;
}

void Init(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	pDongShuZu->iRongliang = 5;
	pDongShuZu->pShuZuTou = (int*)malloc(sizeof(int) * pDongShuZu->iRongliang);
	pDongShuZu->iShuliang = 0;
}

void Zengjia(struct DongShuZu* pDongShuZu, int data)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	//�ж��Ƿ�����
	ZengJiaKongJian(&pDongShuZu);
	//������װ�붯̬������
	pDongShuZu->pShuZuTou[pDongShuZu->iShuliang] = data;
	//�������ݵ�����++
	pDongShuZu->iShuliang++;
}

void ShuChu(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	printf("����:%u ����:%u\n", pDongShuZu->iRongliang, pDongShuZu->iShuliang);
	printf("�Ѵ�����: ");

	for (unsigned int i = 0; i < pDongShuZu->iShuliang; i++)
	{
		printf("%u ", pDongShuZu->pShuZuTou[i]);
	}
	printf("\n");
}

void ZengJiaZhong(struct DongShuZu* pDongShuZu, int data, unsigned int iXiaBiao)
{
	//���Ҫ�������ݵ��±���������������β��
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	//�ж��Ƿ�����
	ZengJiaKongJian(&pDongShuZu);
	//�±����
	if (iXiaBiao > pDongShuZu->iShuliang)
	{
		iXiaBiao = pDongShuZu->iShuliang;
	}
	//��������Ų
	for (unsigned int i = pDongShuZu->iShuliang; i > iXiaBiao; i--)
	{
		pDongShuZu->pShuZuTou[i] = pDongShuZu->pShuZuTou[i - 1];
	}
	//��Ҫ��������ݲ嵽������
	pDongShuZu->pShuZuTou[iXiaBiao] = data;
	//���ݵ�����++
	pDongShuZu->iShuliang++;
}

void ZengJiaKongJian(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	//�����������
	if (pDongShuZu->iShuliang == pDongShuZu->iRongliang)
	{
		//��������
		pDongShuZu->iRongliang += 10;

		//���ٸ�����ڴ�ռ�
		int* pTemp = (int*)malloc(sizeof(int) * pDongShuZu->iRongliang);

		memset(pTemp, 0, sizeof(int) * pDongShuZu->iRongliang);
		//��ԭ�ȵ����ݸ��Ƶ�������ڴ�ռ�
		for (unsigned int i = 0; i < pDongShuZu->iShuliang; i++)
		{
			pTemp[i] = pDongShuZu->pShuZuTou[i];
		}
		//�ͷ�ԭ�����ڴ�ռ�
		free(pDongShuZu->pShuZuTou);
		//������ͷָ���µ��ڴ�ռ�
		pDongShuZu->pShuZuTou = pTemp;
	}
}

void ShanChuWei(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("��������\n");
		return;
	}
	pDongShuZu->iShuliang--;
}