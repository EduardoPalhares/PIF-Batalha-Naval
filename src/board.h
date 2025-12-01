//Tabuleiro (onde ficam as células e os navios)

#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

typedef enum{
    CELL_WATER,                       //  Célula vazia (Água)
    CELL_SHIP,                        //  Célula ocupada por um navio (não atingido)
    CELL_HIT,                         // Célula que tinha navio e foi atingida (Acerto)
    CELL_MISS                         // Célula que era água e foi atingida (Água)
}CellState;

// Representa uma única posição do tabuleiro (o menor elemento estrutural).
typedef struct {
    CellState state;               // Estado atual da célula (água, navio, acerto, erro)
    int ship_id;                   // -1 se não houver navio
} Cell;

//Representa o tabuleiro completo.
typedef struct {
    int rows;                      // Número de linhas (tamanho)
    int cols;                      // Número de colunas (tamanho)
    Cell *cells;                   //para poder usar o malloc(row * col)
} Board;

// Cria um tabuleiro inicializado com ÁGUA
Board board_create(int rows, int cols);

// Libera a memória alocada para o tabuleiro
void board_destroy(Board *board);

// Retorna um ponteiro para a célula na posição (row, col) ou NULL se inválido
Cell* board_get_cell(Board *board, int row, int col);

//Exibe o estado atualizado do tabuleiro no terminal
void board_display(Board *board, int show_ships);

#endif //BOARD_H

