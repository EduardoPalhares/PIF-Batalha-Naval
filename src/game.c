//Regras do jogo e controle dos turnos
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "io.h"
#include "fleet.h"

// Inicializa toda a estrutura do jogo
Game game_init(int rows, int cols) {
    Game g;

    // Configuração do Jogador 1 
    // Cria o tabuleiro dos navios dele
    g.p1.board = board_create(rows, cols);
    g.p1.shots = board_create(rows, cols);        // Cria o tabuleiro de tiros (inicialmente vazio, só água)
    g.p1.fleet = fleet_create();        // Cria a frota padrão

    strcpy(g.p1.nickname, "Jogador 1");    // Define um nome padrão (será alterado depois pelo io_get_player_names)

    //  Configuração do Jogador 2 
    g.p2.board = board_create(rows, cols);
    g.p2.shots = board_create(rows, cols);
    g.p2.fleet = fleet_create();
    strcpy(g.p2.nickname, "Jogador 2");

    // Configurações Iniciais da Partida
    g.current_player = 0; // Jogador 1 começa
    g.game_over = 0;      // Jogo em andamento

    return g;
}

// Limpa a memória
void game_destroy(Game *game) {
    // Libera Jogador 1
    board_destroy(&game->p1.board);
    board_destroy(&game->p1.shots);
    fleet_destroy(&game->p1.fleet);

    // Libera Jogador 2
    board_destroy(&game->p2.board);
    board_destroy(&game->p2.shots);
    fleet_destroy(&game->p2.fleet);
}

// Verifica se um navio afundou
int game_check_sunk_ship(Ship *ship) {
    // Se o número de acertos for igual ou maior que o tamanho, afundou.
    if (ship->hits >= ship->length) {
        return 1; // Verdadeiro (Afundou)
    }
    return 0; // Falso (Ainda vivo)
}

// Atualizar o estado das células e a vida do navio após um tiro válido.
static ShotResult game_check_hit_or_miss(Player *enemy, Cell *shot_c, Cell *real_c) {
    // O tiro acertou um navio (HIT)
    if (real_c->state == CELL_SHIP) {
        shot_c->state = CELL_HIT; // Marca 'X' no meu tabuleiro de tiros (feedback visual)
        real_c->state = CELL_HIT; // Marca 'X' no tabuleiro real do inimigo (computa dano)
        // Lógica de Dano no Navio
        int ship_id = real_c->ship_id;
        // Validação de segurança para garantir que o ID existe na frota
        if (ship_id >= 0 && ship_id < enemy->fleet.count) {
            Ship *hit_ship = &enemy->fleet.ships[ship_id];
            hit_ship->hits++; // Incrementa o contador de danos deste navio
            // Verifica imediatamente se esse tiro afundou o navio
            if (game_check_sunk_ship(hit_ship)) {
                return SHOT_SUNK; // Retorna aviso de "AFUNDOU!"
            }
        }
        return SHOT_HIT; // Retorna aviso de "ACERTOU!"
    } 
    // O tiro caiu na água (MISS)
    else {
        shot_c->state = CELL_MISS; // Marca '.' no meu tabuleiro de tiros
        return SHOT_MISS; // Retorna aviso de "ÁGUA"
    }
}

//Função para processamento de tiro 
//Recebe o jogo e as coordenadas e retorna o resultado (EX:SHOT_HIT)
ShotResult game_handle_shot(Game *game, int row, int col) {
    //  Identifica quem é o atirador (shooter) e quem é o alvo (enemy)
    Player *shooter = (game->current_player == 0) ? &game->p1 : &game->p2;
    Player *enemy   = (game->current_player == 0) ? &game->p2 : &game->p1;

    // Obtém os ponteiros para as células nos dois tabuleiros
    Cell *shot_c = board_get_cell(&shooter->shots, row, col); // Onde eu vejo/marco
    Cell *real_c = board_get_cell(&enemy->board, row, col);   // O que existe de verdade

    // Validações de Regra (Fluxos Alternativos)
    if (!shot_c || !real_c) {
        return SHOT_INVALID; // Erro: Coordenada fora do mapa
    }
    if (shot_c->state != CELL_WATER) {
        return SHOT_REPEATED; // Erro: Já atirou aqui (tem HIT ou MISS)
    }

    //Se passou nas validações, chama a lógica de acerto/erro
    return game_check_hit_or_miss(enemy, shot_c, real_c);
}

