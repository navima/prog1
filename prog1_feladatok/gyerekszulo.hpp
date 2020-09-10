#pragma once

#include <string>
#include <iostream>

class Szulo
{
public:
	int a = 5;

	//elore meg kell adni hogy virtual lesz a függvény -> alapból statikusan van kötve
	virtual std::string nev()
	{
		return "Szulo";
	}	
};

class Gyerek : Szulo
{
	//nem kell megmondani hogy overridolunk, azt kitalálja a compiler
	//ha egy nem virtuális funkcióval megegyezo nevu metódust csinálunk, 
	//akkor shadowolni fogja (elrejti) az eredetit, és azt csak akkor lehet elérni, ha castolunk
	std::string nev()
	{
		return "Gyerek";
	} 
};

static void test()
{
	Szulo* szulo = new Szulo();
	Szulo* gyerek = (Szulo*) new Gyerek();	//explicit castolni kell, nem dinamikus

	Szulo& gyerek2 = *((Szulo*) new Gyerek());	//itt is

	std::cout << szulo->nev() << gyerek->nev() << gyerek2.nev();
}