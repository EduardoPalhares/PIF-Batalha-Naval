// Entrada e saída de dados (menus, leitura de coordenadas)

#ifndef IO_H
#define IO_H

#include <stdbool.h>

bool io_converter_coord(const char *input, int *row,int *col);               //conversão de string para número

int io_show_main_menu();                                  // Exibe o menu principal e retorna a opção escolhida.

bool io_get_settings(int *board_size, char *placement_mode);          //Usa ponteiros para retornar os valores lidos.

#endif
