#ifndef MINESWEEP_H_INCLUDED
#define MINESWEEP_H_INCLUDED

using namespace std;

struct cell
{
    char display;
    int adjMines;
    bool mine;
    bool covered;
    bool flag;
};

#endif // MINESWEEP_H_INCLUDED
