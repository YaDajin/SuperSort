#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100000//数组长度最大取值：256375
/*超级排序*/
inline int sort(unsigned int *a, int len)
{
	unsigned int *b = malloc(sizeof(unsigned) * len);
	int sum[256] = { 0 }, sum1[256] = { 0 }, sum2[256] = { 0 }, sum3[256] = { 0 };
	for (int i = 0; i < len; i++)
	{
		++sum[a[i] & 255];
		++sum1[(a[i] >> 8) & 255];
		++sum2[(a[i] >> 16) & 255];
		++sum3[a[i] >> 24];
	}
	for (int q = 1; q <= 255; ++q)
	{
		sum[q] += sum[q - 1];
		sum1[q] += sum1[q - 1];
		sum2[q] += sum2[q - 1];
		sum3[q] += sum3[q - 1];
	}
	for (int q = len - 1; q >= 0; --q)
		b[--sum[a[q] & 255]] = a[q];
	for (int q = len - 1; q >= 0; --q)
		a[--sum1[(b[q] >> 8) & 255]] = b[q];
	for (int q = len - 1; q >= 0; --q)
		b[--sum2[(a[q] >> 16) & 255]] = a[q];
	for (int q = len - 1; q >= 0; --q)
		a[--sum3[b[q] >> 24]] = b[q];
	free(b);
	return *a;
}
/*打印数组*/
void printArray(int *a, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
int main(void)
{
	int array[LEN] = { 0 };//只支持整数排序
	clock_t begin, end;     //捕获时间变量
	double cost;			//运行时间
	srand((unsigned)time(NULL));
	for (int i = 0; i < LEN; i++)
	{
		array[i] = rand() % 100;
	}
	//printf("排序前：");
	//printArray(array, LEN);
	begin = clock();
	*array = sort(array, LEN);
	end = clock();
	cost = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("排序后：");
	//printArray(array,LEN);
	printf("\n排序时消耗的时间: %lf secs\n", cost);
}
