//Tabuleiro (onde ficam as células e os navios)

#include <stdio.h>
#include<stdlib.h>
#include "board.h"

//Alocar memória para criação de tabuleiro
Board board_create(int rows, int cols){
    Board new_board;                                   //Declaração da variável local que armazenará o novo tabuleiro.

    // Armazena as dimensões do tabuleiro na struct.
    new_board.rows=rows;
    new_board.cols=cols;

    new_board.cells=(Cell *) malloc(rows *cols * sizeof (Cell));               //Aloca a memória para o total de quadradinhos

    if (new_board.cells==NULL){
        printf("Erro ao alocar a memória para o tabuleiro.\n");
        exit (1);
    }

    for (int i=0;i< rows * cols;i++){                 // Percorre todas as células alocadas (do índice 0 até o total de células - 1).
        new_board.cells[i].state=CELL_WATER;          // Inicializa o estado da célula como água (~).
        new_board.cells[i].ship_id=-1;                // -1 indica que não há navio
    }

    return new_board;
}
//Função para liberar memória após uso
void board_destroy(Board *board){
    if (board -> cells !=NULL){
        free(board->cells);
        board->cells=NULL;                             //anulação do ponteiro após liberar
    }
}

// Retorna um ponteiro para a célula na posição (row, col) ou NULL se inválido
Cell* board_get_cell(Board *board, int row, int col){
    if (row < 0 || row >= board->rows || col<0 || col>= board->cols){        // Garante que 'row' e 'col' estão dentro das dimensões válidas do tabuleiro.
        return NULL; //Coordenada Inválida
    }
    
    int index= (row* board->cols) + col;            //calculo de indice

    return &board->cells[index];                   //retorna o endereço daquela celula específica
}


static char get_cell_symbol(CellState state, int show_ships) {
    switch (state) {
        case CELL_WATER: return '~';
        case CELL_HIT:   return 'X';
        case CELL_MISS:  return '.';
        case CELL_SHIP:  return (show_ships) ? 'S' : '~';
        default:         return '?';
    }
}

// Exibe o estado atual do tabuleiro no terminal
// show_ships: 1 para mostrar os navios (jogador vendo seu próprio mapa)
// show_ships: 0 para esconder os navios (jogador vendo o mapa do inimigo)
void board_display(Board *board, int show_ships) {
    // Cabeçalho
    printf("   "); 
    for (int j = 0; j < board->cols; j++) printf("%c ", 'A' + j);
    printf("\n");

    //Tabuleiro
    for (int i = 0; i < board->rows; i++) {
        printf("%2d ", i + 1); // Número da linha

        for (int j = 0; j < board->cols; j++) {
            Cell *c = board_get_cell(board, i, j);
            //Aqui sai simbolo na tela
            printf("%c ", get_cell_symbol(c->state, show_ships));
        }
        printf("\n");
    }
}




