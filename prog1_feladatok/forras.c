#include <stdio.h>

int f(int a, int b);
int g(int a);
int h(int* a);

int forras(void)
{
	int i;
	int tomb[4];
	int* d = 0;
	int* s = 0;
	int n = 6;
	int a = 0;
	for (i = 0; i < 5; ++i) 
	{
		printf("%d", i);
	}
	printf("\n");
	for (i = 0; i < 5; i++)
	{
		printf("%d", i);
	}
	for (i = 0; i < 5; tomb[i] = i++) {}
	for (i = 0; i < n && (*d++ = *s++); ++i)
	{
		printf("");
	}
	printf("%d %d", f(a, ++a), f(++a, a));
	printf("%d %d", g(a), a);
	printf("%d %d", h(&a), a);
	
	return 0;
}

int f(int a, int b)
{
	return 0;
}

int g(int a)
{
	return 0;
}

int h(int* a)
{
	return 0;
}