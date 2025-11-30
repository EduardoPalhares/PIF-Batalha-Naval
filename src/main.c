//Ponto de partida do programa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "io.h"
#include "rnd.h"

// Função auxiliar que gerencia uma partida completa
void run_game_session() {
    int size = 10;
    char mode = 'A'; // Padrão
    char p1_name[32];
    char p2_name[32];

    //Coleta de Dados
    io_get_player_names(p1_name, p2_name);
    io_get_settings(&size, &mode);
    io_show_fleet_rule();

    printf("\n=== PREPARANDO O TABULEIRO [%dx%d] ===\n", size, size);
    //  Inicialização do Jogo
    Game jogo = game_init(size, size);
    strcpy(jogo.p1.nickname, p1_name);
    strcpy(jogo.p2.nickname, p2_name);

    // Inicia o Loop Principal (Posicionamento + Batalha)
    // Agora chamamos a função real que está no game.c!
    game_loop(&jogo, mode);

    // Encerramento e Limpeza
    game_destroy(&jogo);
    printf("\n=== MEMORIA LIBERADA. FIM DA SESSAO ===\n");
}

int main() {
    // Inicializa aleatoriedade
    rnd_init();
    int opcao = 0;

    do {
        opcao = io_show_main_menu();

        switch (opcao) {
            case 1: 
                run_game_session(); // Começa o jogo!
                break;
            case 2: 
                printf("\n[Info] As configuracoes sao definidas ao iniciar um Novo Jogo.\n");
                break;
            case 3: 
                printf("\nSaindo do jogo. Ate mais!\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}
