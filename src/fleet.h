//Frota de navios (definição, posicionamento, status)

#ifndef FLEET_H
#define FLEET_H

//Define a direção em que o navio será posicionado no tabuleiro
typedef enum{
    ORIENT_H,                                   // 0: Orientação horizontal
    ORIENT_V                                    // 1: Orientação vertical
}Orientation;

//Representa um navio individual
typedef struct{
    char name[20];                    // Nome do navio (ex: "Porta-aviões")
    int length;                       // Tamanho do navio em células (ex: 5)
    int hits;                         // Contador de acertos que o navio já sofreu
    int placed;                       // Flag (0 ou 1) indicando se o navio já está posicionado no tabuleiro
}Ship;

//Representa o conjunto total de navios de um jogador (a Frota)
typedef struct {
    Ship *ships;                      // Este ponteiro será alocado usando malloc em fleet_create (em fleet.c) para armazenar todos os navios da frota
    int count;                        // Número total de navios na frota (ex: 6)
} Fleet;

#endif

