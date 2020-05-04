#include "antthread.hpp"
#include <QDebug>
#include <cmath>
#include <QDateTime>
AntThread::AntThread ( Ants* ants, int*** grids,
                     int width, int height,
                     int delay, int numAnts,
                     int pheromone, int nbrPheromone,
                     int evaporation,
                     int min, int max, int cellAntMax)
                        : ants(ants), grids(grids), width(width), height(height), delay(delay),
                          pheromoneIncrementCenter(pheromone),  evaporation(evaporation), min(min), premonomeMax(max),
                          cellAntMax(cellAntMax), pheromoneIncrementNeighbouring(nbrPheromone)
{

    gridAnts = new int*[height];
    for ( int i=0; i<height; ++i )
        gridAnts[i] = new int [width];

    for ( int i=0; i<height; ++i )
        for ( int j=0; j<width; ++j )
            gridAnts[i][j] = 0;

    qsrand ( QDateTime::currentMSecsSinceEpoch() );

    Ant h {0, 0};
    for ( int i {0}; i<numAnts; ++i ) {

        h.y = height/2 + qrand() % 40-20;
        h.x = width/2 + qrand() % 40-20;

        ++gridAnts[h.y][h.x];

        ants->push_back ( h );

    }

    gridIdx = 0;
}

//összead minden cellaértéket az adott "irányban"
double AntThread::sumNbhs ( int **grid, int row, int col, int dir )
{
    double sum = 0.0;

    int ifrom, ito;
    int jfrom, jto;

    parseDiercion ( dir, ifrom, ito, jfrom, jto );

    for ( int i=ifrom; i<ito; ++i )
        for ( int j=jfrom; j<jto; ++j )
            if ( ! ( ( i==0 ) && ( j==0 ) ) ) {

                //handle wrap-around
                int o = col + j;
                if ( o < 0 )
                    o = width-1;
                else if ( o >= width )
                    o = 0;


                int s = row + i;
                if ( s < 0 )
                    s = height-1;
                else if ( s >= height )
                    s = 0;


                sum += (grid[s][o]+1)*(grid[s][o]+1)*(grid[s][o]+1);

            }

    return sum;
}

int AntThread::makeDirection ( int sor, int oszlop, int vsor, int voszlop )
{

    if ( vsor == 0 && sor == height -1 ) {
        if ( voszlop < oszlop ) {
            return 5;
        } else if ( voszlop > oszlop ) {
            return 3;
        } else {
            return 4;
        }
    } else if ( vsor == height - 1 && sor == 0 ) {
        if ( voszlop < oszlop ) {
            return 7;
        } else if ( voszlop > oszlop ) {
            return 1;
        } else {
            return 0;
        }
    } else if ( voszlop == 0 && oszlop == width - 1 ) {
        if ( vsor < sor ) {
            return 1;
        } else if ( vsor > sor ) {
            return 3;
        } else {
            return 2;
        }
    } else if ( voszlop == width && oszlop == 0 ) {
        if ( vsor < sor ) {
            return 7;
        } else if ( vsor > sor ) {
            return 5;
        } else {
            return 6;
        }
    } else if ( vsor < sor && voszlop < oszlop ) {
        return 7;
    } else if ( vsor < sor && voszlop == oszlop ) {
        return 0;
    } else if ( vsor < sor && voszlop > oszlop ) {
        return 1;
    }

    else if ( vsor > sor && voszlop < oszlop ) {
        return 5;
    } else if ( vsor > sor && voszlop == oszlop ) {
        return 4;
    } else if ( vsor > sor && voszlop > oszlop ) {
        return 3;
    }

    else if ( vsor == sor && voszlop < oszlop ) {
        return 6;
    } else if ( vsor == sor && voszlop > oszlop ) {
        return 2;
    }

    else { //(vsor == sor && voszlop == oszlop)
        qDebug() << "ZAVAR AZ EROBEN az iranynal";

        return -1;
    }

}

void AntThread::parseDiercion ( int dir, int& ifrom, int& ito, int& jfrom, int& jto )
{
    switch ( dir ) {
    case 0:
        ifrom = -1;
        ito = 0;
        jfrom = -1;
        jto = 2;
        break;
    case 1:
        ifrom = -1;
        ito = 1;
        jfrom = 0;
        jto = 2;
        break;
    case 2:
        ifrom = -1;
        ito = 2;
        jfrom = 1;
        jto = 2;
        break;
    case 3:
        ifrom =0;
        ito = 2;
        jfrom = 0;
        jto = 2;
        break;
    case 4:
        ifrom = 1;
        ito = 2;
        jfrom = -1;
        jto = 2;
        break;
    case 5:
        ifrom = 0;
        ito = 2;
        jfrom = -1;
        jto = 1;
        break;
    case 6:
        ifrom = -1;
        ito = 2;
        jfrom = -1;
        jto = 0;
        break;
    case 7:
        ifrom = -1;
        ito = 1;
        jfrom = -1;
        jto = 1;
        break;

    }

}

