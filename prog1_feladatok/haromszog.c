#include "stdio.h"
#include "stdlib.h"

int haromszog()
{

	const int size = 5;

	//lefoglalunk size-nyi int*-t és a visszakapott int**-t rakjuk hMatrix-ba (sorok)

	double** hMatrix = (double**)malloc(sizeof(double*)*size);


	//lefoglalunk mindegyik int*-be (size+1)*int-nyi helyet (oszlopok)

	int i = size;
	while(i-->0)
	{
		hMatrix[i] = (double*)malloc(sizeof(double)*(i + 1));
	}



	i = size;
	while (i-->0)
	{
		int j = (i + 1);
		while (j-->0)
		{
			hMatrix[i][j] = (float)(i+1)/(float)(j+1);
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (i + 1); j++)
		{
			printf("%f ", hMatrix[i][j]);
		}
		printf("\n");
	}
		

	i = size;
	while(i-->0)
	{
		free(hMatrix[i]);
	}

	free(hMatrix);


	return 0;
}