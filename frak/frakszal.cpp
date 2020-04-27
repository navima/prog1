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

    egySor = new int[szelesseg];       // itt foglaljuk le a kisz�molt �rt�keknek a helyet. nem kell kitakar�tani, mert �gyis fel�l�rjuk az �sszes �rt�ket
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
            std::complex<double> c(realMin+k*dx, imagMax-j*dy); //az �ppen aktu�lis komplex sz�m

            std::complex<double> z(0, 0);
            iteracio = 0;

        while( std::abs(z) < 4 && iteracio < iteraciosHatar) {  //a t�nyleges mandel sz�m�t�s
          z = z  * z + c;

          iteracio++;
        }

            iteracio %= 256;    //hogy nagyobb maxiter�ci�n�l is n�zzen ki valahogy a k�p�nk, 256oss�val �jrakezdi a fekete-z�ld gradienst

            egySor[k] = iteracio;   //elt�roljuk a kisz�m�tott �rt�ket
        }
        // �br�zol�sra �tadjuk a kisz�molt sort a frakAblak-nak.
        frakAblak->vissza(j, egySor, szelesseg);
    }
    frakAblak->vissza();    //Ezzel jelezz�k hogy k�sz vagyunk
}
