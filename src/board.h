//Tabuleiro (onde ficam as células e os navios)

#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>


typedef enum{
    CELL_WATER,
    CELL_SHIP,
    CELL_HIT,
    CELL_MISS
}CellState;

typedef struct {
    CellState state;
    int ship_id; // -1 se não houver navio
} Cell;

typedef struct {
    int rows;
    int cols;
    Cell *cells; //para poder usar o malloc(row * col)
} Board;

// Cria um tabuleiro inicializado com ÁGUA
Board board_create(int rows, int cols);

// Libera a memória alocada para o tabuleiro
void board_destroy(Board *board);

// Retorna um ponteiro para a célula na posição (row, col) ou NULL se inválido
Cell* board_get_cell(Board *board, int row, int col);

void board_display(Board *board, int show_ships);

#endif //BOARD_H
