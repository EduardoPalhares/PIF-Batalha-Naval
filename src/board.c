//Tabuleiro (onde ficam as células e os navios)

#include <stdio.h>
#include<stdlib.h>
#include "board.h"

//Alocar memória para criação de tabuleiro
Board board_create(int rows, int cols){
    Board new_board;

    new_board.rows=rows;
    new_board.cols=cols;

    //Aloca a memória para o total de quadradinhos
    new_board.cells=(Cell *) malloc(rows *cols * sizeof (Cell)); 

    if (new_board.cells==NULL){
        printf("Erro ao alocar a memória para o tabuleiro.\n");
        exit (1);
    }

    for (int i=0;i< rows * cols;i++){
        new_board.cells[i].state=CELL_WATER;
        new_board.cells[i].ship_id=-1; // -1 indica que não há navio
    }

    return new_board;
}
//Função para liberar memória após uso
void board_destroy(Board *board){
    if (board -> cells !=NULL){
        free(board->cells);
        board->cells=NULL; //anulação do ponteiro após liberar
    }
}

// Retorna um ponteiro para a célula na posição (row, col) ou NULL se inválido
Cell* board_get_cell(Board *board, int row, int col){
    //Verificação de limites
    if (row < 0 || row >= board->rows || col<0 || col>= board->cols){
        return NULL; //Coordenada Inválida
    }
    
    //calculo de indice
    int index= (row* board->cols) + col;

    //retorna o endereço daquela celula específica
    return &board->cells[index];
}


// Exibe o tabuleiro no terminal
// show_ships: 1 para mostrar os navios (jogador vendo seu próprio mapa)
// show_ships: 0 para esconder os navios (jogador vendo o mapa do inimigo)
void board_display(Board *board,int show_ships){
    printf("  ");

    for (int j=0;j< board->cols;j++){
        printf("%c ", 'A'+j);
    }
    printf("\n");

    for (int i=0;i<board->rows;i++){
        //impressão dos números das linhas
        printf("%2d",i+1);

        for (int j=0; j<board->cols;j++){
            Cell *cell=board_get_cell(board,i,j);

            char simbolo='?';

            switch (cell->state){
                case CELL_WATER:
                simbolo='~';
                break;

                case CELL_SHIP:
                // Se show_ships for 1 (verdadeiro), mostra 'S'. Senão, esconde como água '~'.
                simbolo=(show_ships) ? 'S' : '~';
                break;

                case CELL_HIT:
                    simbolo = 'X'; // Navio atingido
                    break;

                case CELL_MISS:
                    simbolo = '.'; // Tiro na água
                    break;
            }
             printf("%c ", simbolo);
        }
            printf("\n");//pula para próxima linha
    }
}




