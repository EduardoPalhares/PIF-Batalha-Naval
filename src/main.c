//Ponto de partida do programa

#include <stdio.h>
#include "board.h"
#include "io.h"

int main() {
    printf("=== TESTE DA FASE 3: BOARD E MALLOC ===\n\n");

    // 1. TESTE DE CRIAÇÃO
    printf("[1] Criando tabuleiro 10x10...\n");
    Board tabuleiro = board_create(10, 10);                          // Chama a função que aloca dinamicamente o array de células.
    
    // 2. TESTE DE ACESSO E ALTERAÇÃO
    printf("[2] Colocando navios manualmente...\n");
    
    // Coloca um navio em B5 (Linha 1, Coluna 4)
    Cell *c1 = board_get_cell(&tabuleiro, 1, 4);                    // Linha 1 corresponde à Linha 2 do usuário; Coluna 4 corresponde à coluna 'E' (0=A).
    if (c1) c1->state = CELL_SHIP;                                  // Verifica se o ponteiro é válido antes de acessar a memória.

    // Coloca um tiro (HIT) em J10 (Linha 9, Coluna 9)
    Cell *c2 = board_get_cell(&tabuleiro, 9, 9);
    if (c2) c2->state = CELL_HIT;                                   // Acessa o membro 'state' e simula um acerto.

    // Tenta acessar fora do tabuleiro (Erro proposital)
    Cell *c_erro = board_get_cell(&tabuleiro, 20, 20);
    if (c_erro == NULL) {                                         // Verifica se a função board_get_cell retornou NULL, indicando que o acesso foi bloqueado.
        printf("    (Sucesso: O sistema bloqueou acesso fora do tabuleiro)\n");
    }

    // 3. TESTE DE EXIBIÇÃO
    printf("\n[3] Visão do Jogador (Vê navios):\n");
    board_display(&tabuleiro, 1);                           // O argumento '1' indica que os navios (CELL_SHIP) devem ser visíveis ('S').

    printf("\n[3] Visão do Inimigo (Navios ocultos):\n");
    board_display(&tabuleiro, 0);                               //O argumento '0' indica que os navios (CELL_SHIP) devem ser ocultados ('~').

    // 4. TESTE DE MEMÓRIA
    printf("\n[4] Liberando memória...\n");
    board_destroy(&tabuleiro);                                  //Chama a função que usa 'free()' para liberar o array de células alocadas.
    printf("    Memória liberada com sucesso.\n");

    int escolha = io_show_main_menu();

    // Lógica de controle com base na escolha
    switch (escolha) {
        case 1:
            printf("Iniciando Novo Jogo...\n");
            // Chamada futura: game_initialize();
            break;
        case 2:
            printf("Acessando Configuracoes...\n");
            // Chamada futura: io_show_config_menu();
            break;
        case 3:
            printf("Saindo do jogo. Ate mais!\n");
            break;
    }
  
    return 0;
}


