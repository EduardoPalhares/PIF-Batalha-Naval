//Frota de navios (definição, posicionamento, status)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fleet.h"

//Função privada usada para criação de frota padrão(Função privada)
static void setup_ship(Ship *s, const char *name, int length){
    strcpy(s->name, name);
    s->length=length;
    s->hits=0;
    s->placed=0;
}


//Frota padrão
Fleet fleet_create(){
    Fleet f;
    f.count =6; //Total de návios

    f.ships=(Ship *)malloc(f.count * sizeof(Ship));//Alocação para criar os espaços para os 6 navios na memória

    if (f.ships == NULL) { 
        printf("ERRO FATAL: Falha ao alocar memória para a frota.\n"); //Verifica o espaço na memória
        exit(1);
    }

    setup_ship(&f.ships[0],"Porta-aviões", 5); //Porta-aviões
    setup_ship(&f.ships[1],"Encouraçado",4); //Encouraçado

    for(int i = 2; i <= 3; i++) {
        setup_ship(&f.ships[i], "Cruzador", 3); // Cruzadores
    }
    for(int i = 4; i <= 5; i++) {
        setup_ship(&f.ships[i], "Destroyer", 2); // Destroyers
    }
    return f;
}

// Libera a memória da frota
void fleet_destroy(Fleet *fleet) {
    if (fleet->ships != NULL) {
        free(fleet->ships);
        fleet->ships = NULL; 
    }
}

