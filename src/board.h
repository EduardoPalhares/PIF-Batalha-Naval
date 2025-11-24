//Tabuleiro (onde ficam as células e os navios)

#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include "cell_state.h"
#include "orientation.h"

typedef struct {
    CellState state;
    Orientation orientation;
    int row;
    int col;
} Cell;

typedef struct {
    int rows;
    int cols;
    Cell cells[10][10];
} Board;

#endif
