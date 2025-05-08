#include "../include/cenario.h"
#include <stdio.h>
#include <stdlib.h>

void limpar_tela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void desenhar_cenario(int posicao) {
    limpar_tela();
    
    // Desenha as 4 primeiras linhas da pista
    for (int i = 0; i < 4; i++) {
        printf("||          ||          ||          ||\n");
    }

    // Linha do carro - SEMPRE VISÍVEL
    printf("  "); // Espaço inicial
    for (int i = 0; i < 36; i++) {
        // Verifica se é posição do carro
        if (i >= posicao*3 && i <= posicao*3+1) {
            // Se estiver sobre uma faixa (posições 2,3,6,7,10,11)
            if (i % 12 == 0 || i % 12 == 1) {
                printf("CC"); // SOBREPÕE a faixa
                i++; // Pula próximo caractere
            } else {
                printf("CC"); // Fora da faixa
                i++; // Pula próximo caractere
            }
        } 
        // Desenha faixas normais
        else if ( i % 36==1||i==1 ||i==4 ||i==5 ||i==36||i==35 ||i==34) {
            printf("|");
        } 
        // Espaço vazio
        else {
            printf(" ");
        }
    }
    printf("\n");

    // Desenha as 2 últimas linhas
    for (int i = 0; i < 2; i++) {
        printf("||          ||          ||          ||\n");
    }
}