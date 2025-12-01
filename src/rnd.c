//Geração de números aleatórios

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "rnd.h"


//Inicializar a semente do gerador de números aleatórios.
void rnd_init() {
    // A função srand() inicializa o gerador de números pseudo-aleatórios.
    // Usamos time(NULL) como argumento para garantir que a semente seja diferente
    // a cada execução do programa, fornecendo verdadeira "aleatoriedade".
    srand(time(NULL));
}

// Gerar um número inteiro aleatório dentro de um intervalo definido.
int rnd_get_int(int min, int max) {
    if (min > max) {                   // Garante que o mínimo não seja maior que o máximo.
        return min;                            
    }


    // O intervalo de números possíveis é (max - min) + 1.
    int range = max - min + 1;
    
    // Geração do Número Aleatório:
    return (rand() % range) + min;
}
