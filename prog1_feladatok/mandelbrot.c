#include "stdio.h"

#define WIDTH 50
#define HEIGHT 100

float pixelXtoReal(int);
float pixelYtoImaginary(int);
int mandel(float, float);
int mappingSquare(float, float, float, float, float*, float*);

int test()
{
	int pontok[WIDTH][HEIGHT];

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			pontok[i][j] = mandel(pixelXtoReal(i), pixelYtoImaginary(j));
			if (pontok[i][j] == 25)
			{
				printf("#");
			}
			else if (pontok[i][j] > 15)
			{
				printf(".");
			}else
			{
				printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}

float pixelXtoReal(int x)
{
	float min = -2;
	float size = 3;
	return ((float)x / (float)WIDTH) * size + min;
}

float pixelYtoImaginary(int y)
{
	float min = -1;
	float size = 2;
	return ((float)y / (float)HEIGHT) * size + min;
}

int mandel(float real, float imaginary)
{
	float Zreal = 0;
	float Zimaginary = 0;
	int i = 0;

	while(i<25 && Zreal<2 && Zimaginary<2)
	{
		mappingSquare(Zreal, Zimaginary, real, imaginary, &Zreal, &Zimaginary);
		i++;
	}

	return i;
}

int mappingSquare(float Zreal, float Zimaginary, float Creal, float Cimaginary, float* realDest, float* imaginaryDest)
{
	
	float temp = Zreal * Zreal - Zimaginary * Zimaginary + Creal;
	*imaginaryDest = 2.0 * Zreal * Zimaginary + Cimaginary;
	*realDest = temp;

	return 0;
}