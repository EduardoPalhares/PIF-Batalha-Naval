// Entrada e saída de dados (menus, leitura de coordenadas)
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

bool io_converter_coord(const char *input, int *row, int *col){

    if(input==NULL || strlen(input)<2){
        return false;
    }

    char letra=toupper(input[0]);

    if (letra<'A' || letra >'Z'){
        return false;
    }

    *col=letra - 'A';

    int numero =atoi(&input[1]);

    *row=numero-1;

    return true;
}