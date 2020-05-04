#pragma once

#include <vector>
#include <QtGlobal>

class Ant
{

public:
    int x;
    int y;
    int dir;

    Ant(int x, int y) : x(x), y(y), dir(qrand() % 8)
    {
    }

};

typedef std::vector<Ant> Ants;
