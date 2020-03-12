#pragma once

#include "stdio.h"
#include <complex>

float pixelXtoReal(int x);

float pixelYtoImaginary(int y);

template <typename T>
std::complex<T> mappingSquare(std::complex<T> Z, std::complex<T> C);

int mandel(float real, float imaginary);

int test();