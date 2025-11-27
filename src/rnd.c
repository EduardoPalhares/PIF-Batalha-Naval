//Geração de números aleatórios (para modo automático)
// Implementação das funções de geração de números aleatórios.

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
    if (min > max) {                           // Garante que o mínimo não seja maior que o máximo.
        return min;                            //Podemos retornar o mínimo ou, idealmente, tratar como erro. Neste caso, retornamos 'min'.
    }

    // 2. Cálculo do Tamanho do Intervalo (Range):
    // O intervalo de números possíveis é (max - min) + 1.
    int range = max - min + 1;
    
    // 3. Geração do Número Aleatório:
    // A fórmula para gerar um número no intervalo [min, max] é: (rand() % range) + min. (rand() % range) garante um número no intervalo [0, range - 1].
    // Ex: [0, 5] se range = 6. Adicionar 'min' desloca o intervalo para [min, max]. Ex: (rand() % 6) + 5 -> gera números de 5 a 10.
    return (rand() % range) + min;
}
