#include "widgetMandel.h"


//A konstruktorunk
widgetMandel::widgetMandel(double realMin, double realMax, double imagMin, double imagMax,
                     int szelesseg, int iteraciosHatar, QWidget *parent)
                         : QMainWindow(parent)  /* default konstruktor az inheritált tagnak */
{
    setWindowTitle("Mandelbrot halmaz");    // Az ablak címe

    assert(realMin < realMax);  //én raktam bele hogy legyen legalább VALAMI validáció szeruség,
    assert(imagMin < imagMax);  //hogy ne lehessen baromságokkal meghívni

    szamitasFut = true;     //Eleve kezdjen számolni
    x = y = mx = my = 0;

    this->realMin = realMin;    //Evidens
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    this->szelesseg = szelesseg;
    this->iteraciosHatar = iteraciosHatar;
    magassag = (int)(szelesseg * ((imagMax-imagMin)/(realMax-realMin))); // szélesség * (X/Y arány) = magasság

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

    // A nagyítandó kijelölt területet bal felsõ sarka:
    x = event->x();
    y = event->y();
    mx = 0;
    my = 0;

    update();
}

void widgetMandel::mouseMoveEvent(QMouseEvent* event) {

    // A nagyítandó kijelölt terület szélessége és magassága:
    mx = event->x() - x;
    my = mx; // négyzet alakú

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
