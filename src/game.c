//Regras do jogo e controle dos turnos
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "game.h"
#include "io.h"
#include "fleet.h"
#include "rnd.h"

// Inicializa toda a estrutura do jogo
Game game_init(int rows, int cols) {
    Game g;
    // Configuração do Jogador 1 
    g.p1.board = board_create(rows, cols);
    g.p1.shots = board_create(rows, cols);  // Cria o board de tiros
    g.p1.fleet = fleet_create();            // Cria a frota padrão

    strcpy(g.p1.nickname, "Jogador 1");     //Define um nome padrão
    g.p1.total_shots = 0;
    g.p1.total_hits = 0;
    //  Configuração do Jogador 2 
    g.p2.board = board_create(rows, cols);  
    g.p2.shots = board_create(rows, cols);
    g.p2.fleet = fleet_create();
    strcpy(g.p2.nickname, "Jogador 2");
    g.p2.total_shots = 0; 
    g.p2.total_hits = 0;  
    //Configurações Iniciais da partida
    g.current_player = 0;     //Começa com jogador 1                          
    g.game_over = 0;     

    return g;
}

// Limpa a memória
void game_destroy(Game *game) {
    //Destrói board e frotas do p1 e p2
    board_destroy(&game->p1.board);
    board_destroy(&game->p1.shots);
    fleet_destroy(&game->p1.fleet);
    board_destroy(&game->p2.board);
    board_destroy(&game->p2.shots);
    fleet_destroy(&game->p2.fleet);
}

// Verifica se um navio afundou
int game_check_sunk_ship(Ship *ship) {
    if (ship->hits >= ship->length) {  //Acertos >=tamanho
        return 1;// Afundou
    }
    return 0; // Ainda vivo
}

// Atualiza o estado das células e a vida do navio após um tiro válido
static ShotResult game_check_hit_or_miss(Player *enemy, Cell *shot_c, Cell *real_c) {
    if (real_c->state == CELL_SHIP) {
        shot_c->state = CELL_HIT;        // Marca no visual
        shot_c->ship_id = real_c->ship_id;   //Copia o ID do navio para o board de tiros 

        real_c->state = CELL_HIT;   // Marca dano real

        int ship_id = real_c->ship_id;
        if (ship_id >= 0 && ship_id < enemy->fleet.count) {
            Ship *hit_ship = &enemy->fleet.ships[ship_id];
            hit_ship->hits++; 
            if (game_check_sunk_ship(hit_ship)) return SHOT_SUNK;
        }
        return SHOT_HIT;
    } 
    else {                               // Errou (MISS)
        shot_c->state = CELL_MISS;
        return SHOT_MISS;
    }
}

//Processamento de tiro
ShotResult game_handle_shot(Game *game, int row, int col) {
    // Identifica quem é o atirador e quem é o alvo
    Player *shooter = (game->current_player == 0) ? &game->p1 : &game->p2;
    Player *enemy   = (game->current_player == 0) ? &game->p2 : &game->p1;

    Cell *shot_c = board_get_cell(&shooter->shots, row, col);          // Onde eu vejo/marco
    Cell *real_c = board_get_cell(&enemy->board, row, col);            // O que existe de verdade

    // Validações de Regra (Fluxos Alternativos)
    if (!shot_c || !real_c) return SHOT_INVALID;           //Coordeanda inválida
    if (shot_c->state != CELL_WATER) return SHOT_REPEATED; //Coordenada repetida

    shooter->total_shots++;         // Contabiliza o tiro
    ShotResult res = game_check_hit_or_miss(enemy, shot_c, real_c);
    if (res == SHOT_HIT || res == SHOT_SUNK) {
        shooter->total_hits++;                   // Contabiliza o acerto
    }

    //Passando nas validações, chama a lógica de acerto/erro
    return res;
}

// Verifica se o jogo acabou,1 (Vitória/Fim) ou 0 (Continua).
int game_check_win(Game *game) {
    // Define quem é o inimigo (quem está levando os tiros)
    Player *enemy = (game->current_player == 0) ? &game->p2 : &game->p1;

    // Verifica a frota do inimigo navio por navio
    for (int i = 0; i < enemy->fleet.count; i++) {
        Ship *s = &enemy->fleet.ships[i];
        if (!game_check_sunk_ship(s)) {              // Se tiver um navio que não afundou, o jogo continua.
            return 0; 
        }
    }
    game->game_over = 1;                      // fim de jogo.
    return 1;                                 // Vitória decretada
}

