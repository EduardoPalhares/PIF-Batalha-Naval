// cell_state.h
#ifndef CELL_STATE_H
#define CELL_STATE_H

// Enum que representa o estado de uma célula no tabuleiro
enum CellState {
    CELL_EMPTY,      // célula vazia, sem navio
    CELL_SHIP,       // célula ocupada por parte de um navio
    CELL_HIT,        // célula que foi atingida por um tiro
    CELL_MISS,       // célula onde o tiro errou
    CELL_DESTROYED   // célula com parte de um navio destruído
};

#endif
