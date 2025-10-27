#include <stdio.h>

int main(void)
{
	for (int i = 1; i <10; i++)
	{
		for (int j = 1; j <10; j++)
		{
			printf("%dx%d=%2d ", i, j, i * j);
		}
		putchar('\n');
	}
	printf("\n");
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (i >= j)
			{
               printf("%dx%d=%2d ", i, j, i * j);
			}			
		}
		putchar('\n');
	}
	//printf("\n");
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (i <= j)
			{
				printf("%dx%d=%2d ", i, j, i * j);
			}
			else
			{
				printf("       ");
			}
		}
		putchar('\n');
	}
	printf("\n");
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (i + j >= 10)
			{
				printf("%dx%d=%2d ", i, j, i * j);
			}
			else
			{
				printf("       ");
			}
		}
		putchar('\n');
	}
	//printf("\n");
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (i+j<=10)
			{
				printf("%dx%d=%2d ", i, j, i * j);
			}
			/*else
			{
				printf("       ");
			}*/
		}
		putchar('\n');
	}

	return 0;
}