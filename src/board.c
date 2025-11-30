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

//Símbolos personalizados
static char get_cell_symbol(Cell *cell, int show_ships) {
    // Se for Água ou Erro (Tiro na água), símbolos padrão
    if (cell->state == CELL_WATER) return '~';
    if (cell->state == CELL_MISS)  return '.';
    // Se for Navio (Escondido ou Atingido)
    char letra = '?';
    switch (cell->ship_id) {
        case 0: letra = 'P'; break; // Porta-aviões
        case 1: letra = 'E'; break; // Encouraçado
        case 2: 
        case 3: letra = 'C'; break; // Cruzador
        case 4: 
        case 5: letra = 'D'; break; // Destroyer
        default: letra = 'S'; break; // Genérico (segurança)
    }
    // Lógica de Exibição
    if (cell->state == CELL_HIT) {
        return letra; // Se acertou, mostra a letra do navio (P, E, C, D) em vez de X
    } 
    if (cell->state == CELL_SHIP) {
        // Se o navio está intacto:mostra a letra se for o meu tabuleiro (show_ships=1),
        // esconde como água se for o inimigo (show_ships=0)
        return (show_ships) ? letra : '~';
    }
    return '?';
}

// Exibe o estado atual do tabuleiro no terminal
void board_display(Board *board, int show_ships) {
    // Cabeçalho das Colunas
    printf("   "); 
    for (int j = 0; j < board->cols; j++) printf("%c ", 'A' + j);
    printf("\n");
    //Linha Divisória Horizontal (---)
    printf("   "); 
    for (int j = 0; j < board->cols; j++) {
        printf("--"); // Dois traços para cada coluna
    }
    printf("\n");
    // Linhas do Tabuleiro
    for (int i = 0; i < board->rows; i++) {
        printf("%2d|", i + 1); // Número da linha + Barra Vertical (|)
        for (int j = 0; j < board->cols; j++) {
            Cell *c = board_get_cell(board, i, j);
            // Agora passamos o ponteiro 'c' inteiro
            printf("%c ", get_cell_symbol(c, show_ships));
        }
        printf("\n");
    }
    printf("   Legenda: [~] Agua  [.] Errou o tiro\n");
    printf("            [P] Porta-avioes  [E] Encouracado\n");
    printf("            [C] Cruzador      [D] Destroyer\n");
}




