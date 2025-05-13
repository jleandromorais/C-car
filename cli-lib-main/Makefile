CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm
SRC = src/main.c src/cenario.c src/tela.c src/screen.c src/timer.c src/ControleCar.c  src/cereja.c src/obstaculo.c
OBJ = $(SRC:.c=.o)
TARGET = bin/jogo_carro

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)