#include "../include/cenario.h"
#include "../include/screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCRWIDTH 80
#define SCRHEIGHT 25

void desenhar_cenario(int posicao, float tempo, int score) {
    // Garante que a posição esteja entre 0 e 5 (6 posições)
    if (posicao < 0) posicao = 0;
    if (posicao > 5) posicao = 5;

    screenClear();
    screenDrawBorders();

    // Mostra tempo e pontuação
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRWIDTH - 15, 1);
    printf("Tempo: %02d:%02d", (int)(tempo / 60), (int)tempo % 60);

    screenGotoxy(SCRWIDTH - 15, 2);
    score = (tempo < 15) ? (int)(tempo * 5) : (int)(tempo * 10);
    printf("Pontos: %03d", score);

    // Configurações da pista
    int largura_cenario = 46;
    int altura_cenario = 20;
    int x_inicio = (SCRWIDTH - largura_cenario) / 2;
    int y_inicio = (SCRHEIGHT - altura_cenario) / 2;

    screenSetColor(LIGHTGRAY, BLACK);

    // Modelo de pista com 6 posições (2 faixas + 3 divisórias)
    const char *modelo_pista = "||      |     ||     |     ||     |     ||";

    // Desenha as 10 linhas superiores
    for (int i = 0; i < 10; i++) {
        screenGotoxy(x_inicio, y_inicio + i);
        printf("%s", modelo_pista);
    }

    // Desenha a linha do carro (com emoji)
    screenGotoxy(x_inicio, y_inicio + 10);
    printf("%s", modelo_pista); // Desenha a pista primeiro

    // Posições X válidas para o carro (6 posições)
    int posicoes_validas[] = {4, 10, 17, 24, 30, 37}; 
    int x_carro = x_inicio + posicoes_validas[posicao];

    // Posiciona o carro
    screenGotoxy(x_carro, y_inicio + 10);
    printf("\xF0\x9F\x9A\x97"); // Emoji do carro (2 caracteres)

    // Desenha as 8 linhas inferiores
    for (int i = 0; i < 8; i++) {
        screenGotoxy(x_inicio, y_inicio + 11 + i);
        printf("%s", modelo_pista);
    }

    screenUpdate();
}