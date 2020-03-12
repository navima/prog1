#include "mandelbrot2.hpp"

constexpr auto WIDTH = 50;
constexpr auto HEIGHT = 100;
constexpr auto maxIter = 25;

float pixelXtoReal(int x)
{
	float min = -2;
	float size = 4;
	return ((float)x / (float)WIDTH) * size + min;
}

float pixelYtoImaginary(int y)
{
	float min = -2;
	float size = 4;
	return ((float)y / (float)HEIGHT) * size + min;
}

template <typename T>
std::complex<T> mappingSquare(std::complex<T> Z, std::complex<T> C)
{
	return Z * Z + C;
}

int mandel(float real, float imaginary)
{
	std::complex<float> Z(0, 0);
	std::complex<float> C(real, imaginary);

	int i = 0;

	while (i < maxIter && Z.real() < 2 && Z.imag() < 2)
	{
		Z = mappingSquare(Z, C);
		i++;
	}

	return i;
}

int biom(float real, float imaginary)
{
	std::complex<float> Z(real, imaginary);
	std::complex<float> D(-0.8, 0.156);
	std::complex<float> V(0, 0);
	float R = 2;


	int i = 0;

	for(i = 0;i<maxIter;i++)
	{
		V = mappingSquare(Z, D);
		Z = mappingSquare(V, D);
		i++;

		if (abs(Z) > R)
			break;
	}

	return i;
}

int test()
{
	char pontok[WIDTH][HEIGHT];

	std::string chars = " .:!#ß";

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			pontok[i][j] = biom(pixelXtoReal(i), pixelYtoImaginary(j));

			printf("%c", chars[(float)pontok[i][j]/maxIter*(chars.length()-1)]);
		}
		printf("\n");
	}

	return 0;
}