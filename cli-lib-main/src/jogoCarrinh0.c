#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Variáveis do jogo
static int carX = 40;
static const int carY = 23;
static int obstX, obstY = 1;
static int pontos = 0;
static int velocidade = 50;

// Protótipos das funções
static void desenhaCarro();
static void desenhaObstaculo();
static void limpaPosicao(int x, int y);
static void desenhaPontuacao();
static int colidiu();
static void novoObstaculo();

int jogoCarrinho() {
    int ch = 0;
    srand(time(NULL));

    // Inicializa sistemas - CORREÇÃO AQUI
    screenInit(1);  // Remove a verificação de retorno
    keyboardInit(); // Remove a verificação de retorno
    timerInit(velocidade);

    // Configuração inicial
    novoObstaculo();
    desenhaCarro();
    desenhaObstaculo();
    desenhaPontuacao();
    screenUpdate();

    // Loop principal do jogo
    while (ch != 27) { // ESC para sair
        if (keyhit()) {
            ch = readch();
            limpaPosicao(carX, carY);

            // Controles
            if (ch == 'a' && carX > 2) carX--;
            if (ch == 'd' && carX < MAXX - 1) carX++;

            desenhaCarro();
            screenUpdate();
        }

        if (timerTimeOver()) {
            limpaPosicao(obstX, obstY);
            obstY++;

            // Verifica colisão
            if (colidiu()) {
                screenSetColor(RED, BLACK);
                screenGotoxy(30, 12);
                printf("GAME OVER!");
                screenGotoxy(30, 13);
                printf("Pontuação: %d", pontos);
                break;
            }

            // Atualiza jogo
            if (obstY >= carY) {
                pontos++;
                if (pontos % 5 == 0 && velocidade > 10) {
                    velocidade -= 5; // Aumenta dificuldade
                }
                novoObstaculo();
                timerInit(velocidade);
            }

            desenhaObstaculo();
            desenhaPontuacao();
            screenUpdate();
        }
    }

    // Finalização
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}

// Implementações das funções auxiliares
static void desenhaCarro() {
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(carX, carY);
    printf("A");
}

static void desenhaObstaculo() {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(obstX, obstY);
    printf("#");
}

static void limpaPosicao(int x, int y) {
    screenGotoxy(x, y);
    printf(" ");
}

static void desenhaPontuacao() {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(2, 1);
    printf("Pontos: %d", pontos);
}

static int colidiu() {
    return obstY == carY && obstX == carX;
}

static void novoObstaculo() {
    obstY = 1;
    obstX = rand() % (MAXX - 2) + 2;
}

// Função principal
int JogoCarrinho0() {
    return jogoCarrinho();
}