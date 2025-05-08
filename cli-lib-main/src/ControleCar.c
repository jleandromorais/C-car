#include <stdio.h>
#include <unistd.h>
#include "ControleCar.h"
#include "screen.h"    // Supondo que existe para screenGotoxy()
#include "keyboard.h"  // Para keyboardInit(), keyhit(), etc.

// Variáveis globais do cenário
#define PISTA_WIDTH 20
#define NUM_PISTAS 3
static int carX = 10;  // Posição inicial do carro
static int carY = 7;   // Linha do carro (ajustada para o cenário)

// Desenha o cenário completo com pistas
static void desenhaCenario() {
    printf("\033[H\033[J");  // Limpa o terminal
    
    // Desenha as pistas (linhas verticais)
    for (int y = 0; y < 10; y++) {
        for (int pista = 0; pista < NUM_PISTAS; pista++) {
            printf("||");
            // Espaço entre as pistas (onde o carro se move)
            for (int x = 0; x < PISTA_WIDTH; x++) {
                if (y == carY && x == carX && pista == 1) {
                    printf("CC");  // Desenha o carro na pista central
                } else {
                    printf(" ");
                }
            }
        }
        printf("||\n");
    }
}

// Função principal
int ControleCar_run() {
    keyboardInit();
    
    while (1) {
        desenhaCenario();
        
        if (keyhit()) {
            int ch = readch();
            
            // Lógica de movimento (igual à sua versão original)
            if (ch == 'a' && carX > 0) carX--;
            if (ch == 'd' && carX < PISTA_WIDTH-2) carX++;
            if (ch == 27) break;  // ESC sai
        }
        
        usleep(100000);  // 100ms
    }
    
    keyboardDestroy();
    return 0;
}