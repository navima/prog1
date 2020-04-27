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

    egySor = new int[szelesseg];       // itt foglaljuk le a kiszámolt értékeknek a helyet. nem kell kitakarítani, mert úgyis felülírjuk az összes értéket
}

FrakSzal::~FrakSzal()
{
    delete[] egySor;
}

void FrakSzal::run()
{
    double dx = (realMax-realMin)/szelesseg;    //valós számegyenes inkrementációi
    double dy = (imagMax-imagMin)/magassag;     //komplex -||-

    int iteracio = 0;

    for(int j=0; j<magassag; j++)
    {
        for(int k=0; k<szelesseg; k++)
        {
            std::complex<double> c(realMin+k*dx, imagMax-j*dy); //az éppen aktuális komplex szám

            std::complex<double> z(0, 0);
            iteracio = 0;

        while( std::abs(z) < 4 && iteracio < iteraciosHatar) {  //a tényleges mandel számítás
          z = z  * z + c;

          iteracio++;
        }

            iteracio %= 256;    //hogy nagyobb maxiterációnál is nézzen ki valahogy a képünk, 256ossával újrakezdi a fekete-zöld gradienst

            egySor[k] = iteracio;   //eltároljuk a kiszámított értéket
        }
        // Ábrázolásra átadjuk a kiszámolt sort a frakAblak-nak.
        frakAblak->vissza(j, egySor, szelesseg);
    }
    frakAblak->vissza();    //Ezzel jelezzük hogy kész vagyunk
}