// Lógica para posicionar todos os navios de forma aleatória.
void game_place_ships_auto(Player *p, int board_size) {
    printf("Posicionando navios de %s automaticamente...\n", p->nickname);
    for (int i = 0; i < p->fleet.count; i++) {
        Ship *s = &p->fleet.ships[i];
        // Tenta posições aleatórias até encontrar uma válida
        while (1) {
            int r = rnd_get_int(0, board_size - 1);
            int c = rnd_get_int(0, board_size - 1);
            Orientation o = (Orientation)rnd_get_int(0, 1);
            
            if (fleet_check_placement(&p->board, s, r, c, o)) {
                fleet_place_ship(&p->board, s, i, r, c, o);
                break;                                //Sucesso, vai indo de navio a navio
            }
        }
    }
    printf("Todos os navios de %s foram posicionados.\n", p->nickname);
}
// Pergunta orientação ao usuário H ou V
static Orientation ask_orientation() {
    char input[100];                          
    char c;
    
    while (1) {
        printf("Orientacao (H/V): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }
        if (sscanf(input, " %c", &c) == 1) {
            c = toupper(c);
            if (c == 'H') return ORIENT_H;
            if (c == 'V') return ORIENT_V;
        }
        printf("Orientacao invalida. Digite H para Horizontal ou V para Vertical.\n");
    }
}
//Lógica para posicionar um único navio manualmente
static void place_single_ship_manual(Player *p, Ship *s, int ship_id, int size) {
    int r, c;
    Orientation o;
    printf("Posicione: %s (Tam %d)\n", s->name, s->length);
    while (1) {                                     // Tenta ler coord e orientação até ser válido
        if (!io_get_shot_coord(size, &r, &c)) continue;
        o = ask_orientation();
        
        if (fleet_check_placement(&p->board, s, r, c, o)) {
            fleet_place_ship(&p->board, s, ship_id, r, c, o);
            printf("Sucesso!\n");
            break;
        } else {
            printf("Posicao invalida (colisao ou fora do mapa).\n");
        }
    }
}
// Gerencia o posicionamento manual de toda a frota
void game_place_ships_manual(Player *p, int board_size) {
    printf("\n=== POSICIONAMENTO MANUAL: %s ===\n", p->nickname);
    for (int i = 0; i < p->fleet.count; i++) {
        place_single_ship_manual(p, &p->fleet.ships[i], i, board_size);
    }
}

// Gerencia um turno completo (Exibir -> Ler -> Atirar -> Resultado)
static void process_turn(Game *game, Player *current, Player *enemy) {
    int r, c;
    printf("\n--- TURNO DE %s ---\n", current->nickname);
    printf("Seus tiros (Inimigo: %s):\n", enemy->nickname);

    board_display(&current->shots, 0); 

    while (1) {                                     // Loop até conseguir um tiro válido
        if (!io_get_shot_coord(current->board.rows, &r, &c)) continue;
        
        ShotResult res = game_handle_shot(game, r, c);
        if (res == SHOT_INVALID || res == SHOT_REPEATED) {
            printf("Tiro invalido ou repetido. Tente de novo.\n");
            continue;
        }
        // Exibe resultado
        const char *s_name = "Navio";
        bool sunk = (res == SHOT_SUNK);
        if (res == SHOT_HIT || sunk) {
             int sid = board_get_cell(&enemy->board, r, c)->ship_id;
             if (sid >= 0) s_name = enemy->fleet.ships[sid].name;
        }
        io_show_shot_result(res, s_name, sunk);
        break; // Turno concluído
    }
}


// Executa o loop principal de turnos do jogo.
void game_loop(Game *game, char placement_mode) {
    if (placement_mode == 'M') {
        game_place_ships_manual(&game->p1, game->p1.board.rows);         //Fase de posicionamento
        game_place_ships_manual(&game->p2, game->p2.board.rows);
    } else {
        game_place_ships_auto(&game->p1, game->p1.board.rows);
        game_place_ships_auto(&game->p2, game->p2.board.rows);
    }
    game->current_player = 0;                                             //Fase de Batalha
    printf("\n=== INICIO DA BATALHA ===\n");
    while (!game->game_over) {
        //Identifica o jogador atual e o oponente.
        Player *curr = (game->current_player == 0) ? &game->p1 : &game->p2;
        Player *enemy = (game->current_player == 0) ? &game->p2 : &game->p1;
        process_turn(game, curr, enemy);
        if (game_check_win(game)) break;
        game->current_player = 1 - game->current_player;                  //Alterna 0 e 1
    }                                                
    // Identifica o vencedor e o perdedor
    Player *winner = (game->current_player == 0) ? &game->p1 : &game->p2;
    Player *loser  = (game->current_player == 0) ? &game->p2 : &game->p1;
    io_show_winner_stats(winner, loser);
}
