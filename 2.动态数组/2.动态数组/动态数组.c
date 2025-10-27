#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct DongShuZu
{
	int* pShuZuTou;
	unsigned int iRongliang;  //容量的大小
	unsigned int iShuliang;     //已存储的数据的数量
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
		printf("参数传递错误\n");
		return;
	}
	//后面的数据往前移
	for (int i = iWeiZhi; i < pDongShuZu->iShuliang - 1; i++)
	{
		pDongShuZu->pShuZuTou[i] = pDongShuZu->pShuZuTou[i + 1];
	}
	//数量--
	pDongShuZu->iShuliang--;
}

void ShiFangShuZu(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("参数错误\n");
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
		printf("参数错误\n");
		return;
	}
	pDongShuZu->iShuliang = 0;
}

void Init(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("参数错误\n");
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
		printf("参数错误\n");
		return;
	}
	//判断是否满了
	ZengJiaKongJian(&pDongShuZu);
	//把数据装入动态数组中
	pDongShuZu->pShuZuTou[pDongShuZu->iShuliang] = data;
	//存入数据的数量++
	pDongShuZu->iShuliang++;
}

void ShuChu(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("参数错误\n");
		return;
	}
	printf("容量:%u 数量:%u\n", pDongShuZu->iRongliang, pDongShuZu->iShuliang);
	printf("已存数据: ");

	for (unsigned int i = 0; i < pDongShuZu->iShuliang; i++)
	{
		printf("%u ", pDongShuZu->pShuZuTou[i]);
	}
	printf("\n");
}

void ZengJiaZhong(struct DongShuZu* pDongShuZu, int data, unsigned int iXiaBiao)
{
	//如果要插入数据的下标大于数量，则插在尾部
	if (NULL == pDongShuZu)
	{
		printf("参数错误\n");
		return;
	}
	//判断是否满了
	ZengJiaKongJian(&pDongShuZu);
	//下标过大
	if (iXiaBiao > pDongShuZu->iShuliang)
	{
		iXiaBiao = pDongShuZu->iShuliang;
	}
	//数据往后挪
	for (unsigned int i = pDongShuZu->iShuliang; i > iXiaBiao; i--)
	{
		pDongShuZu->pShuZuTou[i] = pDongShuZu->pShuZuTou[i - 1];
	}
	//把要插入的数据插到数组中
	pDongShuZu->pShuZuTou[iXiaBiao] = data;
	//数据的数量++
	pDongShuZu->iShuliang++;
}

void ZengJiaKongJian(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("参数错误\n");
		return;
	}
	//如果容量满了
	if (pDongShuZu->iShuliang == pDongShuZu->iRongliang)
	{
		//增加容量
		pDongShuZu->iRongliang += 10;

		//开辟更大的内存空间
		int* pTemp = (int*)malloc(sizeof(int) * pDongShuZu->iRongliang);

		memset(pTemp, 0, sizeof(int) * pDongShuZu->iRongliang);
		//把原先的数据复制到更大的内存空间
		for (unsigned int i = 0; i < pDongShuZu->iShuliang; i++)
		{
			pTemp[i] = pDongShuZu->pShuZuTou[i];
		}
		//释放原来的内存空间
		free(pDongShuZu->pShuZuTou);
		//将数组头指向新的内存空间
		pDongShuZu->pShuZuTou = pTemp;
	}
}

void ShanChuWei(struct DongShuZu* pDongShuZu)
{
	if (NULL == pDongShuZu)
	{
		printf("参数错误\n");
		return;
	}
	pDongShuZu->iShuliang--;
}