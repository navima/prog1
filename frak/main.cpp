#include <QApplication>
#include "widgetMandel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widgetMandel w1(-2,+2,-2,+2,600,15);   /* csinálunk egy widgetMandel típusú widgetet */
    w1.show();      /* megjelenítjük azt a widgetet */

    /*
    FrakAblak w1,
    w2(-.08292191725019529, -.082921917244591272,
       -.9662079988595939, -.9662079988551173, 600, 3000),
    w3(-.08292191724880625, -.0829219172470933,
       -.9662079988581493, -.9662079988563615, 600, 4000),
    w4(.14388310361318304, .14388310362702217,
       .6523089200729396, .6523089200854384, 600, 38655);
    w1.show();
    w2.show();
    w3.show();
    w4.show();
*/
    return a.exec();
}
