//#include "stdio.h"

#include "mandelbrot.h"

//#define WIDTH 50
//#define HEIGHT 100

int testC()
{
	int pontok[WIDTH][HEIGHT];

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			pontok[i][j] = mandelC(pixelXtoRealC(i), pixelYtoImaginaryC(j));
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

float pixelXtoRealC(int x)
{
	float min = -2;
	float size = 3;
	return ((float)x / (float)WIDTH) * size + min;
}

float pixelYtoImaginaryC(int y)
{
	float min = -1;
	float size = 2;
	return ((float)y / (float)HEIGHT) * size + min;
}

int mandelC(float real, float imaginary)
{
	float Zreal = 0;
	float Zimaginary = 0;
	int i = 0;

	while(i<25 && Zreal<2 && Zimaginary<2)
	{
		mappingSquareC(Zreal, Zimaginary, real, imaginary, &Zreal, &Zimaginary);
		i++;
	}

	return i;
}

int mappingSquareC(float Zreal, float Zimaginary, float Creal, float Cimaginary, float* realDest, float* imaginaryDest)
{
	
	float temp = Zreal * Zreal - Zimaginary * Zimaginary + Creal;
	*imaginaryDest = 2.0 * Zreal * Zimaginary + Cimaginary;
	*realDest = temp;

	return 0;
}