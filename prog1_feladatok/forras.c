#include <stdio.h>

int f()
{
	return 0;
}

int forras()
{
	int i;
	int tomb[4];
	int* d = 0;
	int* s = 0;
	int n = 0;
	int a = 0;
	for (i = 0; i < 5; ++i) {}
	for (i = 0; i < 5; i++) {}
	for (i = 0; i < 5; tomb[i] = i++) {}
	for (i = 0; i < n && (*d++ = *s++); ++i) {}
	printf("%d %d", f(a, ++a), f(++a, a));
	printf("%d %d", f(a), a);
	printf("%d %d", f(&a), a);
}