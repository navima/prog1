#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generations(-1),
    universeSize(50)
{
    timer->setInterval(100);    //Az alap interval 100ms lesz
    m_masterColor = "#000";     //Az alap szín a fekete
    universe = new bool[(universeSize + 2) * (universeSize + 2)];   //Az univerzumunk/játékterünk, egy 2d tömb kilapítva
    next = new bool[(universeSize + 2) * (universeSize + 2)];       //A következő állapota a játéktérnek
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration())); //Itt a timer timeout eventjére akasztjuk a newGeneration eventet
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));  //False-ra (unpopuláltra) állítjuk a játékteret
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
}

GameWidget::~GameWidget()
{
    delete [] universe; //A Heapen allokált tömbök törlése
    delete [] next;
}

void GameWidget::startGame(const int &number)
{
    generations = number;
    timer->start();     //Itt indítjuk el a timert
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j] = false;
        }
    }
    gameEnds(true); //Clearelés után leállítjuk a játékot
    update();
}

int GameWidget::cellNumber()
{
    return universeSize;
}

void GameWidget::setCellNumber(const int &s)
{
    universeSize = s;
    resetUniverse();
    update();
}

void GameWidget::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
}

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

bool GameWidget::isAlive(int k, int j)  //Az életjáték szabájai
{
    int power = 0;
    power += universe[(k+1)*universeSize +  j];
    power += universe[(k-1)*universeSize + j];
    power += universe[k*universeSize + (j+1)];
    power += universe[k*universeSize + (j-1)];
    power += universe[(k+1)*universeSize + ( j-1)];
    power += universe[(k-1)*universeSize + (j+1)];
    power += universe[(k-1)*universeSize + (j-1)];
    power += universe[(k+1)*universeSize +  (j+1)];
    if (((universe[k*universeSize + j] == true) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void GameWidget::newGeneration()
{
    if(generations < 0)
        generations++;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            next[k*universeSize + j] = isAlive(k, j);   //Kiszámoljuk a következő állást
        }
    }

    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            universe[k*universeSize + j] = next[k*universeSize + j];
        }
    }
    update();
    generations--;
    if(generations == 0) {
        stopGame();
        gameEnds(true);
        QMessageBox::information(this,
                                 tr("Game finished."),
                                 tr("Iterations finished."),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel);
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    universe[k*universeSize + j] = !universe[k*universeSize + j];
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent *e)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    int currentLocation = k*universeSize + j;
    if(!universe[currentLocation]){                //if current cell is empty,fill in it
        universe [currentLocation]= !universe[currentLocation];
        update();
    }
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    QColor gridColor = m_masterColor; // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/universeSize; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/universeSize; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            if(universe[k*universeSize + j] == true) { // Él a cella?
                qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(m_masterColor)); // fill cell with brush of main color
            }
        }
    }
}

QColor GameWidget::masterColor()
{
    return m_masterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor = color;
    update();
}
