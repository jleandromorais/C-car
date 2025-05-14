#include "../include/cenario.h"
#include "../include/screen.h"
#include "../include/cereja.h"
#include "../include/obstaculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// Define as dimensões da tela
#define SCRWIDTH 80
#define SCRHEIGHT 28

// Função principal para desenhar o cenário do jogo
void desenhar_cenario(int posicao, float tempo, int score) {
    setlocale(LC_ALL, "en_US.UTF-8");  // Ativa suporte a caracteres UTF-8 (emojis, por exemplo)

    // Garante que a posição do carro esteja entre 0 e 5
    posicao = (posicao < 0) ? 0 : (posicao > 5) ? 5 : posicao;

    // Limpa a tela e desenha a borda do jogo
    screenClear();
    screenDrawBorders();

    // Define o tamanho da pista e sua posição centralizada
    const int largura_pista = 46;
    const int altura_pista = 20;
    const int x_inicio = (SCRWIDTH - largura_pista) / 2;
    const int y_inicio = (SCRHEIGHT - altura_pista) / 2;

    // Representação visual da pista (com linhas verticais como obstáculos de cenário)
    const char *pista = "||      |     ||     |     ||     |     ||";

    // --- HUD (tempo e pontuação) ---
    screenSetNormal();
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(SCRWIDTH - 15, 1); // Coloca o cursor perto do canto superior direito
    printf("Tempo: %02d:%02d", (int)(tempo/60), (int)tempo%60); // Exibe tempo em minutos:segundos

    screenGotoxy(SCRWIDTH - 15, 2); // Logo abaixo do tempo
    printf("Pontos: %03d", score); // Exibe pontuação com 3 dígitos

    // --- Parte superior da pista acima do carro ---
    for(int i = 0; i < 12; i++) {
        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(x_inicio, y_inicio + i); // Move cursor linha a linha
        printf("%s", pista); // Desenha a faixa da pista
    }

    // --- Desenha cerejas coletáveis na pista ---
    desenhar_cerejas(x_inicio, y_inicio);

    // --- Desenha obstáculos (troncos) na pista ---
    desenhar_obstaculos(x_inicio, y_inicio);

    // --- Linha onde o carro está localizado ---
    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(x_inicio, y_inicio + 8);
    printf("%s", pista);

    // --- Desenha o carro do jogador ---
   const int x_carro = x_inicio + posicoes_x[posicao];
    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(x_carro, y_inicio + 8); // Coloca o carro na linha da "pista"
    printf("\xF0\x9F\x9A\x97"); // Emoji de carro 🚗

    // --- Parte inferior da pista abaixo do carro ---
    for(int i = 0; i < 3; i++) {
        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(x_inicio, y_inicio + 9 + i); // Desenha 4 linhas abaixo do carro
        printf("%s", pista);
    }

    // Atualiza a tela com tudo que foi desenhado
    screenUpdate();
}
