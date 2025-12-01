//Definição e controle dos navios
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fleet.h"

//Auxilia fleet_create()
static void fleet_add_ship(Fleet *f, const char *name, int length) {
    //  Aumenta a contagem de navios
    f->count++;

    // Aumenta mais um no array de navios
    Ship *temp = (Ship *) realloc(f->ships, f->count * sizeof(Ship));

    //Verificação
    if (temp == NULL) {
        printf("ERRO FATAL: Falha ao realocar memoria para a frota.\n");
        free(f->ships); 
        exit(1);
    }
    
    f->ships = temp;
    //  Configura o novo navio (que está na última posição: count - 1)
    Ship *new_ship = &f->ships[f->count - 1];
    strcpy(new_ship->name, name);
    new_ship->length = length;
    new_ship->hits = 0;
    new_ship->placed = 0;
}

//Frota padrão
Fleet fleet_create() {
    Fleet f;
    f.count = 0;
    f.ships = NULL; 

    // Adiciona os navios um a um dinamicamente
    
    // 1 Porta-aviões (5)
    fleet_add_ship(&f, "Porta-avioes", 5);
    
    // 1 Encouraçado (4)
    fleet_add_ship(&f, "Encouracado", 4);

    // 2 Cruzadores (3)
    fleet_add_ship(&f, "Cruzador", 3);
    fleet_add_ship(&f, "Cruzador", 3);

    // 2 Destroyers (2)
    fleet_add_ship(&f, "Destroyer", 2);
    fleet_add_ship(&f, "Destroyer", 2);

    return f;
}

// Libera a memória da frota
void fleet_destroy(Fleet *fleet) {
    if (fleet->ships != NULL) {
        free(fleet->ships);
        fleet->ships = NULL;
        fleet->count = 0; 
    }
}


//Verifica se o navio cabe
int fleet_check_placement(Board *board, Ship *ship, int row, int col, Orientation orient) {
    // Verificação limites do board
    if (orient == ORIENT_H) {

        if (col + ship->length > board->cols) return 0; // Sai do mapa à direita
    } else {

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
        cell->ship_id = ship_id;  
    }

    ship->placed = 1;      // Marca o navio como posicionado na struct dele

}