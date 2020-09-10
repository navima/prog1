#pragma once

#include <string>
#include <iostream>

class Szulo
{
public:
	int a = 5;

	//elore meg kell adni hogy virtual lesz a f�ggv�ny -> alapb�l statikusan van k�tve
	virtual std::string nev()
	{
		return "Szulo";
	}	
};

class Gyerek : Szulo
{
	//nem kell megmondani hogy overridolunk, azt kital�lja a compiler
	//ha egy nem virtu�lis funkci�val megegyezo nevu met�dust csin�lunk, 
	//akkor shadowolni fogja (elrejti) az eredetit, �s azt csak akkor lehet el�rni, ha castolunk
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