int AntThread::calculateAntDirection ( int **racs,
                           int sor, int oszlop,
                           int& vsor, int& voszlop, int dir )
{
    int y = sor;
    int x = oszlop;

    int ifrom, ito;
    int jfrom, jto;

    parseDiercion ( dir, ifrom, ito, jfrom, jto );

    double osszes = sumNbhs ( racs, sor, oszlop, dir );
    double random = ( float ) ( qrand() % 1000000 ) / ( float ) 1000000.0;
    double gvalseg = 0.0;


    for ( int i=ifrom; i<ito; ++i )
        for ( int j=jfrom; j<jto; ++j )
            if ( ! ( ( i==0 ) && ( j==0 ) ) )
            {
                //edge wrap-around
                int o = oszlop + j;
                if ( o < 0 )
                    o = width-1;
                else if ( o >= width )
                    o = 0;

                int s = sor + i;
                if ( s < 0 )
                    s = height-1;
                else if ( s >= height )
                    s = 0;

                //double kedvezo = std::sqrt((double)(racs[s][o]+2));//(racs[s][o]+2)*(racs[s][o]+2);
                //double kedvezo = (racs[s][o]+b)*(racs[s][o]+b);
                //double kedvezo = ( racs[s][o]+1 );
                double kedvezo = (racs[s][o]+1)*(racs[s][o]+1)*(racs[s][o]+1);

                double valseg = kedvezo/osszes;
                gvalseg += valseg;

                if ( gvalseg >= random ) {

                    vsor = s;
                    voszlop = o;

                    return makeDirection ( sor, oszlop, vsor, voszlop );

                }

            }

    qDebug() << "ZAVAR AZ EROBEN a lepesnel";
    vsor = y;
    voszlop = x;

    return dir;
}

void AntThread::timeStep()
{
    int **gridOld = grids[gridIdx];
    int **gridNew = grids[ ( gridIdx+1 ) %2];


    //calculate pheromone evaporation for each cell in gridNew
    for ( int i=0; i<height; ++i )
    {

        for ( int j=0; j<width; ++j )
        {
            gridNew[i][j] = gridOld[i][j];

            if ( gridNew[i][j] - evaporation >= 0 ) {
                gridNew[i][j] -= evaporation;
            } else {
                gridNew[i][j] = 0;
            }

        }}

    for ( Ant& elem: *ants )
    {
        int ujSor;
        int ujOszlop;
        int ujirany = calculateAntDirection( gridOld, elem.y, elem.x, ujSor, ujOszlop, elem.dir );

        addPheromone ( gridNew, elem.y, elem.x );

        //csak ha a célcellában még van hely
        if ( gridAnts[ujSor][ujOszlop] < cellAntMax ) {

            //hangya mozgatása
            --gridAnts[elem.y][elem.x];
            ++gridAnts[ujSor][ujOszlop];

            elem.x = ujOszlop;
            elem.y = ujSor;
            elem.dir = ujirany;

        }
    }

    gridIdx = ( gridIdx+1 ) %2;
}

void AntThread::addPheromone ( int **racs, int sor, int oszlop )
{

    for ( int i=-1; i<2; ++i )
        for ( int j=-1; j<2; ++j )
            if ( ! ( ( i==0 ) && ( j==0 ) ) )
            {
                int o = oszlop + j;
                {
                    if ( o < 0 ) {
                        o = width-1;
                    } else if ( o >= width ) {
                        o = 0;
                    }
                }
                int s = sor + i;
                {
                    if ( s < 0 ) {
                        s = height-1;
                    } else if ( s >= height ) {
                        s = 0;
                    }
                }

                if ( racs[s][o] + pheromoneIncrementNeighbouring <= premonomeMax ) {
                    racs[s][o] += pheromoneIncrementNeighbouring;
                } else {
                    racs[s][o] = premonomeMax;
                }


            }

    if ( racs[sor][oszlop] + pheromoneIncrementCenter <= premonomeMax ) {
        racs[sor][oszlop] += pheromoneIncrementCenter;
    } else {
        racs[sor][oszlop]  = premonomeMax;
    }

}

void AntThread::run()
{
    running = true;
    while ( running ) {

        QThread::msleep ( delay );

        if ( !paused )
            timeStep();

        emit step ( gridIdx );

    }

}

AntThread::~AntThread()
{
    for ( int i=0; i<height; ++i ) {
        delete [] gridAnts[i];
    }

    delete [] gridAnts;
}

