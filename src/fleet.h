//Frota de navios (definição, posicionamento, status)

#ifndef FLEET_H
#define FLEET_H

#include "board.h" 

//Define a direção do posicinamento dos navios
typedef enum{
    ORIENT_H,     // 0 Orientação horizontal
    ORIENT_V     // 1 Orientação vertical
}Orientation;

//Representa um navio 
typedef struct{
    char name[20];     // Nome do navio 
    int length;        // Tamanho do navio em células 
    int hits;          // Contador de acertos que o navio já sofreu
    int placed;        // Se návio já está no tabuleiro
}Ship;

//Representa o conjunto total de navios de um jogador (a Frota)
typedef struct {
    Ship *ships;      // Armazena os navios na frota
    int count;        // Total de navios na frota 
} Fleet;

//Cria a frota padrão 
Fleet fleet_create();

//Libera a memória alocada para a frota
void fleet_destroy(Fleet *fleet);

//Verifica se é possível colocar o navio no board
int fleet_check_placement(Board *board, Ship *ship, int row, int col, Orientation orient);

//Grava o navio no board
void fleet_place_ship(Board *board, Ship *ship, int ship_id, int row, int col, Orientation orient);

#endif//FLEET_H

