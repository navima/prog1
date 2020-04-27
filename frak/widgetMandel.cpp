#include "widgetMandel.h"


//A konstruktorunk
widgetMandel::widgetMandel(double realMin, double realMax, double imagMin, double imagMax,
                     int szelesseg, int iteraciosHatar, QWidget *parent)
                         : QMainWindow(parent)  /* default konstruktor az inheritált tagnak */
{
    setWindowTitle("Mandelbrot halmaz");    // Az ablak címe

    assert(realMin < realMax);  //én raktam bele hogy legyen legalább VALAMI validáció szeruség,
    assert(imagMin < imagMax);  //hogy ne lehessen baromságokkal meghívni

    szamitasFut = true;     //Eleve számolva kezdünk

    this->realMin = realMin;    //Evidens
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    this->szelesseg = szelesseg;
    this->iteraciosHatar = iteraciosHatar;
    magassag = (int)(szelesseg * ((imagMax-imagMin)/(realMax-realMin))); // szélesség * (Y/X arány) = magasság

    setFixedSize(QSize(szelesseg, magassag));   // beállítjuk az elobbiekben kiszámolt méreteket
    fraktal= new QImage(szelesseg, magassag, QImage::Format_RGB32); // megcsináljuk a képet/grafikai objektumot amin ábrázolunk majd

    computationThread = new FrakSzal(realMin, realMax,
                                     imagMin, imagMax,
                                     szelesseg, magassag, iteraciosHatar, this);    // csinálunk egy threadet ami számolni fog nekünk
    computationThread->start();     // elindítjuk a threadet
}

widgetMandel::~widgetMandel()   //destruktorban kitöröljük a threadet és a képet is (mást nem hoztunk létre new-al)
{
    delete fraktal;
    delete computationThread;
}

void widgetMandel::paintEvent(QPaintEvent*) {   //inheritált funkció, akkor hívódik meg mikor újrarajzolódik az adott widget
    QPainter qpainter(this);
    qpainter.drawImage(0, 0, *fraktal); //A kiszámolt képünket festjük ki a widgetre
    if(!szamitasFut) {      //Akkor fog lefutni, amikor elozoleg megnyomtuk a bal/jobbklikket. Bovebben a mousePressEvent-ben
        qpainter.setPen(QPen(Qt::white, 1));
        qpainter.drawRect(x, y, mx, my);    //a kijelölés vizualizálása érdekében egy fehér téglalapot rajzolunk a kijelölt terület köré
    }
    qpainter.end();
}

void widgetMandel::mousePressEvent(QMouseEvent* event) {

    // A nagyításra kijelölt terület bal felso sarka az egér event generálásakor aktuális helyzete
    x = event->x();
    y = event->y();

    // A terület iniciális mérete 0
    mx = 0;
    my = 0;

    //Invalidálja a widget teljes területét ezzel "meghívva" a paintEventet
    update();
}

void widgetMandel::mouseMoveEvent(QMouseEvent* event) {

    // Frissíti a nagyítandó terület méretét
    mx = event->x() - this->x;
    my = mx; // négyzet alakú

    update();
}

void widgetMandel::mouseReleaseEvent(QMouseEvent* event) {

    if(szamitasFut) //Ha éppen fut a számító-threadünk akkor ne muködjön a nagyítás
        return;

    szamitasFut = true; //Egybol ezután majd számolni fogunk

    double dx = (realMax-realMin)/szelesseg;    //mekkora a komplex számsíkon egy pixel
    double dy = (imagMax-imagMin)/magassag;

    double realMin = this->realMin+x*dx;
    double realMax = this->realMin+x*dx+mx*dx;
    double imagMin = this->imagMax-y*dy-my*dy;
    double imagMax = this->imagMax-y*dy;

    this->realMin = realMin;
    this->realMax = realMax;
    this->imagMin = imagMin;
    this->imagMax = imagMax;

    delete computationThread;   //kitöröljük a számító threadünket, mert új határok között szeretnénk számolni
    computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);    //elkezdünk számolni az új határok között
    computationThread->start();

    update();
}

void widgetMandel::keyPressEvent(QKeyEvent *event)
{

    if(szamitasFut)
        return;

    if (event->key() == Qt::Key_N)  //csak az N beture fusson le
    {
        iteraciosHatar *= 2;    //iterációs határ megkétszerezése és a kép újraszámolása
        szamitasFut = true;

        delete computationThread;
        computationThread = new FrakSzal(realMin, realMax, imagMin, imagMax, szelesseg, magassag, iteraciosHatar, this);
        computationThread->start();
    }

}


void widgetMandel::vissza(int magassag, int *sor, int meret)    // a "callback" funkció amit a threadünk fog majd meghívni
{
    for(int i=0; i<meret; ++i) {    //a kapott információt színné alakítjuk majd a képünk adott sorát (magassag) frissítjük az új információval
        QRgb szin = qRgb(0, 255-sor[i], 0);
        fraktal->setPixel(i, magassag, szin);
    }
    update();
}

void widgetMandel::vissza(void) // ha a számító threadünk ezt hívja meg, akkor végzett a számítással
{
    szamitasFut = false;
    x = y = mx = my = 0;
}
