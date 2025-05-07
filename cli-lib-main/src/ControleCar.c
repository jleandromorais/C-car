#include <stdio.h>
#include "keyboard.h"
#include "screen.h"

int carX = 10;
int carY = 10;

void desenhaCarro() {
    screenGotoxy(carX, carY);
    printf("CC");
}

void limpaCarro() {
    screenGotoxy(carX, carY);
    printf("  "); // apaga o carro anterior
}

int main() {
    int ch = 0;
    screenInit(0);        // Inicializa tela sem bordas
    keyboardInit();       // Inicializa teclado

    desenhaCarro();
    screenUpdate();

    while (ch != 27) { // ESC para sair
        if (keyhit()) {
            ch = readch();
            limpaCarro();

            if (ch == 'a' && carX > 1) carX--;          // Move para a esquerda
            if (ch == 'd' && carX < MAXX - 3) carX++;   // Move para a direita

            desenhaCarro();
            screenUpdate();
        }
    }

    keyboardDestroy();  // Restaura configurações do terminal
    screenDestroy();    // Limpa tela
    return 0;
}
