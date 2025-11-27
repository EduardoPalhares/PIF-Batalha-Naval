// Entrada e saída de dados (menus, leitura de coordenadas)
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

bool io_converter_coord(const char *input, int *row, int *col){
    
    if(input==NULL || strlen(input)<2){    // Validação inicial do ponteiro e do comprimento da string.
        return false;
    }

    char letra=toupper(input[0]);      // Pega o primeiro caractere (a letra) e o converte para maiúsculo.

    if (letra<'A' || letra >'Z'){     // Validação da Coluna: Garante que o primeiro caractere é uma letra válida (A-Z).
        return false;
    }

    // A coluna é calculada subtraindo o valor ASCII de 'A' do valor ASCII da letra.
    // Ex: 'A' - 'A' = 0; 'B' - 'A' = 1.
    // O resultado é escrito no endereço de memória de *col (passagem por ponteiro).
    *col=letra - 'A';

    int numero =atoi(&input[1]);                             // Usa atoi() para converter a parte numérica da string (a partir do segundo caractere).

    //As linhas do tabuleiro são numeradas de 1 a N. O índice interno do array é 0 a N-1.
    //O índice da linha é o número do usuário - 1.
    //O resultado é escrito no endereço de memória de *row (passagem por ponteiro).
    *row=numero-1;

    return true;                                              // A conversão da estrutura da string para números foi bem-sucedida.
}
