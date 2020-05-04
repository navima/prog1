#pragma once

#include <QThread>
#include "ant.hpp"

class AntThread: public QThread
{
    Q_OBJECT

public:
    AntThread(Ants * ants, int ** * grids, int width, int height,
            int delay, int numAnts, int pheromoneIncrementCenter, int pheromoneIncrementNeighbouring,
            int evaporation, int min, int premonomeMax, int cellAntMax);

    ~AntThread();

    void run();
    void finish() { running = false; }
    void pause() { paused = !paused; }
    bool isRunning() { return running; }

private:
    bool running = true;
    bool paused = false;
    Ants * ants;
    int ** gridAnts;
    int min, premonomeMax;
    int cellAntMax;
    int pheromoneIncrementCenter;
    int evaporation;
    int pheromoneIncrementNeighbouring;
    int ** * grids;
    const int width;
    const int height;
    int gridIdx;
    int delay;

    void timeStep();

    int makeDirection(int sor, int oszlop, int vsor, int voszlop);
    void parseDiercion(int irany, int & ifrom, int & ito, int & jfrom, int & jto);
    int calculateAntDirection(int ** grid, int row, int col, int & retrow, int & retcol, int);
    double sumNbhs(int ** grid, int row, int col, int);
    void addPheromone(int ** grid, int row, int col);

    signals:
        void step(const int & );

};
