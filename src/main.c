//Ponto de partida do programa

#include <stdio.h>
#include "../include/cell_state.h"
#include "../include/orientation.h"

int main() {
    enum CellState estado = CELL_SHIP;
    enum Orientation direcao = ORIENTATION_VERTICAL;

    printf("Estado da célula: %d\n", estado);
    printf("Orientação do navio: %d\n", direcao);

    // Simulando alteração de estado
    estado = CELL_HIT;
    printf("Novo estado: %d\n", estado);

    return 0;
}
