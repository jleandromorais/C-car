CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
BIN_DIR = bin
EXEC = jogo_carro

all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(SRC_DIR)/main.c $(SRC_DIR)/cenario.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean