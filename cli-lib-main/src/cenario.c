#include "../include/cenario.h"
#include "../include/screen.h"  // Biblioteca para manipular a "tela" no terminal (como limpar, posicionar cursor etc)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a largura e altura da tela (ajustável conforme o terminal)
#define SCRWIDTH 80
#define SCRHEIGHT 25

// Função que desenha o cenário com base na posição do carro e no tempo decorrido
void desenhar_cenario(int posicao, float tempo,int score) {
    screenClear();             // Limpa a tela atual
    screenDrawBorders();      // Desenha as bordas ao redor da tela

    // Exibe o tempo decorrido no canto superior direito da tela
    screenSetColor(YELLOW, BLACK);           // Define cor do texto (amarelo sobre preto)
    screenGotoxy(SCRWIDTH - 15, 1);          // Move o cursor para a posição superior direita
    int minutos = abs((int)(tempo / 60));    // Converte tempo em minutos
    int segundos = abs((int)tempo % 60);     // Obtém os segundos restantes
    printf("Seu Tempo: %02d:%02d", minutos, segundos);  // Imprime o tempo formatado

    screenSetColor(YELLOW,BLACK);
    screenGotoxy(SCRWIDTH-15,2);
    if(tempo<15){
    score =(int)(tempo*5);
    }
    else
    {
        score=(int)(tempo *10);
    }
    
    printf("Sua pontuação:%03d",score);

    // Define dimensões da "pista" e calcula onde ela começa para ficar centralizada
    int largura_cenario = 45;
    int altura_cenario = 20;
    int x_inicio = (SCRWIDTH - largura_cenario) / 2;
    int y_inicio = (SCRHEIGHT - altura_cenario) / 2;

    screenSetColor(LIGHTGRAY, BLACK);  // Define cor padrão da pista

    // Desenha as primeiras 10 linhas da estrada (acima do carro)
    for (int i = 0; i < 10; i++) {
        screenGotoxy(x_inicio, y_inicio + i);  // Move cursor linha por linha
        printf(" ||    |     ||     |    ||     |    ||");  // Linha da estrada com divisórias
    }

    // Desenha o carro na 11ª linha (posição central da pista)
    screenGotoxy(x_inicio, y_inicio + 10);  // Move cursor para a linha do carro
    printf(" ");
    for (int i = 0; i < largura_cenario; i++) {
        // Verifica se a posição atual é a posição do carro
        if (i >= posicao * 3 && i <= posicao * 3 + 1) {
            printf("\xF0\x9F\x9A\x97");  // Desenha emoji de carro 🚗
            screenSetColor(LIGHTGRAY, BLACK);  // Restaura a cor padrão
            i++;  // Pula um caractere extra (emoji ocupa dois espaços)
        } 
        // Desenha divisórias verticais na estrada
        else if (i % 12 == 1 || i % 12 == 0 || i == 6) {
            printf("|");
        } 
        else {
            printf(" ");  // Espaço vazio na pista
        }
    }

    // Desenha as 8 linhas inferiores da estrada (abaixo do carro)
    for (int i = 0; i < 8; i++) {
        screenGotoxy(x_inicio, y_inicio + 11 + i);  // Move cursor linha por linha
        printf(" ||    |     ||     |    ||     |    ||");  // Linha da estrada
    }

    screenUpdate();  // Atualiza a tela exibindo todo o conteúdo desenhado
}
