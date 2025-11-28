//Ponto de partida do programa

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "io.h"
#include "rnd.h" // Importante: incluir para inicializar o aleatório

// Função auxiliar para rodar a partida (Loop do Jogo)
// O Matheus provavelmente vai criar isso separadamente, mas aqui está a estrutura.
void run_game_session() {
    // 1. Configurar (Pode vir do io_get_settings no futuro)
    int rows = 10;
    int cols = 10;

    printf("\n=== INICIANDO NOVA PARTIDA ===\n");
    
    // 2. Inicializar o Jogo (Sua função da Fase 7!)
    Game jogo = game_init(rows, cols);

    // 3. Posicionar Navios (Aqui entra a lógica da Fase 7 do Matheus)
    // Por enquanto, vamos colocar automático só para testar se tiver pronto
    // game_place_ships_auto(&jogo); 
    
    // 4. Loop Principal (Onde os turnos acontecem)
    // game_loop(&jogo); 
    printf(">> (Simulação) O jogo rodaria aqui...\n");

    // 5. Limpar memória ao final da partida (Sua função!)
    game_destroy(&jogo);
    printf("=== FIM DA PARTIDA ===\n\n");
}

int main() {
    // 1. Inicializar a semente de números aleatórios (Uma única vez!)
    rnd_init();

    int opcao = 0;

    // Loop do Menu Principal
    do {
        // Chama a função de menu do Matheus
        opcao = io_show_main_menu();

        switch (opcao) {
            case 1: // Novo Jogo
                run_game_session();
                break;
                
            case 2: // Configurações
                printf("\n[Em Desenvolvimento] Configurações virão aqui.\n");
                // io_show_settings_menu();
                break;
                
            case 3: // Sair
                printf("\nSaindo do jogo. Até mais!\n");
                break;
                
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 3); // Repete até o usuário escolher Sair

    return 0;
}

