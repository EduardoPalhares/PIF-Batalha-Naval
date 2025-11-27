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

int io_show_main_menu() {                                  //Exibir o menu inicial e ler/validar a opção do usuário.
    int opcao;
    do {                                                    // Loop de leitura: repete até que uma opção válida (1, 2 ou 3) seja inserida.
        printf("\n=== BATALHA NAVAL ===\n");
        printf("1) Novo jogo\n");
        printf("2) Configuracoes\n");
        printf("3) Sair\n");
        printf("> ");
        if (scanf("%d", &opcao) != 1) {                               // Tenta ler a opção. Se o scanf retornar 0, a entrada não foi um número.
            printf("\nOpcao invalida. Digite um numero (1, 2 ou 3).\n");
            int c;                                        // Limpa o buffer de entrada (stdin) para descartar caracteres inválidos (letras, etc.)
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = 0; // Força o loop a continuar
            continue;
        }
        if (opcao < 1 || opcao > 3) {                                                   // Validação de intervalo
            printf("\nOpcao invalida. Escolha 1, 2 ou 3.\n");
        }
    } while (opcao < 1 || opcao > 3); // O loop continua enquanto a opção for inválida.
    return opcao;
}
