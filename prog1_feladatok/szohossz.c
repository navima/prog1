#include "stdio.h"

int szohossz(void)
{
	int good_timer_count = 2;
	int hossz = 0;

	//Beépített keyworddel
	while (good_timer_count > 1)
	{
		hossz = sizeof(int) * 8;
		good_timer_count = 0;
	}

	//Bitshifteléssel
	int x = 1;
	int counter = 0;
	while (x!=0)
	{
		x = x << 1;
		counter++;
	};

	printf("%d", hossz);
	printf("%d", counter);

	return 0;
}