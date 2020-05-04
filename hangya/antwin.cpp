#include "antwin.hpp"
#include <QDebug>

AntWin::AntWin ( int width, int height, int delay, int numAnts,
                 int pheromone, int nbhPheromon, int evaporation, int cellDef,
                 int min, int max, int cellAntMax, QWidget *parent )
                        : QMainWindow ( parent ), width(width), height(height), max(max), min(min)
{
    setWindowTitle ( "Ant Simulation" );

    cellWidth = 6; //"pixel" mérete
    cellHeight = 6;

    setFixedSize ( QSize ( width*cellWidth, height*cellHeight ) );

    grids = new int**[2];
    grids[0] = new int*[height];
    for ( int i=0; i<height; ++i )
        grids[0][i] = new int [width];

    grids[1] = new int*[height];
    for ( int i=0; i<height; ++i )
        grids[1][i] = new int [width];

    //a grids-be csinálunk 2 gridet


    gridIdx = 0;
    grid = grids[gridIdx];

    for ( int i=0; i<height; ++i )
        for ( int j=0; j<width; ++j )
            grid[i][j] = cellDef;


    ants = new Ants();

    antThread = new AntThread ( ants, grids, width, height, delay, numAnts, pheromone,
                                nbhPheromon, evaporation, min, max, cellAntMax);

    connect ( antThread, SIGNAL ( step ( int) ),
              this, SLOT ( step ( int) ) );

    antThread->start();

}

void AntWin::paintEvent ( QPaintEvent* )
{
    QPainter qpainter ( this );

    qpainter.fillRect(0,0,width*cellWidth, height*cellHeight, Qt::white);

    //az éppen aktuális grid
    grid = grids[gridIdx];


    //a feromonok ábrázolása
    float pheromoneColorIncrement = 255.0/max;
    for ( int i=0; i<height; ++i )
        for ( int j=0; j<width; ++j )
            if(grid[i][j]>0)
            {
                qpainter.fillRect ( j*cellWidth, i*cellHeight, cellWidth, cellHeight,
                                    QColor ( 255 - grid[i][j]*pheromoneColorIncrement,
                                             255,
                                             255 - grid[i][j]*pheromoneColorIncrement) );
            }

    //a hangyák ábrázolása
    for ( auto elem: *ants) {
        qpainter.setPen ( QPen ( Qt::black, 1 ) );

        qpainter.drawRect ( elem.x*cellWidth+1, elem.y*cellHeight+1,
                            cellWidth-2, cellHeight-2 );

    }

    qpainter.end();
}

AntWin::~AntWin()
{
    delete antThread;

    for ( int i=0; i<height; ++i ) {
        delete[] grids[0][i];
        delete[] grids[1][i];
    }

    delete[] grids[0];
    delete[] grids[1];
    delete[] grids;

    delete ants;
}

void AntWin::step ( const int &gridIdx )
{

    this->gridIdx = gridIdx;
    update();
}
