# 🚢 Batalha Naval em C

Projeto de implementação do clássico jogo Batalha Naval, desenvolvido inteiramente na linguagem C como requisito para a disciplina de Programação Imperativa e Funcional (PIF).

---

##  Contexto do Projeto

Este é o projeto final da disciplina de **Programação Imperativa e Funcional (PIFSI 2025.2)** do curso de Sistemas de Informação da **CESAR School**.

O objetivo principal é aplicar os conceitos fundamentais da linguagem C aprendidos em sala de aula, demonstrando o domínio de:
* **Structs e Enums** para modelagem de dados.
* **Ponteiros e Passagem por Referência**.
* **Alocação Dinâmica de Memória** (`malloc` e `free`).
* **Modularização** e organização de código.

##  Equipe

* **Artur Borges** ([LinkedIn](https://www.linkedin.com/in/arturborgesdnogueira/))
* **Eduardo Palhares** ([LinkedIn](https://www.linkedin.com/in/palhareseduardo))
* **Matheus Arantes** ([LinkedIn](https://www.linkedin.com/in/matheus-arantes-almeida-2a5a99366/))

---

##  Como Compilar e Executar

O projeto utiliza um `Makefile` para automatizar o processo de compilação. Certifique-se de ter o `gcc` e o `make` instalados.

1.  **Compilar o projeto:**
    Abra o terminal na raiz do projeto e execute:
    ```bash
    make
    ```

2.  **Executar o jogo:**
    Após a compilação, inicie o jogo com:
    ```bash
    ./batalha_naval
    ```

3.  **Limpar arquivos compilados (Opcional):**
    Para remover os arquivos `.o` e o executável gerado:
    ```bash
    make clean
    ```

---

## Decisões de Design e Implementação

Conforme solicitado no relatório técnico, destacamos as seguintes escolhas de arquitetura e design:

### 1. Modularização e Responsabilidade Única
O código foi dividido em módulos lógicos para garantir baixo acoplamento e alta coesão:
* **`game.c`**: Contém exclusivamente as regras de negócio (vitória, turnos, validação de tiro).
* **`io.c`**: Responsável por toda a interação com o usuário (`printf`, `scanf`, menus), isolando a lógica da apresentação.
* **`board.c` e `fleet.c`**: Gerenciam as estruturas de dados fundamentais.

### 2. Encapsulamento com Funções Estáticas
Utilizamos funções `static` (como `setup_ship` em `fleet.c` e `get_cell_symbol` em `board.c`) para criar funções auxiliares "privadas". Isso mantém o escopo global limpo e respeita a boa prática de manter funções públicas curtas e legíveis.

### 3. Tratamento Robusto de Entrada
Para evitar erros comuns de "lixo de buffer" em C, padronizamos a leitura de entradas (nomes, coordenadas e orientações) utilizando `fgets` e loops de limpeza de buffer. Isso impede que o jogo trave ou pule etapas caso o usuário digite algo inesperado.

### 4. Interface Visual Melhorada (UX)
Ao invés de utilizar apenas um 'X' genérico para acertos, implementamos uma lógica visual que exibe a inicial do navio atingido (**P**orta-aviões, **E**ncouraçado, **C**ruzador, **D**estroyer). Isso enriquece a estratégia do jogador, permitindo identificar qual tipo de navio está sendo atacado antes mesmo de afundá-lo.

### 5. Gestão de Memória
Toda a memória alocada dinamicamente para os tabuleiros e frotas (via `board_create` e `fleet_create`) é rigorosamente liberada ao final da execução através da função `game_destroy`, garantindo que não haja vazamentos de memória (*memory leaks*).

---

##  Funcionalidades

* [x] Tabuleiro configurável (6x6 a 26x26).
* [x] Posicionamento de navios Manual e Automático (Aleatório).
* [x] Validação de sobreposição e limites do mapa.
* [x] Sistema de turnos alternados.
* [x] Detecção de vitória e estatísticas finais (Precisão de tiro).

## Como Jogar 
* [x]**Objetivo**
* [x] O objetivo do batalha naval é afundar toda a frota de navios do seu oponente antes que ele afunde a sua.
* [x]**Jogabilidade**
* [x] O Jogo é disputado por dois jogadores
* [x] Os jogadores, ou o próprio jogo, caso os jogadores tenham escolhido o modo automático, posicionam as peças no tabuleiro
* [x] Os jogadores alteram em turnos disparando tiros em coordenadas (Por exemplo "H1")
* [x] Caso um jogador acerte o navio do adversário o jogo irá notificar "Acertou o Navio X"
* [x] Caso tenha afundado, tenha finalizado as peças determinadas de uma embarcação, aparecerá "Afundou o Navio X"
* [x] Caso não acerte nenhum navio, o jogo mostrará "AGUA"
* [x] O Jogo termina quando um dos adversários afundar todas as embacações do rival
