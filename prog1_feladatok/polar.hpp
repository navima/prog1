#pragma once
#include <stdlib.h>
#include <iostream>

template <typename T>
class polar
{
private:
	T value;	/* Az ertekunk */
	bool valid = false;	/* Az eltarolt valtozo */
	void calcValue()	/* A fuggveny amivel kiszamoljuk az erteket */
	{
		value = (T)rand();
	}
public:
	T getValue()	/* A getter funkcio */
	{
		if (valid)	/* Megnezzuk  hogy van-e mar szamolva ertek*/
		{
			return value;	/* ha igen, visszaterunk vele */
		}
		else
		{
			calcValue();	/* ha nem, kiszamoljuk es utana terunk vissza vele */ 
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