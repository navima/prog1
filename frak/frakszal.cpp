#include "frakszal.h"

FrakSzal::FrakSzal(double realMin, double realMax, double imagMin, double imagMax,
                   int szelesseg, int magassag, int iteraciosHatar, widgetMandel *frakAblak)
{
    this->realMin = realMin;
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;
    this->szelesseg = szelesseg;
    this->iteraciosHatar = iteraciosHatar;
    this->frakAblak = frakAblak;
    this->magassag = magassag;

    egySor = new int[szelesseg];
}

FrakSzal::~FrakSzal()
{
    delete[] egySor;
}

void FrakSzal::run()
{
    double dx = (realMax-realMin)/szelesseg;    //val�s sz�megyenes inkrement�ci�i
    double dy = (imagMax-imagMin)/magassag;     //komplex -||-

    int iteracio = 0;

    for(int j=0; j<magassag; j++)
    {
        for(int k=0; k<szelesseg; k++)
        {
            std::complex<double> c(realMin+k*dx, imagMax-j*dy);

            std::complex<double> z(0, 0);
            iteracio = 0;

        while( std::abs(z) < 4 && iteracio < iteraciosHatar) {
          z = z  * z + c;

          iteracio++;
        }

            // ha a < 4 felt�tel nem teljes�lt �s a
            // iter�ci� < iter�ci�sHat�r s�r�l�s�vel l�pett ki, azaz
            // feltessz�k a c-r�l, hogy itt a z_{n+1} = z_n * z_n + c
            // sorozat konvergens, azaz iter�ci� = iter�ci�sHat�r
            // ekkor az iter�ci� %= 256 egyenl� 255, mert az esetleges
            // nagy�tasok sor�n az iter�ci� = valah�ny * 256 + 255

            iteracio %= 256;

            //a sz�nez�st viszont m�r majd a FrakAblak oszt�lyban lesz
            egySor[k] = iteracio;
        }
        // �br�zol�sra �tadjuk a kisz�molt sort a FrakAblak-nak.
        frakAblak->vissza(j, egySor, szelesseg);
    }
    frakAblak->vissza();

}
