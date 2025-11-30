// Entrada e saída de dados (menus, leitura de coordenadas)

#ifndef IO_H
#define IO_H

#include "game.h" 
#include "board.h"
#include <stdbool.h>

bool io_converter_coord(const char *input, int *row,int *col);               //conversão de string para número

int io_show_main_menu();                                  // Exibe o menu principal e retorna a opção escolhida.

bool io_get_settings(int *board_size, char *placement_mode);          //Usa ponteiros para retornar os valores lidos.

void io_get_player_names(char *p1_nickname, char *p2_nickname);             // Solicita e armazena os nomes dos jogadores nos arrays fornecidos (passados por ponteiro).

bool io_get_shot_coord(int max_size, int *row, int *col);                // Lê e valida a coordenada de tiro, garantindo que esteja dentro dos limites.

void io_show_shot_result(ShotResult result, const char *ship_name, bool is_sunk);              // Exibe o resultado de um tiro com base no estado da célula e no status do navio.

void io_show_winner_stats(const Player *winner, const Player *loser);                 // Exibe o vencedor e as estatísticas de ambos os jogadores ao final do jogo.

void io_show_fleet_rule();  //Exibe a composição de frotas para os jogadores
#endif
