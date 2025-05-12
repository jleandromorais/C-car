#include "../include/cenario.h"
#include "../include/screen.h"
#include "../include/cereja.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define SCRWIDTH 80
#define SCRHEIGHT 28

void desenhar_cenario(int posicao, float tempo, int score) {
    setlocale(LC_ALL, "en_US.UTF-8");

    posicao = (posicao < 0) ? 0 : (posicao > 5) ? 5 : posicao;

    screenClear();
    screenDrawBorders();

    const int largura_pista = 46;
    const int altura_pista = 20;
    const int x_inicio = (SCRWIDTH - largura_pista) / 2;
    const int y_inicio = (SCRHEIGHT - altura_pista) / 2;
    const char *pista = "||      |     ||     |     ||     |     ||";

    // HUD
    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(SCRWIDTH - 15, 1);
    printf("Tempo: %02d:%02d", (int)(tempo/60), (int)tempo%60);

    screenGotoxy(SCRWIDTH - 15, 2);
    printf("Pontos: %03d", score);

    screenGotoxy(SCRWIDTH - 15, 3);
    printf("Multiplicador: %dx", multiplicador_score);

    // Pista acima do carro
    for(int i = 0; i < 7; i++) {
        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(x_inicio, y_inicio + i);
        printf("%s", pista);
    }

    desenhar_cerejas(x_inicio,y_inicio);

    // Linha do carro
    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(x_inicio, y_inicio + 7);
    printf("%s", pista);

    // Carro
    const int x_carro = x_inicio + posicoes_x[posicao];
    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(x_carro, y_inicio + 7);
    printf("\xF0\x9F\x9A\x97");

    // Pista abaixo do carro
    for(int i = 0; i < 4; i++) {
        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(x_inicio, y_inicio + 8 + i);
        printf("%s", pista);
    }

    screenUpdate();
}
