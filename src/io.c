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
    // O resultado é escrito no endereço de memória de *col (passagem por ponteiro).
    *col=letra - 'A';

    int numero =atoi(&input[1]);                             // Usa atoi() para converter a parte numérica da string (a partir do segundo caractere).
     
    if (numero < 1) {
        return false;                                       //Bloquear números menores que 1
    }
    //O índice da linha é o número do usuário - 1.
    //O resultado é escrito no endereço de memória de *row (passagem por ponteiro).
    *row=numero-1;                                           //As linhas do tabuleiro são numeradas de 1 a N. O índice interno do array é 0 a N-1.


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


//Limpa o buffer de entrada para evitar que caracteres residuais interfiram 
static void clear_input_buffer() {
    int c;
    // Descarta todos os caracteres até encontrar uma quebra de linha ('\n') ou o fim do arquivo (EOF).
    while ((c = getchar()) != '\n' && c != EOF);
}


//Lidar com as configurações iniciais (tamanho do tabuleiro e modo).
bool io_get_settings(int *board_size, char *placement_mode) {
    int size = 0;
    char mode;
    do {                                // 1. LEITURA E VALIDAÇÃO DO TAMANHO DO TABULEIRO
        printf("\nTamanho do tabuleiro (6-26): ");
        if (scanf("%d", &size) != 1) {                              //Tenta ler um inteiro. Se falhar (retornar 0), a entrada não foi numérica.
            printf("Entrada invalida. Digite um numero.\n");
            clear_input_buffer();                                   // Limpa o buffer para a próxima tentativa.
            size = 0;                                       //força a continuação do loop.
            continue;}
        clear_input_buffer();                                // Limpa o buffer após uma leitura bem-sucedida de um número.
        if (size < 6 || size > 26) {                                 // Validação de Limites (6 a 26)
            printf("Tamanho invalido. Escolha um valor entre 6 e 26.\n"); }
    } while (size < 6 || size > 26);
    *board_size = size;                             // Armazena o tamanho validado no endereço de memória apontado por *board_size.
    do {                                           // 2. LEITURA E VALIDAÇÃO DO MODO DE POSICIONAMENTO
        printf("Posicionamento manual ou automatico? Digite 'M' ou 'A'. > ");
        if (scanf(" %c", &mode) != 1) {                                   // O espaço antes do %c ignora qualquer caractere de espaço em branco anterior (como \n).
            printf("Modo invalido. Digite 'M' ou 'A'.\n");
            clear_input_buffer();
            continue;}
        clear_input_buffer();                             // Limpeza do buffer após a leitura do caractere (para o caso de entrada como "M resto").
        mode = toupper(mode);                                       // Converte o caractere para maiúsculo para aceitar 'm' ou 'a'.
        if (mode == 'M' || mode == 'A') {                            // Validação de Opção ('M' ou 'A')
            *placement_mode = mode;                                         // Armazena o modo validado no endereço de memória apontado por *placement_mode.
            break;} 
            else { 
            printf("Modo invalido. Digite 'M' para Manual ou 'A' para Automatico.\n");}
    } while (1);                                                            // Loop infinito até que o break seja alcançado.
    return true;                                                           // Retorna sucesso na leitura de configurações.
}

void io_get_player_names(char *p1_nickname, char *p2_nickname) {                            //Objetivo: Solicitar e armazenar o nome dos dois jogadores.
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("\n===REGISTRO DE JOGADORES===\n");
    printf("Nome do Jogador 1 (no máximo 31 caracteres): ");                            // 1. Leitura do Nome do Jogador 1
    fgets(p1_nickname, 32, stdin);
    p1_nickname[strcspn(p1_nickname, "\n")] = '\0';                                 // Usamos strcspn para encontrar a posição do '\n' e substituí-lo por '\0' (terminador de string).
    printf("Nome do Jogador 2 (no máximo 31 caracteres): ");                           // 2. Leitura do Nome do Jogador 2
    fgets(p2_nickname, 32, stdin);                 
    p2_nickname[strcspn(p2_nickname, "\n")] = '\0';
    printf("Nomes registrados!\n");
}

