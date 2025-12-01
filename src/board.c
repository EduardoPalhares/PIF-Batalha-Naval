//Estrutura do tabuleiro

#include <stdio.h>
#include<stdlib.h>
#include "board.h"

//Alocar memória para criação do board
Board board_create(int rows, int cols){
    Board board;    

    // Linhas e colunas do board
    board.rows=rows;
    board.cols=cols;

    board.cells=(Cell *) malloc(rows *cols * sizeof (Cell));  //Aloca as células do board

    if (board.cells==NULL){
        printf("Erro ao alocar a memória para o tabuleiro.\n");
        exit (1);
    }
    //Inicia como água e com -1(não há navio)
    for (int i=0;i< rows * cols;i++){                 
        board.cells[i].state=CELL_WATER;          
        board.cells[i].ship_id=-1;                
    }

    return board;
}
//Liberar memória alocada para o tabuleiro
void board_destroy(Board *board){
    if (board -> cells !=NULL){
        free(board->cells);
        board->cells=NULL;        
    }
}

// Retorna um ponteiro para a célula na posição ou NULL se inválido
Cell* board_get_cell(Board *board, int row, int col){
    //Valida limites
    if (row < 0 || row >= board->rows || col<0 || col>= board->cols){  
        return NULL;      
    }
    
    int index= (row* board->cols) + col; //Cálculo de indice

    return &board->cells[index];  //Retorna da celula específica
}

//Símbolos dos ships
char get_ship_symbol(int id) {
    switch(id) {
        case 0: return 'P'; // Porta-avioes
        case 1: return 'E'; // Encouracado
        case 2: return 'C'; // Cruzador
        case 3: return 'C'; // Cruzador
        default: return 'D'; // Destroyer
    }
}

//Símbolo da célula
char get_symbol(Cell *c, int show_ships) {
    if (c->state == CELL_WATER) return '~';
    if (c->state == CELL_MISS) return '.';
    
    
    if (c->state == CELL_HIT) {
        return get_ship_symbol(c->ship_id);
    }
    
    if (c->state == CELL_SHIP) {
        if (show_ships == 1) return get_ship_symbol(c->ship_id);
        else return '~'; 
    }
    
    return '?'; // Erro
}

// Exibe o estado atual do board no terminal
void board_display(Board *board, int show_ships) {
    // Colunas
    printf("   "); 
    for (int j = 0; j < board->cols; j++) printf("%c ", 'A' + j);
    printf("\n");
    
    printf("   "); 
    for (int j = 0; j < board->cols; j++) {
        printf("--"); 
    }
    printf("\n");
    // Linhas 
    for (int i = 0; i < board->rows; i++) {
        printf("%2d|", i + 1); 
        for (int j = 0; j < board->cols; j++) {
            Cell *c = board_get_cell(board, i, j);
            //Mostra a letra de acordo com o acerto
            printf("%c ", get_symbol(c, show_ships));
        }
        printf("\n");
    }
    printf("   Legenda: [~] Agua  [.] Errou o tiro\n");
    printf("            [P] Porta-avioes  [E] Encouracado\n");
    printf("            [C] Cruzador      [D] Destroyer\n");
}




