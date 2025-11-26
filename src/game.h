//Regras do jogo e controle dos turnos
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

// Representa um jogador individual e seu estado no jogo.
typedef struct {
    Board board;                          // O tabuleiro onde estão posicionados OS SEUS navios
    Board shots;                          // Tabuleiro de tiros (visto do inimigo)
    Fleet fleet;                          // A frota de navios que pertence a este jogador
    char nickname[32];                    // Apelido ou nome do jogador
}Player;

// Representa o estado geral e o controle do jogo
typedef struct{
    Player p1;                            // Dados completos do Jogador 1
    Player p2;                            // Dados completos do Jogador 2
    int current_player;                   // Variável de controle que indica de quem é o turno, pode usar 1 para P1 e 2 para P2
    int game_over;                        // Flag (0 ou 1) que indica se o jogo terminou.O jogo termina quando a frota de um jogador é afundada
}Game;


#endif
