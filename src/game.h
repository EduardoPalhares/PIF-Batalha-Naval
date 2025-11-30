//Regras do jogo e controle dos turnos
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef enum {
    SHOT_MISS,      // Errou (Água)
    SHOT_HIT,       // Acertou uma parte do navio
    SHOT_SUNK,      // Afundou o navio todo!
    SHOT_REPEATED,  // Já tinha atirado aqui antes
    SHOT_INVALID    // Coordenada inválida
} ShotResult;

// Representa um jogador individual e seu estado no jogo.
typedef struct {
    Board board;                          // O tabuleiro onde estão posicionados OS SEUS navios
    Board shots;                          // Tabuleiro de tiros (visto do inimigo)
    Fleet fleet;                          // A frota de navios que pertence a este jogador
    char nickname[32];                    // Apelido ou nome do jogador
    int total_shots;                      // Total de tiros disparados
    int total_hits;                       // Total de tiros que acertaram (X)
}Player;

// Representa o estado geral e o controle do jogo
typedef struct{
    Player p1;                            // Dados completos do Jogador 1
    Player p2;                            // Dados completos do Jogador 2
    int current_player;                   // Variável de controle que indica de quem é o turno, pode usar 1 para P1 e 2 para P2
    int game_over;                        // Flag (0 ou 1) que indica se o jogo terminou.O jogo termina quando a frota de um jogador é afundada
}Game;

//inicializa o jogo: cria tabuleiros (com tamanho rows x cols) e frotas para ambos
Game game_init(int rows,int cols);

//Libera toda memŕoa alocada no jogo (tabuleiros e frotas)
void game_destroy(Game *game);

//Função para processamento de tiro 
//Recebe o jogo e as coordenadas e retorna o resultado (EX:SHOT_HIT)
ShotResult game_handle_shot(Game *game, int row, int col);

// Verifica se um navio específico afundou (hits >= length)
// Retorna 1 (True) se afundou, 0 (False) se ainda está vivo
int game_check_sunk_ship(Ship *ship);

// Verifica se o jogo acabou (se todos os navios do oponente afundaram).
// Retorna 1 (Vitória/Fim) ou 0 (Continua).
// Também atualiza a flag game->game_over.
int game_check_win_condition(Game *game);

// Coloca navios automaticamente (lógica de pos. aleatório)
void game_place_ships_auto(Player *p, int board_size); 

// Coloca navios manualmente (lógica de I/O)
void game_place_ships_manual(Player *p, int board_size);

// Executa o loop principal de turnos do jogo.
void game_loop(Game *game, char placement_mode);

#endif //GAME_H