// Verifica se o jogo acabou (se todos os navios do oponente afundaram).
// Retorna 1 (Vitória/Fim) ou 0 (Continua).
// Também atualiza a flag game->game_over.
int game_check_win_condition(Game *game) {
    // Define quem é o inimigo (quem está levando os tiros)
    // Se o jogador atual é o P1 (0), o inimigo é o P2.
    Player *enemy = (game->current_player == 0) ? &game->p2 : &game->p1;

    // Verifica a frota do inimigo navio por navio
    for (int i = 0; i < enemy->fleet.count; i++) {
        Ship *s = &enemy->fleet.ships[i];

        // Se encontrar UM navio que NÃO afundou, o jogo não acabou.
        if (!game_check_sunk_ship(s)) {
            return 0; // Jogo continua
        }
    }
    //Se passou pelo loop, todos os navios afundaram!
    game->game_over = 1; // Atualiza a flag de estado do jogo
    return 1; // Vitória decretada
}

// Lógica para posicionar navios manualmente.
void game_place_ships_manual(Player *p, int board_size) {
    int i, r, c;
    char orientation_char;
    Orientation orient;
    printf("\n=== POSICIONAMENTO MANUAL: %s ===\n", p->nickname);
    printf("Você posicionará %d navios.\n", p->fleet.count);
    for (i = 0; i < p->fleet.count; i++) {                             // Itera sobre CADA navio na frota
        Ship *current_ship = &p->fleet.ships[i];
        printf("\nNavio %d de %d: %s (Tamanho %d)\n", 
               i + 1, p->fleet.count, current_ship->name, current_ship->length);
        do {                                    // Loop de validação: Repete até que o navio seja colocado em um local válido.
            if (!io_get_shot_coord(board_size, &r, &c)) {                            // Usamos io_get_shot_coord para aproveitar a validação de formato e limites.
                continue;                                                           // Em caso de erro fatal de leitura do I/O, avança para o próximo navio ou sai.
            }
            printf("Orientacao (H para Horizontal, V para Vertical): ");                               // LEITURA DA ORIENTAÇÃO
            if (scanf(" %c", &orientation_char) != 1) {                                  // Lê o caractere e converte para maiúsculo
                printf("Entrada invalida. Tente novamente.\n");
                clear_input_buffer();
                continue;
            }
            clear_input_buffer();
            orientation_char = toupper(orientation_char);
            if (orientation_char == 'H') {
                orient = ORIENT_H;
            } else if (orientation_char == 'V') {
                orient = ORIENT_V;
            } else {
                printf("Orientacao invalida. Use H ou V.\n");
                continue;
            }
            if (fleet_check_placement(&p->board, current_ship, r, c, orient) == 1) {                              // Nota: O seu fleet_check_placement retorna 1 (OK) ou 0 (Inválido).
                fleet_place_ship(&p->board, current_ship, i, r, c, orient);                                          // O ship_id é o índice 'i' do loop.
                printf("%s posicionado com sucesso!\n", current_ship->name);
                break;                             // Sai do loop 'do-while' interno e avança para o próximo navio.
            } else {
                printf("Posicao invalida: Colisao com outro navio ou fora dos limites do tabuleiro.\n");
            }
        } while (1);                                     // Repete infinitamente até o 'break' ser alcançado (posicionamento válido).
    }
}

