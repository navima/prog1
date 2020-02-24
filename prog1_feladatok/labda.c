#include <math.h>

int labda()
{
	//location of ball
	int x = 1;
	int y = 1;

	//velocity of ball
	int vx = 1;
	int vy = 1;

	while (1)
	{
		//maximum bounds
		int max_x = 15;
		int max_y = 10;

		//minimum bounds
		int min_x = 0;
		int min_y = 0;

		//bounds check
		vx *= trunc((max_x - (x + 0.5)) / fabs((max_x - (x + 0.5))));
		vy *= trunc((max_y - (y + 0.5)) / fabs((max_y - (y + 0.5))));

		vx *= trunc((min_x + (x - 0.5)) / fabs((min_x + (x - 0.5))));
		vy *= trunc((min_y + (y - 0.5)) / fabs((min_y + (y - 0.5))));

		//applying velocity
		x += vx;
		y += vy;
	}

	return 0;
}