#include "../include/cenario.h"
#include "../include/screen.h"  // Inclua a nova biblioteca
#include <stdio.h>
#include <stdlib.h>
  

#define SCRWIDTH 80    // ou 100, conforme desejar
#define SCRHEIGHT 25 

void desenhar_cenario(int posicao) {
    screenClear();
    screenDrawBorders();

    int largura_cenario = 45;
    int altura_cenario = 20;
    int x_inicio = (SCRWIDTH - largura_cenario) / 2;
    int y_inicio = (SCRHEIGHT - altura_cenario) / 2;

    screenSetColor(LIGHTGRAY, BLACK);

    // Desenha as primeiras 10 linhas (acima do carro)
    for (int i = 0; i < 10; i++) {  // Aumentado de 7 para 10
        screenGotoxy(x_inicio, y_inicio + i);
        printf(" ||    |     ||     |    ||     |    ||");
    }

    // Linha do carro (agora na 11ª linha)
    screenGotoxy(x_inicio, y_inicio + 10);  // Mudado para +10 (11ª linha)
    printf(" ");
    for (int i = 0; i < largura_cenario; i++) {
        if (i >= posicao * 3 && i <= posicao * 3 + 1) {
    
            printf("\xF0\x9F\x9A\x97");
            screenSetColor(LIGHTGRAY, BLACK);
            i++;
        } 
        else if (i % 12 == 1 || i % 12 == 0|| i==6) {
            printf("|");
        } 
        else {
            printf(" ");
        }
    }

    // Restante das linhas (abaixo do carro)
    for (int i = 0; i < 8; i++) {  // Reduzido para 3 linhas para manter o total
        screenGotoxy(x_inicio, y_inicio + 11 + i);
        printf(" ||    |     ||     |    ||     |    ||");
    }

    screenUpdate();
}