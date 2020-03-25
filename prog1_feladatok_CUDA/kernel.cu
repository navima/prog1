#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

__global__ void mappingSquareKernel(unsigned short int* dest, const float* cReal, const float* cImag)
{
	int i = threadIdx.x + (blockIdx.x*blockDim.x);

	float zRealLoc = cReal[i];
	float zImagLoc = cImag[i];

	int k = 0;

	for (k = 0; k < 64; k++)
	{
		float temp = zRealLoc * zRealLoc - zImagLoc * zImagLoc + cReal[i];
		zImagLoc = 2.0 * zRealLoc * zImagLoc + cImag[i];
		zRealLoc = temp;

		if (fabs(zRealLoc) > 2.0 || fabs(zImagLoc) > 2.0)
			break;
	}

	dest[i] = k;
}

__global__ void mappingBiomKernel(unsigned short int* dest, const float* cReal, const float* cImag)
{
	int i = threadIdx.x + (blockIdx.x*blockDim.x);

	float zRealLoc = cReal[i];
	float zImagLoc = cImag[i];

	float dR = -0.8;
	float dI = 0.156;

	float vR = 0;
	float vI = 0;


	int k = 0;

	for (k = 0; k < 64; k++)
	{
		vR = zRealLoc * zRealLoc - zImagLoc * zImagLoc + dR;
		vI = 2.0 * zRealLoc * zImagLoc + dI;
		k++;

		zRealLoc = vR * vR - vI * vI + dR;
		zImagLoc = 2.0 * vR * vI + dI;

		if (fabs(zRealLoc) > 2.0 || fabs(zImagLoc) > 2.0)
			break;
	}

	dest[i] = k;
}

void mandelWithCuda(unsigned short int* iter, const float* bR, const float* bI, unsigned int WIDTH, unsigned int HEIGHT)
{
	unsigned int size = WIDTH * HEIGHT;

	float* dev_bR = 0;
	float* dev_bI = 0;
	unsigned short int* dev_iter = 0;

	cudaError asd;

	cudaSetDevice(0);

	asd = cudaMalloc((void**)&dev_iter, size * sizeof(unsigned short));
	asd = cudaMalloc((void**)&dev_bR, size * sizeof(float));
	asd = cudaMalloc((void**)&dev_bI, size * sizeof(float));


	asd = cudaMemcpy(dev_bR, bR, size * sizeof(float), cudaMemcpyHostToDevice);
	asd = cudaMemcpy(dev_bI, bI, size * sizeof(float), cudaMemcpyHostToDevice);


	dim3 dimBlock = dim3(std::min(1024u, size));;
	dim3 dimGrid = dim3(std::ceil((float)size / 1024));

	mappingSquareKernel << <dimGrid, dimBlock >> > (dev_iter, dev_bR, dev_bI);

	asd = cudaGetLastError();


	cudaDeviceSynchronize();

	cudaMemcpy(iter, dev_iter, size * sizeof(unsigned short), cudaMemcpyDeviceToHost);
}

int main()
{
	const unsigned int WIDTH = 512;
	const unsigned int HEIGHT = 512;

	float* bReal = new float[WIDTH*HEIGHT];
	float* bImag = new float[WIDTH*HEIGHT];
	unsigned short int* iter = new unsigned short int[WIDTH*HEIGHT];

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
		{
			bReal[i*HEIGHT + j] = (float)i / WIDTH * 4.0 - 2.0;
			bImag[i*HEIGHT + j] = (float)j / HEIGHT * 4.0 - 2.0;
		}


	mandelWithCuda(iter, bReal, bImag, WIDTH, HEIGHT);

	cudaDeviceReset();

	delete[] bReal;
	delete[] bImag;

	std::ofstream out;
	out.open("out.pgm");

	out << "P2\n";
	out << HEIGHT << " " << WIDTH << "\n";
	out << "63\n";

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++, out << "\n")
			out << iter[i*HEIGHT + j] << " ";

	out.close();

	//convert to png with 'magick out.pgm out.png'

	delete[] iter;
}