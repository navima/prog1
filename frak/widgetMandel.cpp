#include "widgetMandel.h"


//A konstruktorunk
widgetMandel::widgetMandel(double realMin, double realMax, double imagMin, double imagMax,
                     int szelesseg, int iteraciosHatar, QWidget *parent)
                         : QMainWindow(parent)  /* default konstruktor az inherit�lt tagnak */
{
    setWindowTitle("Mandelbrot halmaz");    // Az ablak c�me

    assert(realMin < realMax);  //�n raktam bele hogy legyen legal�bb VALAMI valid�ci� szerus�g,
    assert(imagMin < imagMax);  //hogy ne lehessen baroms�gokkal megh�vni

    szamitasFut = true;     //Eleve kezdjen sz�molni
    x = y = mx = my = 0;

    this->realMin = realMin;    //Evidens
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    this->szelesseg = szelesseg;
    this->iteraciosHatar = iteraciosHatar;
    magassag = (int)(szelesseg * ((imagMax-imagMin)/(realMax-realMin))); // sz�less�g * (X/Y ar�ny) = magass�g

    setFixedSize(QSize(szelesseg, magassag));
    fraktal= new QImage(szelesseg, magassag, QImage::Format_RGB32);

    computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);
    computationThread->start();
}

widgetMandel::~widgetMandel()
{
    delete fraktal;
    delete computationThread;
}

void widgetMandel::paintEvent(QPaintEvent*) {
    QPainter qpainter(this);
    qpainter.drawImage(0, 0, *fraktal);
    if(!szamitasFut) {
        qpainter.setPen(QPen(Qt::white, 1));
        qpainter.drawRect(x, y, mx, my);

    }
    qpainter.end();
}

void widgetMandel::mousePressEvent(QMouseEvent* event) {

    // A nagy�tand� kijel�lt ter�letet bal fels� sarka:
    x = event->x();
    y = event->y();
    mx = 0;
    my = 0;

    update();
}

void widgetMandel::mouseMoveEvent(QMouseEvent* event) {

    // A nagy�tand� kijel�lt ter�let sz�less�ge �s magass�ga:
    mx = event->x() - x;
    my = mx; // n�gyzet alak�

    update();
}

void widgetMandel::mouseReleaseEvent(QMouseEvent* event) {

    if(szamitasFut)
        return;

    szamitasFut = true;

    double dx = (realMax-realMin)/szelesseg;
    double dy = (imagMax-imagMin)/magassag;

    double realMin = this->realMin+x*dx;
    double realMax = this->realMin+x*dx+mx*dx;
    double imagMin = this->imagMax-y*dy-my*dy;
    double imagMax = this->imagMax-y*dy;

    this->realMin = realMin;
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    delete computationThread;
    computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);
    computationThread->start();

    update();
}

void widgetMandel::keyPressEvent(QKeyEvent *event)
{

    if(szamitasFut)
        return;

    if (event->key() == Qt::Key_N)
        iteraciosHatar *= 2;
    szamitasFut = true;

    delete computationThread;
    computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);
    computationThread->start();

}


void widgetMandel::vissza(int magassag, int *sor, int meret)
{
    for(int i=0; i<meret; ++i) {
        QRgb szin = qRgb(0, 255-sor[i], 0);
        fraktal->setPixel(i, magassag, szin);
    }
    update();
}

void widgetMandel::vissza(void)
{
    szamitasFut = false;
    x = y = mx = my = 0;
}