//Controla o fluxo de turnos, I/O do usuário, processamento de tiros e
//           verificação da condição de vitória.
// ===================================================================================
void game_loop(Game *game, char placement_mode) {
    int row, col;
    ShotResult result;
    Player *current_p, *enemy_p;
    printf("\n=== FASE DE POSICIONAMENTO ===\n");
    if (placement_mode == 'M') {                                 // Posiciona navios para o Jogador 1
        game_place_ships_manual(&game->p1, game->p1.board.rows);
    } else { // 'A'
        game_place_ships_auto(&game->p1, game->p1.board.rows);
    }
    if (placement_mode == 'M') {                                         // Posiciona navios para o Jogador 2
        game_place_ships_manual(&game->p2, game->p2.board.rows);
    } else { // 'A'
        game_place_ships_auto(&game->p2, game->p2.board.rows);
    }
    game->current_player = 0;                                // Define o Jogador 1 como o primeiro a jogar
    printf("\n=== INICIO DA BATALHA ===\n");
    while (game->game_over == 0) {                        // LOOP PRINCIPAL DE TURNOS
        current_p = (game->current_player == 0) ? &game->p1 : &game->p2;                       // Identifica o jogador da vez e o oponente.
        enemy_p = (game->current_player == 0) ? &game->p2 : &game->p1;
        printf("\n--- TURNO DE %s ---\n", current_p->nickname);
        printf("Seu tabuleiro de tiros (Inimigo: %s):\n", enemy_p->nickname);                              // Exibe o tabuleiro do inimigo (shots) para que o jogador saiba onde atirar. Assumindo que board_show_hidden está implementado (você o fará em board.c)
        board_show_hidden(&current_p->shots); 
        do {                               // Loop de tiro: Garante que o jogador só avance se acertar um tiro válido.
            if (!io_get_shot_coord(current_p->board.rows, &row, &col)) {                             // board_size é o tamanho da linha (rows), que deve ser igual a cols.
                break;                                           // Em caso de erro de I/O, avança para o próximo jogador (opcional).
            }
            result = game_handle_shot(game, row, col);                            // PROCESSAMENTO DO TIRO (Lógica do Game)
            if (result == SHOT_REPEATED) {                                       // FEEDBACK E VERIFICAÇÃO DE RESULTADO
                printf("Voce ja atirou nessa coordenada. Tente outra.\n");
                // Continua o loop 'do-while' para pedir novo tiro.
            } else if (result == SHOT_INVALID) {
                printf("Coordenada invalida para o tabuleiro. Tente novamente.\n");
                // Continua o loop 'do-while'.
            } else {
                const char *ship_name = "Navio";               // Tiro bem-sucedido (MISS, HIT, SUNK). Determina o nome do navio, se houver acerto ou afundamento.
                bool is_sunk = false;
                if (result == SHOT_HIT || result == SHOT_SUNK) {
                    int ship_id = board_get_cell(&enemy_p->board, row, col)->ship_id;                             // O navio está no tabuleiro real do inimigo (enemy_p->board).
                    if (ship_id >= 0 && ship_id < enemy_p->fleet.count) {
                        ship_name = enemy_p->fleet.ships[ship_id].name;
                        is_sunk = (result == SHOT_SUNK);
                    }
                }
                io_show_shot_result(board_get_cell(&current_p->shots, row, col)->state, ship_name, is_sunk);                               // Exibe o resultado do tiro para o usuário.
                break; 
            }
        } while (1);             // Loop de tiro
        if (game_check_win_condition(game)) {                        // VERIFICAÇÃO DE VITÓRIA
            break;                                      // Se game->game_over foi setado para 1, o loop 'while' externo irá parar.
        }
        game->current_player = 1 - game->current_player;                                    // TROCA DE TURNO. Alterna entre 0 e 1.
    }
    io_show_winner_stats(current_p, enemy_p);                           // O vencedor é o jogador atual (current_p) porque ele acabou de afundar o último navio do oponente (enemy_p).
}
