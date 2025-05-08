CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/cenario.c src/tela.c src/screen.c
OBJ = $(SRC:.c=.o)
TARGET = bin/jogo_carro

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)