#pragma once
#include <stdlib.h>
#include <iostream>

template <typename T>
class polar
{
private:
	T value;
	bool valid = false;
	void calcValue()
	{
		value = (T)rand();
	}
public:
	T getValue()
	{
		if (valid)
		{
			return value;
		}
		else
		{
			calcValue();
			valid = true;
			return value;
		}
	}
};

void test()
{
	polar<int> asd1;
	polar<int> asd2;

	std::cout << asd1.getValue() << "\n";
	std::cout << asd1.getValue() << "\n";

	std::cout << asd2.getValue() << "\n";
	std::cout << asd2.getValue() << "\n";
}