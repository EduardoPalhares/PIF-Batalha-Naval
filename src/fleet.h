//Frota de navios (definição, posicionamento, status)

#ifndef FLEET_H
#define FLEET_H

#include "orientation.h"

typedef struct {
    int row;           // linha inicial
    int col;           // coluna inicial
    int size;          // tamanho do navio
    Orientation orientation; // Vertical ou Horizontal
    int hits;          // quantas vezes já foi acertado
} Ship;

#define MAX_SHIPS 5

typedef struct {
    Ship ships[MAX_SHIPS];  
    int ship_count;         
} Fleet;

#endif
