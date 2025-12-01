
#   Makefile - Batalha Naval (PIF 2025.2)

# Configurações do Compilador
CC = gcc
# Flags obrigatórias para garantir "Qualidade de Código" (sem warnings)
CFLAGS = -Wall -Wextra -std=c99 -g

#  Estrutura de Pastas
SRC_DIR = src
OBJ_DIR = obj

#  Nome do Executável Final
EXEC = batalha_naval

#  Lista de Arquivos
# Pega todos os .c dentro da pasta src/ (main.c, board.c, fleet.c, io.c, rnd.c, game.c)
SOURCES = $(wildcard $(SRC_DIR)/*.c)
# Cria a lista de objetos equivalentes na pasta obj/
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#   Regras de Compilação

# Regra padrão: ao digitar apenas 'make', cria o executável
all: $(EXEC)

# Regra para Linkar (Juntar tudo no executável)
$(EXEC): $(OBJECTS)
	@echo "Linkando o projeto..."
	$(CC) $(OBJECTS) -o $(EXEC)
	@echo "Sucesso! Execute com: ./$(EXEC)"

# Regra para Compilar (Transformar cada .c em .o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo " Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para Limpar (Apagar arquivos temporários)
clean:
	@echo "Limpando arquivos compilados..."
	rm -rf $(OBJ_DIR) $(EXEC)

# Regra para Rodar o jogo direto
run: all
	@echo "Iniciando o jogo..."
	./$(EXEC)

.PHONY: all clean run