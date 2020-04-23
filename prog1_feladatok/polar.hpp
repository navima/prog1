#pragma once
#include <stdlib.h>
#include <iostream>

template <typename T>
class polar
{
private:
	T value;	/* Az ertekunk */
	T nextValue /* A kovetkezo ertekunk */
	bool havenext = false;	/* Az eltarolt valtozo */
	
public:
	T getValue()	/* A getter funkcio */
	{
		if (havenext)	/* Megnezzuk  hogy van-e mar szamolva kovetkezo ertek*/
		{
			havenext = false;	/* felhasznaltuk a kovetkezo erteket */
			return nextValue;	/* visszaterunk vele */
		}
		else
		{
			value = rand();		/* kiszamoljuk a mostani es a kovetkezo erteket */
			nextValue = rand();
			havenext = true;	/* van eltarolt kovetkezo ertekunk */
			return value;		/* visszaterunk az ertekkel */
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