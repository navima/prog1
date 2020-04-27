#include "widgetMandel.h"


//A konstruktorunk
widgetMandel::widgetMandel(double realMin, double realMax, double imagMin, double imagMax,
                     int szelesseg, int iteraciosHatar, QWidget *parent)
                         : QMainWindow(parent)  /* default konstruktor az inherit�lt tagnak */
{
    setWindowTitle("Mandelbrot halmaz");    // Az ablak c�me

    assert(realMin < realMax);  //�n raktam bele hogy legyen legal�bb VALAMI valid�ci� szerus�g,
    assert(imagMin < imagMax);  //hogy ne lehessen baroms�gokkal megh�vni

    szamitasFut = true;     //Eleve sz�molva kezd�nk

    this->realMin = realMin;    //Evidens
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    this->szelesseg = szelesseg;
    this->iteraciosHatar = iteraciosHatar;
    magassag = (int)(szelesseg * ((imagMax-imagMin)/(realMax-realMin))); // sz�less�g * (Y/X ar�ny) = magass�g

    setFixedSize(QSize(szelesseg, magassag));   // be�ll�tjuk az elobbiekben kisz�molt m�reteket
    fraktal= new QImage(szelesseg, magassag, QImage::Format_RGB32); // megcsin�ljuk a k�pet/grafikai objektumot amin �br�zolunk majd

    computationThread = new FrakSzal(realMin, realMax,
                                     imagMin, imagMax,
                                     szelesseg, magassag, iteraciosHatar, this);    // csin�lunk egy threadet ami sz�molni fog nek�nk
    computationThread->start();     // elind�tjuk a threadet
}

widgetMandel::~widgetMandel()   //destruktorban kit�r�lj�k a threadet �s a k�pet is (m�st nem hoztunk l�tre new-al)
{
    delete fraktal;
    delete computationThread;
}

void widgetMandel::paintEvent(QPaintEvent*) {   //inherit�lt funkci�, akkor h�v�dik meg mikor �jrarajzol�dik az adott widget
    QPainter qpainter(this);
    qpainter.drawImage(0, 0, *fraktal); //A kisz�molt k�p�nket festj�k ki a widgetre
    if(!szamitasFut) {      //Akkor fog lefutni, amikor elozoleg megnyomtuk a bal/jobbklikket. Bovebben a mousePressEvent-ben
        qpainter.setPen(QPen(Qt::white, 1));
        qpainter.drawRect(x, y, mx, my);    //a kijel�l�s vizualiz�l�sa �rdek�ben egy feh�r t�glalapot rajzolunk a kijel�lt ter�let k�r�
    }
    qpainter.end();
}

void widgetMandel::mousePressEvent(QMouseEvent* event) {

    // A nagy�t�sra kijel�lt ter�let bal felso sarka az eg�r event gener�l�sakor aktu�lis helyzete
    x = event->x();
    y = event->y();

    // A ter�let inici�lis m�rete 0
    mx = 0;
    my = 0;

    //Invalid�lja a widget teljes ter�let�t ezzel "megh�vva" a paintEventet
    update();
}

void widgetMandel::mouseMoveEvent(QMouseEvent* event) {

    // Friss�ti a nagy�tand� ter�let m�ret�t
    mx = event->x() - this->x;
    my = mx; // n�gyzet alak�

    update();
}

void widgetMandel::mouseReleaseEvent(QMouseEvent* event) {

    if(szamitasFut) //Ha �ppen fut a sz�m�t�-thread�nk akkor ne muk�dj�n a nagy�t�s
        return;

    szamitasFut = true; //Egybol ezut�n majd sz�molni fogunk

    double dx = (realMax-realMin)/szelesseg;    //mekkora a komplex sz�ms�kon egy pixel
    double dy = (imagMax-imagMin)/magassag;

    double realMin = this->realMin+x*dx;
    double realMax = this->realMin+x*dx+mx*dx;
    double imagMin = this->imagMax-y*dy-my*dy;
    double imagMax = this->imagMax-y*dy;

    this->realMin = realMin;
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    delete computationThread;   //kit�r�lj�k a sz�m�t� thread�nket, mert �j hat�rok k�z�tt szeretn�nk sz�molni
    computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);    //elkezd�nk sz�molni az �j hat�rok k�z�tt
    computationThread->start();

    update();
}

void widgetMandel::keyPressEvent(QKeyEvent *event)
{

    if(szamitasFut)
        return;

    if (event->key() == Qt::Key_N)  //csak az N beture fusson le
    {
        iteraciosHatar *= 2;    //iter�ci�s hat�r megk�tszerez�se �s a k�p �jrasz�mol�sa
        szamitasFut = true;

        delete computationThread;
        computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);
        computationThread->start();
    }

}


void widgetMandel::vissza(int magassag, int *sor, int meret)    // a "callback" funkci� amit a thread�nk fog majd megh�vni
{
    for(int i=0; i<meret; ++i) {    //a kapott inform�ci�t sz�nn� alak�tjuk majd a k�p�nk adott sor�t (magassag) friss�tj�k az �j inform�ci�val
        QRgb szin = qRgb(0, 255-sor[i], 0);
        fraktal->setPixel(i, magassag, szin);
    }
    update();
}

void widgetMandel::vissza(void) // ha a sz�m�t� thread�nk ezt h�vja meg, akkor v�gzett a sz�m�t�ssal
{
    szamitasFut = false;
    x = y = mx = my = 0;
}
