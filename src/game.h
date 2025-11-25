//Regras do jogo e controle dos turnos
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Board board;
    Board shots; // Tabuleiro de tiros (visto do inimigo)
    Fleet fleet;
    char nickname[32];
}Player;

typedef struct{
    Player p1;
    Player p2;
    int current_player;
    int game_over;
}Game;


#endif