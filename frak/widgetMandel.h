#pragma once

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "frakszal.h"

class FrakSzal;

class widgetMandel : public QMainWindow
{
    Q_OBJECT

public:
    widgetMandel(double realMin = -2.0, double realMax = .7, double imagMin = -1.35,
              double imagMax = 1.35, int szelesseg = 600,
              int iteraciosHatar = 255, QWidget *parent = 0);
    ~widgetMandel();

    void vissza(int magassag , int * sor, int meret) ;
    void vissza(void) ;

    double realMin, realMax, imagMin, imagMax;

    // A komplex sík vizsgált tartományára feszített
    // háló szélessége és magassága.
    int szelesseg, magassag;

    int iteraciosHatar;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);

private:
    QImage* fraktal;
    FrakSzal* computationThread;
    bool szamitasFut;
    // A nagyítandó kijelölt területet bal felsõ sarka.
    int x = 0;
    int y = 0;
    // A nagyítandó kijelölt terület szélessége és magassága.
    int mx = 0;
    int my = 0;
};
