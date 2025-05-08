#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Posição do carrinho
int carX = 40;
const int carY = 23;

// Obstáculo
int obstX;
int obstY = 1;

// Pontuação
int pontos = 0;
int velocidade = 50;

void desenhaCarro() {
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(carX, carY);
    printf("A");  // símbolo do carrinho
}

void desenhaObstaculo() {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(obstX, obstY);
    printf("#");
}

void limpaPosicao(int x, int y) {
    screenGotoxy(x, y);
    printf(" ");
}

void desenhaPontuacao() {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(2, 1);
    printf("Pontos: %d", pontos);
}

int colidiu() {
    return obstY == carY && obstX == carX;
}

void novoObstaculo() {
    obstY = 1;
    obstX = rand() % (MAXX - 2) + 2;  // Evita as bordas
}

int main() {
    int ch = 0;
    srand(time(NULL));

    screenInit(1);
    keyboardInit();
    timerInit(velocidade);

    novoObstaculo();
    desenhaCarro();
    desenhaObstaculo();
    desenhaPontuacao();
    screenUpdate();

    while (ch != 27) { // ESC para sair
        if (keyhit()) {
            ch = readch();
            limpaPosicao(carX, carY);

            if (ch == 'a' && carX > 2) carX--;
            if (ch == 'd' && carX < MAXX - 1) carX++;

            desenhaCarro();
            screenUpdate();
        }

        if (timerTimeOver()) {
            limpaPosicao(obstX, obstY);
            obstY++;

            if (colidiu()) {
                screenSetColor(RED, BLACK);
                screenGotoxy(30, 12);
                printf("GAME OVER!");
                screenGotoxy(30, 13);
                printf("Pontuação: %d", pontos);
                break;
            }

            if (obstY >= carY) {
                pontos++;
                if (pontos % 5 == 0 && velocidade > 10) velocidade -= 5; // aumenta dificuldade
                novoObstaculo();
                timerInit(velocidade);
            }

            desenhaObstaculo();
            desenhaPontuacao();
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
