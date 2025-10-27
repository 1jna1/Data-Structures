#include <stdio.h>
#include <time.h>

time_t time_cnt;

struct tm* time_date;

char* time_str;

int main(void)
{
	//time(&time_cnt);
	time_cnt = 1672588795;

	time_date=localtime(&time_cnt);

	printf("%d\r\n", time_date->tm_year);

	return 0;
}