//Ler a coordenada do tiro, validar formato e limites do tabuleiro.
bool io_get_shot_coord(int max_size, int *row, int *col) {
    char input[10]; // Buffer para ler a coordenada (ex: A10, B5)
    int temp_row = -1, temp_col = -1;
    bool valid_input = false;
    do {                        // Loop de validação: Repete até obter uma coordenada válida nos limites do tabuleiro.
        printf("Digite coordenada do tiro (ex.: E5): ");
        if (fgets(input, sizeof(input), stdin) == NULL){                           // Uso de fgets para ler a coordenada de forma segura.
            return false;                   // Erro de leitura.
        }
        input[strcspn(input, "\n")] = '\0';                              // Limpa o caractere '\n' inserido pelo fgets.
        if (!io_converter_coord(input, &temp_row, &temp_col)) {                      // Tenta converter a string (ex: "B5") para índices numéricos (temp_row, temp_col).
            printf("Coordenada invalida. Formato incorreto (esperado LetraNumero, ex: A1).\n");
            continue; // Tenta novamente.
        }
        if (temp_row < 0 || temp_row >= max_size || temp_col < 0 || temp_col >= max_size) {                    // Verifica se os índices convertidos estão dentro dos limites do tabuleiro.
            printf("Coordenada fora dos limites do tabuleiro (%c1 a %c%d).\n", 'A', 'A' + max_size - 1, max_size);
            continue;                     // Tenta novamente.
        }
        valid_input = true;                                        // Se chegou até aqui, a coordenada é válida.
    } while (!valid_input);
    *row = temp_row;                            // Armazena os índices validados nos ponteiros de retorno.
    *col = temp_col;
    return true;
}


//Exibir o resultado do tiro para o usuário (ÁGUA, ACERTOU, AFUNDOU).
void io_show_shot_result(ShotResult result, const char *ship_name, bool is_sunk) {
    printf("Resultado: ");

    // Tratamento para ÁGUA
    if (result == SHOT_MISS) {
        printf("AGUA.\n");
    }
    // Tratamento para Erros (Repetido ou Inválido)
    else if (result == SHOT_REPEATED || result == SHOT_INVALID) {
        printf("Erro: Tiro repetido ou coordenada invalida.\n");
    }
    // Tratamento para Acertos (HIT ou SUNK)
    else if (result == SHOT_HIT || result == SHOT_SUNK) {
        // Verifica se afundou (pelo enum ou pela flag bool)
        if (result == SHOT_SUNK || is_sunk) {
            printf("AFUNDOU %s!\n", ship_name);
        } else {
            printf("ACERTOU no %s!\n", ship_name);
        }
    }
}


//Calcula a precisão e imprime o bloco de estatísticas para um jogador.
static void print_player_stats(const Player *p) {
    //Valores reais
    int total_shots = p->total_shots;    
    int hits = p->total_hits;     
    
    double accuracy = 0.0;
    
    if (total_shots > 0) {                                             // Cálculo da precisão: (acertos / tiros) * 100.0. Não requer math.h.
        accuracy = ((double)hits / total_shots) * 100.0;
    }
    printf("Estatisticas de %s:\n", p->nickname);
    printf("Tiros: %d | Acertos: %d | Precisao: %.1f%%\n", total_shots, hits, accuracy);
}

//Exibir o vencedor e as estatísticas.
void io_show_winner_stats(const Player *winner, const Player *loser) {
    printf("\n*** FIM DE JOGO ***\n");
    printf("Vencedor: %s\n", winner->nickname);                   // Exibe o vencedor, acessando diretamente o campo 'nickname'.
    printf("\n--- Estatisticas do Vencedor ---\n");                         // Imprime as estatísticas do Vencedor.
    print_player_stats(winner);
    printf("\n--- Estatisticas do Perdedor ---\n");                             // Imprime as estatísticas do Perdedor.
    print_player_stats(loser);
}

//Exibe a composição de frotas para os jogadores

void io_show_fleet_rule() {
    printf("\n=== COMPOSICAO DA FROTA ===\n");
    printf("- 1 Porta-avioes (5 celulas)\n");
    printf("- 1 Encouracado  (4 celulas)\n");
    printf("- 2 Cruzadores   (3 celulas)\n");
    printf("- 2 Destroyers   (2 celulas)\n");
    printf("===========================\n");
}