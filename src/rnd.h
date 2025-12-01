//Geração de números aleatórios
#ifndef RND_H
#define RND_H

//Inicializa a semente para o gerador de números pseudo-aleatórios com srand()
//É chamada apenas uma vez no início do programa .
void rnd_init();

//Gera e retorna um número inteiro pseudo-aleatório no intervalo [min, max] (inclusivo).
int rnd_get_int(int min, int max);

#endif // RND_H
