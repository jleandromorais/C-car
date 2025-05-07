#include <stdio.h>
#include "ControleCar.h"

// Variáveis locais (static para evitar conflitos)
static int carX = 10;
static int carY = 10;

// Função para desenhar o carro
static void desenhaCarro() {
    screenGotoxy(carX, carY);
    printf("CC");
}

// Função para apagar o carro
static void limpaCarro() {
    screenGotoxy(carX, carY);
    printf("  ");
}

// Implementação da função principal
int ControleCar_run() {
    int ch = 0;
    
    // Inicializa sistemas
    screenInit(0);        // Tela sem bordas
    keyboardInit();       // Teclado

    // Desenha o carro inicial
    desenhaCarro();
    screenUpdate();

    // Loop principal
    while (ch != 27) { // ESC para sair
        if (keyhit()) {
            ch = readch();
            limpaCarro();

            // Movimento para esquerda
            if (ch == 'a' && carX > 1) carX--;
            
            // Movimento para direita
            if (ch == 'd' && carX < MAXX - 3) carX++;

            // Redesenha o carro na nova posição
            desenhaCarro();
            screenUpdate();
        }
    }

    // Finalização
    keyboardDestroy();  // Restaura terminal
    screenDestroy();    // Limpa tela
    
    return 0;
}