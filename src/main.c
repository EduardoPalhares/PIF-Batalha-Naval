//Ponto de partida do programa

#include <stdio.h>
#include "board.h"

int main() {
    printf("=== TESTE DA FASE 3: BOARD E MALLOC ===\n\n");

    // 1. TESTE DE CRIAÇÃO
    printf("[1] Criando tabuleiro 10x10...\n");
    Board tabuleiro = board_create(10, 10);
    
    // 2. TESTE DE ACESSO E ALTERAÇÃO
    printf("[2] Colocando navios manualmente...\n");
    
    // Coloca um navio em B5 (Linha 1, Coluna 4)
    Cell *c1 = board_get_cell(&tabuleiro, 1, 4); 
    if (c1) c1->state = CELL_SHIP;

    // Coloca um tiro (HIT) em J10 (Linha 9, Coluna 9)
    Cell *c2 = board_get_cell(&tabuleiro, 9, 9);
    if (c2) c2->state = CELL_HIT;

    // Tenta acessar fora do tabuleiro (Erro proposital)
    Cell *c_erro = board_get_cell(&tabuleiro, 20, 20);
    if (c_erro == NULL) {
        printf("    (Sucesso: O sistema bloqueou acesso fora do tabuleiro)\n");
    }

    // 3. TESTE DE EXIBIÇÃO
    printf("\n[3] Visão do Jogador (Vê navios):\n");
    board_display(&tabuleiro, 1);

    printf("\n[3] Visão do Inimigo (Navios ocultos):\n");
    board_display(&tabuleiro, 0);

    // 4. TESTE DE MEMÓRIA
    printf("\n[4] Liberando memória...\n");
    board_destroy(&tabuleiro);
    printf("    Memória liberada com sucesso.\n");

    return 0;
}
