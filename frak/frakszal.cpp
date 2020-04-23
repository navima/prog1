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
    double dx = (realMax-realMin)/szelesseg;    //valós számegyenes inkrementációi
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

            // ha a < 4 feltétel nem teljesült és a
            // iteráció < iterációsHatár sérülésével lépett ki, azaz
            // feltesszük a c-rõl, hogy itt a z_{n+1} = z_n * z_n + c
            // sorozat konvergens, azaz iteráció = iterációsHatár
            // ekkor az iteráció %= 256 egyenlõ 255, mert az esetleges
            // nagyítasok során az iteráció = valahány * 256 + 255

            iteracio %= 256;

            //a színezést viszont már majd a FrakAblak osztályban lesz
            egySor[k] = iteracio;
        }
        // Ábrázolásra átadjuk a kiszámolt sort a FrakAblak-nak.
        frakAblak->vissza(j, egySor, szelesseg);
    }
    frakAblak->vissza();

}
