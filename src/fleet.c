//Frota de navios (definição, posicionamento, status)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fleet.h"

//Função privada usada para criação de frota padrão(Função privada)
static void setup_ship(Ship *s, const char *name, int length){
    strcpy(s->name, name);// leva 
    s->length=length; // Comprimento do navio com quantas celúlas ele tem
    s->hits=0; // Inicializa o contador de acertos com 0 (navio novo, sem dano)
    s->placed=0; // Navio está na memória
}


//Frota padrão
Fleet fleet_create(){
    Fleet f;
    f.count =6; //Total de návios

    f.ships=(Ship *)malloc(f.count * sizeof(Ship));//Alocação para criar os espaços para os 6 navios na memória

    if (f.ships == NULL) { 
        printf("ERRO FATAL: Falha ao alocar memória para a frota.\n"); //Verifica o espaço na memória
        exit(1);
    }

    setup_ship(&f.ships[0],"Porta-aviões", 5); //Porta-aviões
    setup_ship(&f.ships[1],"Encouraçado",4); //Encouraçado

    for(int i = 2; i <= 3; i++) {
        setup_ship(&f.ships[i], "Cruzador", 3); // Cruzadores
    }
    for(int i = 4; i <= 5; i++) {
        setup_ship(&f.ships[i], "Destroyer", 2); // Destroyers
    }
    return f;
}

// Libera a memória da frota
void fleet_destroy(Fleet *fleet) {
    if (fleet->ships != NULL) {
        free(fleet->ships);
        fleet->ships = NULL; 
    }
}

//Verifica se é possível colocar o navio no board(sem gravar)
//Retorna 1 se for possível,0 se inválido (fora do mapa ou colisão)
int fleet_check_placement(Board *board, Ship *ship, int row, int col, Orientation orient) {
    // Verificação limites do tabuleiro
    if (orient == ORIENT_H) {
        //Se for horizontal, col + tamanho deve ser <= total de colunas
        if (col + ship->length > board->cols) return 0; // Sai do mapa à direita
    } else {
        //Se for vertical, row + tamanho deve ser <= total de linhas
        if (row + ship->length > board->rows) return 0; // Sai do mapa para baixo
    }
    //Verificar Colisão (Se já tem navio no caminho)
    for (int i = 0; i < ship->length; i++) {
        int r = row;
        int c = col;
        if (orient == ORIENT_H) {
            c += i; // Avança nas colunas
        } else {
            r += i; // Avança nas linhas
        }
        Cell *cell = board_get_cell(board, r, c); // Pega a célula naquela posição
        // Se a célula não for ÁGUA, já tem algo lá (colisão)
        if (cell->state != CELL_WATER) {
            return 0; 
        }
    }
    return 1;
}

//Grava o navio no tabuleiro
void fleet_place_ship(Board *board, Ship *ship, int ship_id, int row, int col, Orientation orient) {
    for (int i = 0; i < ship->length; i++) {
        int r = row;
        int c = col;

        if (orient == ORIENT_H) c += i;
        else r += i;

        Cell *cell = board_get_cell(board, r, c);
        
        // Atualiza o estado da célula
        cell->state = CELL_SHIP;
        cell->ship_id;  // Ex: 'A' - 'A' = 0; 'B' - 'A' = 1.d = ship_id;
    }

    ship->placed = 1;      // Marca o navio como posicionado na struct dele

}