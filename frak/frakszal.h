#pragma once

#include <QThread>
#include <cmath>
#include <complex>
#include "widgetMandel.h"

class widgetMandel;

class FrakSzal : public QThread
{
    Q_OBJECT

public:
    FrakSzal(double realMin, double realMax, double imagMin, double imagMax,
             int szelesseg, int magassag, int iteraciosHatar, widgetMandel *frakAblak);
    ~FrakSzal();
    void run();

protected:
    double realMin, realMax, imagMin, imagMax;

    // A komplex sík vizsgált tartományára feszített
    // háló szélessége és magassága.
    int szelesseg, magassag;

    int iteraciosHatar;

    //parent
    widgetMandel* frakAblak;

    int* egySor;

};
