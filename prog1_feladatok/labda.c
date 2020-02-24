#include <math.h>

int print(int x, int y)
{
	return 0;
}

int getBounds(int* bounds) // {xmin ymin xmax ymax}
{
	bounds[0] = 0;
	bounds[1] = 0;
	bounds[2] = 15;
	bounds[3] = 8;
	return 0;
}

int labda_if()
{
	int x = 1;
	int y = 1;

	int vx = 1;
	int vy = 1;

	int xmin = 0;
	int ymin = 0;

	int xmax = 10;
	int ymax = 5;

	while (1)
	{
		//get bounds
		int bounds[4];
		getBounds(bounds);

		xmin = bounds[0];
		ymin = bounds[1];
		xmax = bounds[2];
		ymax = bounds[3];


		//bounds check
		if ((x+1) > xmax)
			vx *= -1;
		if ((y+1) > ymax)
			vy *= -1;
		if ((x-1) < xmin)
			vx *= -1;
		if ((y-1) < ymin)
			vy *= -1;

		//apply velocity
		x += vx;
		y += vy;

		//print
		print(x, y);
	}
}

int labda_ifless()
{
	int x = 1;
	int y = 1;

	int vx = 1;
	int vy = 1;

	int xmin = 0;
	int ymin = 0;

	int xmax = 10;
	int ymax = 5;

	while (1)
	{
		//get bounds
		int bounds[4];
		getBounds(bounds);

		xmin = bounds[0];
		ymin = bounds[1];
		xmax = bounds[2];
		ymax = bounds[3];

		//bounds check

		//max
		vx *= (xmax - (x + 0.5)) / (fabs(xmax - (x + 0.5)));
		vy *= (ymax - (y + 0.5)) / (fabs(ymax - (y + 0.5)));

		//min
		vx *= (xmin + (x - 0.5)) / (fabs(xmin + (x - 0.5)));
		vy *= (ymin + (y - 0.5)) / (fabs(ymin + (y - 0.5)));

		//apply velocity
		x += vx;
		y += vy;

		//print
		print(x, y);
	}
}