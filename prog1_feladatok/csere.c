#include <limits.h>

int csere_seged()
{
	int a = 5;
	int b = 3;

	int t = a;
	a = b;
	b = t;

	return 0;
}

int csere_kiv()
{
	int a = INT_MIN;
	int b = INT_MAX;

	a = a - b;
	b = a + b;
	a = b - a;

	return 0;
}