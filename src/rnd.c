//Geração de números aleatórios (para modo automático)

#ifndef RND_H
#define RND_H

//Inicializa a semente para o gerador de números pseudo-aleatórios (srand).
//Deve ser chamada apenas uma vez no início do programa (ex: em game_initialize ou main).
void rnd_init();

//Gera e retorna um número inteiro pseudo-aleatório no intervalo [min, max] (inclusivo).
int rnd_get_int(int min, int max);

#endif // RND_H
