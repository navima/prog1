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
		//***Update bounds here***
		int bounds[4] = getBounds(); //Order: {xmin, ymin, xmax, ymax}

		//minimum bounds
		int min_x = bounds[0];
		int min_y = bounds[1];

		//maximum bounds
		int max_x = bounds[2];
		int max_y = bounds[3];


		//bounds check
		vx *= trunc((max_x - (x + 0.5)) / fabs((max_x - (x + 0.5))));
		vy *= trunc((max_y - (y + 0.5)) / fabs((max_y - (y + 0.5))));

		vx *= trunc((min_x + (x - 0.5)) / fabs((min_x + (x - 0.5))));
		vy *= trunc((min_y + (y - 0.5)) / fabs((min_y + (y - 0.5))));

		//applying velocity
		x += vx;
		y += vy;

		//***Print here***
		print(x, y);
	}

	return 0;
}

int print(x, y)
{
	//Print code
}

int* getBounds() //Order: {xmin, ymin, xmax, ymax}
{
	int bounds[4] = { 0,0,15,10 };
	return bounds;
}