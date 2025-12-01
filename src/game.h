//Regras do jogo e controle dos turnos
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

//Resultado do tiro
typedef enum {
    SHOT_MISS,      // Água
    SHOT_HIT,       // Acertou 
    SHOT_SUNK,      // Afundou 
    SHOT_REPEATED,  // Repetido
    SHOT_INVALID    // Inválido
} ShotResult;

// Estrutura do Jogador
typedef struct {
    Board board;        // Board com os navios
    Board shots;        // Board de tiros
    Fleet fleet;        // Frota do jogador
    char nickname[32];  // Apelido ou nome do jogador
    int total_shots;    // Total de tiros disparados
    int total_hits;     // Total de tiros acertados
}Player;

// Estrutura do jogo
typedef struct{
    Player p1;          // Jogador 1
    Player p2;          // Jogador 2
    int current_player; // Turno de jogar
    int game_over;      // Se acabou
}Game;

//Incia as estruturas do Board
Game game_init(int rows,int cols);

//Libera toda memŕoa alocada no jogo
void game_destroy(Game *game);

//Processa um tiro
ShotResult game_handle_shot(Game *game, int row, int col);

// Verifica se um navio afundou 
int game_check_sunk_ship(Ship *ship);

//Verifica vitória
int game_check_win(Game *game);

//Coloca navios automaticamente (lógica de pos. aleatório)
void game_place_ships_auto(Player *p, int board_size); 

//Coloca navios manualmente (lógica de I/O)
void game_place_ships_manual(Player *p, int board_size);

//Executa o loop principal do jogo
void game_loop(Game *game, char placement_mode);

#endif 
