#include <stdio.h>
#include <math.h>

int pageRank()
{
	//link values matrix
	float linkMatrix[4][4] = {	{0, 0, 1.f/3.f, 0},
								{1, 0.5f, 1.f/3.f, 1},
								{0, 0.5f, 0, 0},
								{0, 0, 1.f/3.f, 0}
							 };

	//if deltaSum and newsum differ by less than this, we break
	//precision?
	const float epsilon = 0.01f;

	//rank of pages
	float pages[4] = { 0,0,0,0};

	//previous rank of pages
	float pagesDef[4] = { 1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0 };

	//main loop
	for (int it = 0; it < 1000; it++)
	{
		//perform the matrix multiplication
		for (int i = 0; i < 4; i++)
		{
			pages[i] = 0;
			for (int j = 0; j < 4; j++)
			{
				pages[i] += linkMatrix[i][j] * pagesDef[j];
			}
		}
		
		//refresh the previous deltaSum and the previous "pages"
		float deltaSum = 0;
		for (int i = 0; i < 4; i++)
		{
			deltaSum += (float) fabs((double)pages[i]-(double)pagesDef[i]);
			pagesDef[i] = pages[i];
		}
		printf("%i: %f %f %f %f\n",it,pagesDef[0], pagesDef[1], pagesDef[2], pagesDef[3]);

		if (deltaSum < epsilon)
			break;
	}

	return 0;
}