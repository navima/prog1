#pragma once
#include "stdio.h"

#define WIDTH 30
#define HEIGHT 30

int testC();
float pixelXtoRealC(int x);
float pixelYtoImaginaryC(int y);
int mandelC(float real, float imaginary);
int mappingSquareC(float Zreal, float Zimaginary, float Creal, float Cimaginary, float* realDest, float* imaginaryDest);